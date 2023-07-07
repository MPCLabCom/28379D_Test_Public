/* ==========================================================================
System Name:  	LAB_Inverter
File Name:		Main.c
Description:	INVERTER
Originator:		MPC Lab
Start Date 	: 	2021. 07. 30
Final Date 	: 	2021. 08. 30
Programmer 	: 	Jongwon Choi
Check		:
================================================================================
 History:
--------------------------------------------------------------------------------
07-30-2021	Version 0.1   Modified
================================================================================*/

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xD_Ipc_drivers.h"

//App


/*======================================================================
    User Define Function
======================================================================*/
interrupt void cpu_timer0_isr(void);

/*======================================================================
	etc. Variable
======================================================================*/
Uint16 counter=0;
Uint16 Flag = 0;
Uint32  SetReg = 0;
Uint16 GPIO10_Data = 0;
volatile Uint32 * GpioDataReg_Pointer;
void main(void)
{
	/*-----------------------------------------------------------------------------
		Step 1
		Disable Global Interrupt & Interrupt Flag Clear
	-----------------------------------------------------------------------------*/
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	/*-----------------------------------------------------------------------------
	 	 Copy time critical code and Flash setup code to RAM
		This includes InitFlash(), Flash API functions and any functions that are
		assigned to ramfuncs section.
		The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
		symbols are created by the linker. Refer to the device .cmd file.
		=> Please, look at F2837xD_SysCtrl.c
	----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------
		Step 2
		Initialize System Control: PLL, WatchDog, enable Peripheral Clocks
		This example function is found in the F28M3Xx_SysCtrl.c file.
	----------------------------------------------------------------------------*/
	InitSysCtrl();

	#ifdef _STANDALONE
		#ifdef _FLASH
		// Send boot command to allow the CPU2 application to begin execution
		IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
		#else
		// Send boot command to allow the CPU2 application to begin execution
		IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
		#endif
	#endif
	/*-----------------------------------------------------------------------------
		Step 3
		Initialize GPIO:
		This example function is found in the F28M3Xx_Gpio.c file and
		illustrates how to set the GPIO to it's default state.
	----------------------------------------------------------------------------*/
	InitGpio();
	//GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PULLUP|GPIO_OPENDRAIN); //Pull up
	//GPIO_SetupPinMux(34, GPIO_MUX_CPU1, 0);             //GPIO set
    EALLOW;



	GpioCtrlRegs.GPBPUD.bit.GPIO34 =  1; //Disables the Pull-Up
	GpioCtrlRegs.GPBODR.bit.GPIO34  = 0; //Normal Operation
	GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1; //Output
	GpioDataRegs.GPBDAT.bit.GPIO34  = 1; // LED Turn off;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;  // GPIO9 = GPIO9


	EDIS;

	GPIO_SetupPinOptions(20, GPIO_INPUT, GPIO_PULLUP); //Lab5
	//GPIO_SetupPinOptions(20, GPIO_INPUT, GPIO_INVERT|GPIO_PULLUP); //Lab6
	GPIO_SetupPinMux(20, GPIO_MUX_CPU1, 0);             //GPIO set
    InitEPwmGpio();

    GpioDataReg_Pointer = &GpioDataRegs.GPADAT.all;
	/*-----------------------------------------------------------------------------
		Step 4
		Initialize PIE vector table: Pie Vector Table relocation
	-----------------------------------------------------------------------------*/
	InitPieCtrl();
	InitPieVectTable();

	/*-----------------------------------------------------------------------------
	    Step 5
	    5.1 Interrupt Service routine re-mapping and Interrupt vector enable
	 -----------------------------------------------------------------------------*/
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    IER |= M_INT1; //Enable group 1 interrupts, ADCA1_INT, ADCB1_INT, ADCC1_INT
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //TIMER 0 Interrupt
	/*-----------------------------------------------------------------------------
	  Step 6
	   6.1 Initialize Peripherals for User Application
	-----------------------------------------------------------------------------*/
    InitCpuTimers();   // For this example, only initialize the Cpu Timers

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 200MHz CPU Freq, 1 second Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 200, 1000); //1msec
    CpuTimer0Regs.TCR.all = 0x4000; //Interrupt enable, flag clear
	/*-----------------------------------------------------------------------------
		Step 7
		7.1 Initialize S/W modules and Variables
	-----------------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------------
        Step 8
        Apps initialization
    -----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------
	    Step 9
	    9.1 Enable Global realtime interrupt DBGM
	    9.2 Enable Global Interrupt
	-----------------------------------------------------------------------------*/
	ERTM;	/* Enable Global realtime interrupt DBGM */
	EINT;   /* Enable Global interrupt INTM */
	/*-----------------------------------------------------------------------------
	    Step 9
	    9.1 Idle Loop
	-----------------------------------------------------------------------------*/
    for(;;)
    {
        F28x_usDelay(1000000);
        counter++;

        GPIO_WritePin(34,0);

        if(1==Flag)
        {
            EALLOW;
            *(volatile Uint16*)0x00007C0A = SetReg;
            //*(volatile Uint32*)0x00007C0A = SetReg;
            EDIS;
            //GPIO10_Data = GPIO_ReadPin(10);
            //GPIO10_Data = ((*(volatile Uint16*)0x00007F00)&0x00000040)>>10 ;
            GPIO10_Data = ((*(volatile Uint16*)0x00007F00)&0x00000400)>>10 ;
            Flag = 0;
        }
    }

}
/*======================================================================
	End of Main function.
======================================================================*/

interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   //DAC_Display();

   //
   // Acknowledge this interrupt to receive more interrupts from group 1
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
