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


/*======================================================================
	etc. Variable
======================================================================*/
Uint16 counter=0;

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
    InitEPwmGpio();

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


	EDIS;   // This is needed to disable write to EALLOW protected registers

	/*-----------------------------------------------------------------------------
	  Step 6
	   6.1 Initialize Peripherals for User Application
	-----------------------------------------------------------------------------*/

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
    }

}
/*======================================================================
	End of Main function.
======================================================================*/
