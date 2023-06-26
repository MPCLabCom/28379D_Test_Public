/*
 * F2837xD_DAC.c
 *
 *  Created on: 2016. 4. 6.
 *      Author: owner
 */

#include "F2837xD_device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File
#include "F2837xD_dac.h"   // F2837xD Examples Include File
#include "userdefines.h"
#include "userparms.h"

float32 gfDAC_Val_1;
float32 gfDAC_Val_2;
float32 gfDAC_Val_3;
float32 gfDAC_Val_4;

void InitDAC1Gpio(void);
void InitDAC2Gpio(void);
void InitDACGpio(void)
{

	// endable PWM11 and PWM 12 for DAC
	CpuSysRegs.PCLKCR2.bit.EPWM7=1;
	CpuSysRegs.PCLKCR2.bit.EPWM8=1;

	InitDAC1Gpio();
	InitDAC2Gpio();

	gfDAC_Val_1 = 0.0;
	gfDAC_Val_2 = 0.0;
	gfDAC_Val_3 = 0.0;
	gfDAC_Val_4 = 0.0;
}



void InitDAC1Gpio(void) //PWM DAC1-2 //InitEPwm7Gpio
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
   	for reduced power consumption */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;    // Disable pull-up on GPIO159 (EPWM8A)
	GpioCtrlRegs.GPFPUD.bit.GPIO160 = 1;    // Disable pull-up on GPIO166 (EPWM8B)

	/* Configure EPWM-6 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;   // Configure GPIO165 as EPWM8A
	GpioCtrlRegs.GPFMUX1.bit.GPIO160 = 1;   // Configure GPIO166 as EPWM8B

	// Config for conventional PWM first
	EPwm8Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// Set Immediate load
	EPwm8Regs.TBPRD = DAC1_TIMER_TBPRD; 		// period = 20us
	EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// up_count
	EPwm8Regs.TBCTL.bit.PHSEN = TB_DISABLE; 	// Do not synchronization
	EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set actions
	EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;         // Set PWM11A
	EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;   // No action
	EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // Clear PWM1A on event A, up count
	EPwm8Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;   // No action
	EPwm8Regs.AQCTLB.bit.ZRO = AQ_SET;   		// Set PWM11B
	EPwm8Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;   // No action
	EPwm8Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;   // No action
	EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR;       // Clear PWM1B on event B, up count

	// Set Compare values
	EPwm8Regs.CMPA.half.CMPA = DAC1_MIN_CMPA;   // Set compare A value
	EPwm8Regs.CMPB.half.CMPB = DAC1_MIN_CMPB;   // Set Compare B value

	// Interrupt where we will change the Compare Values
	EPwm8Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm8Regs.ETSEL.bit.INTEN = 0;                // Enable INT
	EPwm8Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 3rd event

	EDIS;
}

void InitDAC2Gpio(void) //PWM DAC3-4 InitEPwm12Gpio
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
   	for reduced power consumption */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;    // Disable pull-up on GPIO157 (EPWM7A)
	GpioCtrlRegs.GPEPUD.bit.GPIO158 = 1;    // Disable pull-up on GPIO158 (EPWM7B)

	/* Configure EPWM-6 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;   // Configure GPIO157 as EPWM7A
	GpioCtrlRegs.GPEMUX2.bit.GPIO158 = 1;   // Configure GPIO158 as EPWM7B

	// Config for conventional PWM first
	EPwm7Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// Set Immediate load
	EPwm7Regs.TBPRD = DAC1_TIMER_TBPRD; 		// period = 20us
	EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// up_count
	EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE; 	// Do not synchronization
	EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set actions
	EPwm7Regs.AQCTLA.bit.ZRO = AQ_SET;         // Set PWM11A
	EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;   // No action
	EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // Clear PWM1A on event A, up count
	EPwm7Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;   // No action
	EPwm7Regs.AQCTLB.bit.ZRO = AQ_SET;   		// Set PWM11B
	EPwm7Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;   // No action
	EPwm7Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;   // No action
	EPwm7Regs.AQCTLB.bit.CBU = AQ_CLEAR;       // Clear PWM1B on event B, up count

	// Set Compare values
	EPwm7Regs.CMPA.half.CMPA = DAC1_MIN_CMPA;   // Set compare A value
	EPwm7Regs.CMPB.half.CMPB = DAC1_MIN_CMPB;   // Set Compare B value

	// Interrupt where we will change the Compare Values
	EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm7Regs.ETSEL.bit.INTEN = 0;                // Enable INT
	EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 3rd event

	EDIS;
}
#ifdef __FLASH_PROGRAM
#pragma CODE_SECTION(Updata_DACValue, "ramfuncs");
#endif
void Updata_DACValue(void) //PWM DAC1-2 //InitEPwm7Gpio
{
    BOUND_VAL(gfDAC_Val_1, DAC1_MAX_CMPA, DAC1_MIN_CMPA)
    BOUND_VAL(gfDAC_Val_2, DAC1_MAX_CMPA, DAC1_MIN_CMPA)
    BOUND_VAL(gfDAC_Val_3, DAC1_MAX_CMPA, DAC1_MIN_CMPA)
    BOUND_VAL(gfDAC_Val_4, DAC1_MAX_CMPA, DAC1_MIN_CMPA)

    EPwm8Regs.CMPA.half.CMPA  = gfDAC_Val_1;   // Set compare A value
    EPwm8Regs.CMPB.half.CMPB  = gfDAC_Val_2;   // Set Compare B value
    EPwm7Regs.CMPA.half.CMPA  = gfDAC_Val_3;   // Set compare A value
    EPwm7Regs.CMPB.half.CMPB  = gfDAC_Val_4;   // Set Compare B value
}
