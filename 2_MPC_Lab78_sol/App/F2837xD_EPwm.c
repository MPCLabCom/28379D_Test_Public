//###########################################################################
//
// FILE:   F2837xD_EPwm.c
//
// TITLE:  F2837xD EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v190 $
// $Release Date: Mon Feb  1 16:51:57 CST 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
/* ================================================================================
 History:
--------------------------------------------------------------------------------
 04-06-2016	Version 0.1   Modified For PWM Converter
 06-12-2016 Version 0.2   Modified Dead time 2.5usec - > 3usec
================================================================================*/

#include "F2837xD_device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File
#include "userparms.h"

void InitEPwmGpio(void)
{
	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // It is important role. It should be do it
	EDIS;

	// enable PWM1 ~ PWM 3
	EALLOW;
	CpuSysRegs.PCLKCR2.bit.EPWM1  = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM2  = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM3  = 1;

    /* Setup GPIO */
    GpioCtrlRegs.GPAPUD.bit.GPIO0   = 1; //PullDown
    GpioCtrlRegs.GPAPUD.bit.GPIO1   = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO2   = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO3   = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO4   = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO5   = 1;

    /* Configure EPWM-1 pins using GPIO regs*/
    // This specifies which of the possible GPIO pins will be EPWM1 functional pins.
    // Comment out other unwanted lines.
    GpioCtrlRegs.GPAMUX1.bit.GPIO0   = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1   = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2   = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3   = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4   = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5   = 1;

    /* Setup TBCLK */
    EPwm1Regs.TBPRD = (TBCLK / PWMCARRIER) / 2; /* Set Timer Period */ //20000 (5KHz)
    EPwm1Regs.TBCTR = 0; /* Clear Counter */
    EPwm2Regs.TBPRD = (TBCLK / PWMCARRIER) / 2; /* Set Timer Period */
    EPwm2Regs.TBCTR = 0; /* Clear Counter */
    EPwm3Regs.TBPRD = (TBCLK / PWMCARRIER) / 2; /* Set Timer Period */
    EPwm3Regs.TBCTR = 0; /* Clear Counter */

    /* Set Compare values */
    EPwm1Regs.CMPA.half.CMPA = (TBCLK / PWMCARRIER) / 4; /* Set Compare A value to min*/
    EPwm2Regs.CMPA.half.CMPA = (TBCLK / PWMCARRIER) / 4; /* Set Compare A value to min */
    EPwm3Regs.CMPA.half.CMPA = (TBCLK / PWMCARRIER) / 4; /* Set Compare A value to min */

    /* SYNCSELECT */
    SyncSocRegs.SYNCSELECT.all = 0x00000000; //Sync Input and Output Select Register

    /* Setup counter mode */
    /* Master 1 */
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN; /* Count Up/Down (Symmetric) */
    EPwm1Regs.TBPHS.half.TBPHS      = TB_DISABLE; /* Phase is 0 */
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE; /* Master module, Disable phase loading */
    EPwm1Regs.TBCTL.bit.SYNCOSEL    = TB_CTR_ZERO; /* Sync down-stream module */
    EPwm1Regs.TBCTL.bit.PRDLD       = 0; /* Period Register is loaded from its shadow when CNTR=Zero */
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1; /* Clock ratio to SYSCLKOUT */
    EPwm1Regs.TBCTL.bit.CLKDIV      = TB_DIV1; /* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

    /* Slave 1-1 */
    EPwm2Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN; /* Count Up/Down (Symmetric) */
    EPwm2Regs.TBPHS.half.TBPHS      = TB_DISABLE; /* disable*/
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE; /* Slave module1, Enable phase loading */
    EPwm2Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN; /* Sync flow-through */
    EPwm2Regs.TBCTL.bit.PHSDIR      = 1; /* Count-down on sync () */
    EPwm2Regs.TBCTL.bit.PRDLD       = 0; /* Period Register is loaded from its shadow when CNTR=Zero */
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1; /* Clock ratio to SYSCLKOUT */
    EPwm2Regs.TBCTL.bit.CLKDIV      = TB_DIV1; /* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

    /* Slave 1-2 */
    EPwm3Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN; /* Count Up/Down (Symmetric) */
    EPwm3Regs.TBPHS.half.TBPHS      = TB_DISABLE; /* disable*/
    EPwm3Regs.TBCTL.bit.PHSEN       = TB_ENABLE; /* Slave module2, Enable phase loading */
    EPwm3Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN; /* Sync flow-through */
    EPwm3Regs.TBCTL.bit.PHSDIR      = 1; /* PHSDIR bit indicates the direction the time-base counter (TBCTR) will count after a synchronization */
    EPwm3Regs.TBCTL.bit.PRDLD       = 0; /* Period Register is loaded from its shadow when CNTR=Zero */
    EPwm3Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1; /* Clock ratio to SYSCLKOUT */
    EPwm3Regs.TBCTL.bit.CLKDIV      = TB_DIV1; /* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

	/* Setup shadowing */
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;						/* Enable Shadowing */
	EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;						/* Load on CNTR=Zero */
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;						/* Enable Shadowing */
	EPwm2Regs.CMPCTL.bit.LOADAMODE = 0;						/* Load on CNTR=Zero */
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0;						/* Enable Shadowing */
	EPwm3Regs.CMPCTL.bit.LOADAMODE = 0;						/* Load on CNTR=Zero */

	/* Set actions */ //Active High Code
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output A
	EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output A
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Action When TBCTR = CMPA on Up Count  For Output A
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;           // Action When TBCTR = CMPA on Down Count For Output A
	EPwm1Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output A
	EPwm1Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output A

	EPwm1Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output B
	EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output B
	EPwm1Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm1Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B
	EPwm1Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm1Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B

	EPwm1Regs.AQCTLA2.all = 0x0000;
	EPwm1Regs.AQCTLB2.all = 0x0000;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output A
	EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output A
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Action When TBCTR = CMPA on Up Count  For Output A
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;           // Action When TBCTR = CMPA on Down Count For Output A
	EPwm2Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output A
	EPwm2Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output A

	EPwm2Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output B
	EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output B
	EPwm2Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm2Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B
	EPwm2Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm2Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B

	EPwm2Regs.AQCTLA2.all = 0x0000;
	EPwm2Regs.AQCTLB2.all = 0x0000;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output A
	EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output A
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Action When TBCTR = CMPA on Up Count  For Output A
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;           // Action When TBCTR = CMPA on Down Count For Output A
	EPwm3Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output A
	EPwm3Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output A

	EPwm3Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;     // Action When TBCTR = 0 For Output B
	EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // Action When TBCTR = TBPRD For Output B
	EPwm3Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm3Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B
	EPwm3Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Up Count For Output B
	EPwm3Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;     // Action When TBCTR = CMPB on Down Count For Output B

	EPwm3Regs.AQCTLA2.all = 0x0000;
	EPwm3Regs.AQCTLB2.all = 0x0000;

	/* Set Dead-time */
	EPwm1Regs.DBCTL.bit.IN_MODE     = DBA_ALL;			/* EPWMxA is the source for both falling-edge & rising-edge delay */
	EPwm1Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;	/* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
	EPwm1Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;		/* Active high complementary (AHC). EPWMxB is inverted.*/
	EPwm1Regs.DBCTL.bit.OUTSWAP     = DB_NO_SWAP;
	EPwm1Regs.DBFED                 = 400;//500;		/* 2usec  4/2 =2.0us */
	EPwm1Regs.DBRED                 = 400;				/* 2usec */

	EPwm2Regs.DBCTL.bit.IN_MODE  = DBA_ALL;			/* EPWMxA is the source for both falling-edge & rising-edge delay */
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	/* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
	EPwm2Regs.DBCTL.bit.POLSEL =  DB_ACTV_HIC;		/* Active high complementary (AHC). EPWMxB is inverted.*/
    EPwm2Regs.DBCTL.bit.OUTSWAP     = DB_NO_SWAP;
	EPwm2Regs.DBFED = 400;							/* 3usec */
	EPwm2Regs.DBRED = 400;							/* 3usec */

	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;			/* EPWMxA is the source for both falling-edge & rising-edge delay */
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	/* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;		/* Active high complementary (AHC). EPWMxB is inverted.*/
    EPwm3Regs.DBCTL.bit.OUTSWAP     = DB_NO_SWAP;
	EPwm3Regs.DBFED = 400;							/* 3usec */
	EPwm3Regs.DBRED = 400;							/* 35usec */

	// Interrupt where we will change the Compare Values
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on Zero event
	EPwm1Regs.ETSEL.bit.INTEN = 0;                  // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;             // Generate INT on 3rd event

	// ADC SETTING
	EPwm1Regs.ETSEL.bit.SOCAEN	= 1;	            // SOCA 이벤트 트리거 Enable
    EPwm1Regs.ETSEL.bit.SOCASEL   = ET_CTR_PRD;   // SCCA 트리거 조건 : TOP
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다
    EDIS;

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
	EDIS;

}

void InitEPwm1Gpio(void) //PWM_3B
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPEPUD.bit.GPIO145 = 1;    // Disable pull-up on GPIO145 (EPWM1A)
   GpioCtrlRegs.GPEPUD.bit.GPIO146 = 1;    // Disable pull-up on GPIO146 (EPWM1B)


/* Configure EPWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
//  GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
	GpioCtrlRegs.GPEMUX2.bit.GPIO145 = 1;   // Configure GPIO145 as EPWM1A
	GpioCtrlRegs.GPEMUX2.bit.GPIO146 = 1;   // Configure GPIO0146 as EPWM1B

#ifdef PWM_CONV
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Count up

#endif
#ifndef PWM_CONV
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Count up
#endif
   // Setup TBCLK
   //EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;      		// Set timer period
   EPwm1Regs.TBPRD = (TBCLK/PWMCARRIER)/2;      	// Set timer period
   EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;    		// Disable phase loading
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;       		// Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                 		 // Clear counter
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   		// Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadow register load on ZERO
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set Compare values
   EPwm1Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
   EPwm1Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

   EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	// No action
   EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;           // Set PWM1B on Zero
   EPwm1Regs.AQCTLA.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

  // Set actions
   EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
   EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
   EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
   EPwm1Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // No action

   // Interrupt where we will change the Compare Values
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event


   // ADC SETTING
//	EPwm1Regs.ETSEL.bit.SOCAEN	= 1;	        // SOCA 이벤트 트리거 Enable
//	EPwm1Regs.ETSEL.bit.SOCASEL	= 4;	        // SCCA 트리거 조건 : 카운터==CMPA when Counter is increasing
//	EPwm1Regs.ETPS.bit.SOCAPRD = 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다

    EDIS;
}

void InitEPwm2Gpio(void) //PWM_3A
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)
   GpioCtrlRegs.GPEPUD.bit.GPIO147 = 1;    // Disable pull-up on GPIO147 (EPWM2A)
   GpioCtrlRegs.GPEPUD.bit.GPIO148 = 1;    // Disable pull-up on GPIO148 (EPWM2B)

/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
//    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   GpioCtrlRegs.GPEMUX2.bit.GPIO147 = 1;   // Configure GPIO147 as EPWM2A
   GpioCtrlRegs.GPEMUX2.bit.GPIO148 = 1;   // Configure GPIO148 as EPWM2B


   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
   EPwm2Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;       // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadow register load on ZERO
   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set Compare values
   EPwm2Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
   EPwm2Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

   // Set actions
   EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
   EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
   EPwm2Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // No action

   EPwm2Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;    	// No action
   EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
   EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;           // Set PWM1B on Zero
   EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count


   // Interrupt where we will change the Compare Values
   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

   // ADC SETTING
   EPwm2Regs.ETSEL.bit.SOCAEN	= 1;	        // SOCA 이벤트 트리거 Enable
   EPwm2Regs.ETSEL.bit.SOCASEL	= 4;	        // SCCA 트리거 조건 : 카운터==CMPA when Counter is increasing
   EPwm2Regs.ETPS.bit.SOCAPRD = 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다

   // Active Low PWMs - Setup Deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm2Regs.DBCTL.bit.LOADREDMODE = 0;
   EPwm2Regs.DBCTL.bit.LOADFEDMODE = 0;
   EPwm2Regs.DBRED = 200;
   EPwm2Regs.DBFED = 200;


   EDIS;
}

void InitEPwm3Gpio(void) //PWM_4B
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
//  GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)
 	GpioCtrlRegs.GPEPUD.bit.GPIO149 = 1;    // Disable pull-up on GPIO149 (EPWM3A)
 	GpioCtrlRegs.GPEPUD.bit.GPIO150 = 1;    // Disable pull-up on GPIO150 (EPWM3B)

/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

//	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
//	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	GpioCtrlRegs.GPEMUX2.bit.GPIO149 = 1;   // Configure GPIO149 as EPWM3A
	GpioCtrlRegs.GPEMUX2.bit.GPIO150 = 1;   // Configure GPIO150 as EPWM3B

	   // Setup TBCLK
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm3Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm3Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx1_3;    // Phase is 120deg
	EPwm3Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadow register load on ZERO
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	EPwm3Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm3Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

	// Set actions
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm3Regs.AQCTLA.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

   // Set actions
	EPwm3Regs.AQCTLB.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm3Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // No action

	   // Interrupt where we will change the Compare Values
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

	EDIS;
}

void InitEPwm4Gpio(void) //PWM_4A
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
//  GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)
 	GpioCtrlRegs.GPEPUD.bit.GPIO151 = 1;    // Disable pull-up on GPIO151 (EPWM4A)
 	GpioCtrlRegs.GPEPUD.bit.GPIO152 = 1;    // Disable pull-up on GPIO152 (EPWM4B)

/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
//  GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	GpioCtrlRegs.GPEMUX2.bit.GPIO151 = 1;   // Configure GPIO151 as EPWM4A
	GpioCtrlRegs.GPEMUX2.bit.GPIO152 = 1;   // Configure GPIO152 as EPWM4B

	   // Setup TBCLK
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm4Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm4Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx1_3;    // Phase is 120deg
	EPwm4Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadow register load on ZERO
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	EPwm4Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm4Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

   // Set actions
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm4Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm4Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // No action

	EPwm4Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm4Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm4Regs.AQCTLB.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count


	// Interrupt where we will change the Compare Values
	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

	   // ADC SETTING
	EPwm4Regs.ETSEL.bit.SOCAEN	= 1;	        // SOCA 이벤트 트리거 Enable
	EPwm4Regs.ETSEL.bit.SOCASEL	= 4;	        // SCCA 트리거 조건 : 카운터==CMPA when Counter is increasing
	EPwm4Regs.ETPS.bit.SOCAPRD = 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다


    EDIS;
}

void InitEPwm5Gpio(void) //NO USE
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO9 (EPWM5B)
// 	GpioCtrlRegs.GPEPUD.bit.GPIO153 = 1;    // Disable pull-up on GPIO153 (EPWM5A)
// 	GpioCtrlRegs.GPEPUD.bit.GPIO154 = 1;    // Disable pull-up on GPIO154 (EPWM5B)

/* Configure EPWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
//	GpioCtrlRegs.GPEMUX2.bit.GPIO153 = 1;   // Configure GPIO153 as EPWM5A
//	GpioCtrlRegs.GPEMUX2.bit.GPIO154 = 1;   // Configure GPIO0154 as EPWM5B

    EDIS;
}

void InitEPwm6Gpio(void) //AO
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)
// 	GpioCtrlRegs.GPEPUD.bit.GPIO155 = 1;    // Disable pull-up on GPIO155 (EPWM6A)
// 	GpioCtrlRegs.GPEPUD.bit.GPIO156 = 1;    // Disable pull-up on GPIO156 (EPWM6B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	//	GpioCtrlRegs.GPEMUX2.bit.GPIO155 = 1;   // Configure GPIO155 as EPWM6A
	//	GpioCtrlRegs.GPEMUX2.bit.GPIO156 = 1;   // Configure GPIO156 as EPWM6B

    EDIS;
}

void InitEPwm7Gpio(void) //PWM_2B
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;    // Disable pull-up on GPIO12 (EPWM7A)
//  GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;    // Disable pull-up on GPIO13 (EPWM7B)
 	GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;    // Disable pull-up on GPIO157 (EPWM7A)
 	GpioCtrlRegs.GPEPUD.bit.GPIO158 = 1;    // Disable pull-up on GPIO158 (EPWM7B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;   // Configure GPIO12 as EPWM7A
//  GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;   // Configure GPIO13 as EPWM7B
	GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;   // Configure GPIO157 as EPWM7A
	GpioCtrlRegs.GPEMUX2.bit.GPIO158 = 1;   // Configure GPIO158 as EPWM7B

	   // Setup TBCLK
	EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm7Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm7Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx2_3;    // Phase is 240deg
	EPwm7Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadow register load on ZERO
	EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	EPwm7Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm7Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

	// Set actions
	EPwm7Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm7Regs.AQCTLA.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm7Regs.AQCTLA.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

   // Set actions
	EPwm7Regs.AQCTLB.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm7Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm7Regs.AQCTLB.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm7Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // No action



	// Interrupt where we will change the Compare Values
	EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm7Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm7Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
/*
    // Active Low PWMs - Setup Deadband
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
    EPwm7Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm7Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm7Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm7Regs.DBRED.bit.DBRED = 200;
    EPwm7Regs.DBFED.bit.DBFED = 200;
*/
    EDIS;
}

void InitEPwm8Gpio(void) //PWM_2A
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;    // Disable pull-up on GPIO14 (EPWM8A)
//  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;    // Disable pull-up on GPIO15 (EPWM8B)
 	GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;    // Disable pull-up on GPIO159 (EPWM8A)
 	GpioCtrlRegs.GPFPUD.bit.GPIO160 = 1;    // Disable pull-up on GPIO160 (EPWM8B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;   // Configure GPIO14 as EPWM8A
//  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;   // Configure GPIO15 as EPWM8B
	GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;   // Configure GPIO159 as EPWM8A
	GpioCtrlRegs.GPFMUX1.bit.GPIO160 = 1;   // Configure GPIO160 as EPWM8B

	   // Setup TBCLK
	EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm8Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm8Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx2_3;    // Phase is 240deg
	EPwm8Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadow register load on ZERO
	EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   // Set Compare values
	EPwm8Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm8Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

	   // Set actions
	EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm8Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // No action

	EPwm8Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm8Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm8Regs.AQCTLB.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

	// Interrupt where we will change the Compare Values
	EPwm8Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm8Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm8Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

	   // ADC SETTING
	EPwm8Regs.ETSEL.bit.SOCAEN	= 1;	        // SOCA 이벤트 트리거 Enable
	EPwm8Regs.ETSEL.bit.SOCASEL	= 4;	        // SCCA 트리거 조건 : 카운터==CMPA when Counter is increasing
	EPwm8Regs.ETPS.bit.SOCAPRD = 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다
/*
    // Active Low PWMs - Setup Deadband
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
    EPwm8Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm8Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm8Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm8Regs.DBRED.bit.DBRED = 200;
    EPwm8Regs.DBFED.bit.DBFED = 200;
*/
    EDIS;
}

void InitEPwm9Gpio(void) //PWM_1B
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFPUD.bit.GPIO161 = 1;    // Disable pull-up on GPIO161 (EPWM9A)
    GpioCtrlRegs.GPFPUD.bit.GPIO162 = 1;    // Disable pull-up on GPIO162 (EPWM9B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPFMUX1.bit.GPIO161 = 1;   // Configure GPIO161 as EPWM9A
	GpioCtrlRegs.GPFMUX1.bit.GPIO162 = 1;   // Configure GPIO162 as EPWM9B

   // Setup TBCLK
	EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm9Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm9Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm9Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx1_3;    // Phase is 0
	EPwm9Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm9Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm9Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   // Setup shadow register load on ZERO
	EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm9Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm9Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm9Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

	// Set actions
	EPwm9Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm9Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm9Regs.AQCTLA.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm9Regs.AQCTLA.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

	// Set actions
	EPwm9Regs.AQCTLB.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm9Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm9Regs.AQCTLB.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm9Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;     // No action


	// Interrupt where we will change the Compare Values
	EPwm9Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm9Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm9Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
/*
    // Active Low PWMs - Setup Deadband
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
    EPwm9Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm9Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm9Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm9Regs.DBRED.bit.DBRED = 200;
    EPwm9Regs.DBFED.bit.DBFED = 200;
*/
    EDIS;
}

void InitEPwm10Gpio(void) //PWM_1A
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFPUD.bit.GPIO163 = 1;    // Disable pull-up on GPIO163 (EPWM10A)
    GpioCtrlRegs.GPFPUD.bit.GPIO164 = 1;    // Disable pull-up on GPIO164 (EPWM10B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFMUX1.bit.GPIO163 = 1;   // Configure GPIO163 as EPWM10A
    GpioCtrlRegs.GPFMUX1.bit.GPIO164 = 1;   // Configure GPIO164 as EPWM10B

    // Setup TBCLK
	EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm10Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
	EPwm10Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Disable phase loading
	EPwm10Regs.TBPHS.half.TBPHS = EPWM1_TIMER_TBPRDx1_3;    // Phase is 0
	EPwm10Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm10Regs.CMPA.half.CMPA = EPWM1_MIN_CMPA;   // Set compare A value
	EPwm10Regs.CMPB.half.CMPB = EPWM1_MIN_CMPB;   // Set Compare B value

	// Set actions
	EPwm10Regs.AQCTLA.bit.ZRO = AQ_SET;         	// Set PWM1A on Zero
	EPwm10Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Set PWM1A on Zero
	EPwm10Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;     // No action

	EPwm10Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;    	// No action
	EPwm10Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;     // No action
	EPwm10Regs.AQCTLB.bit.CAU = AQ_SET;           // Set PWM1B on Zero
	EPwm10Regs.AQCTLB.bit.CBU = AQ_CLEAR;         // Clear PWM1B on event B, up count

	// Interrupt where we will change the Compare Values
	EPwm10Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm10Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm10Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

	// ADC SETTING
	EPwm10Regs.ETSEL.bit.SOCAEN= 1;	        // SOCA 이벤트 트리거 Enable
	EPwm10Regs.ETSEL.bit.SOCASEL= 4;	        // SCCA 트리거 조건 : 카운터==CMPA when Counter is increasing
	EPwm10Regs.ETPS.bit.SOCAPRD= 1;		        // SOCA 이벤트 분주 설정 : 트리거 조건 한번 마다
/*
    // Active Low PWMs - Setup Deadband
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
    EPwm10Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm10Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm10Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm10Regs.DBRED.bit.DBRED = 200;
    EPwm10Regs.DBFED.bit.DBFED = 200;
*/
    EDIS;
}

void InitEPwm11Gpio(void) //PWM DAC1-2
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFPUD.bit.GPIO165 = 1;    // Disable pull-up on GPIO165 (EPWM11A)
    GpioCtrlRegs.GPFPUD.bit.GPIO166 = 1;    // Disable pull-up on GPIO166 (EPWM11B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFMUX1.bit.GPIO165 = 1;   // Configure GPIO165 as EPWM11A
    GpioCtrlRegs.GPFMUX1.bit.GPIO166 = 1;   // Configure GPIO166 as EPWM11B

    EDIS;
}

void InitEPwm12Gpio(void) //PWM DAC3-4
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFPUD.bit.GPIO167 = 1;    // Disable pull-up on GPIO167 (EPWM12A)
    GpioCtrlRegs.GPFPUD.bit.GPIO168 = 1;    // Disable pull-up on GPIO168 (EPWM12B)

/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPFMUX1.bit.GPIO167 = 1;   // Configure GPIO167 as EPWM12A
    GpioCtrlRegs.GPFMUX1.bit.GPIO168 = 1;   // Configure GPIO168 as EPWM12B

    EDIS;
}
