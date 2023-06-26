//###########################################################################
// FILE:   F2837xD_Adc.c
// TITLE:  F2837xD Adc Support Functions.
//###########################################################################
// $TI Release: F2837xD Support Library v190 $
// $Release Date: Mon Feb  1 16:51:57 CST 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xD_device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File
#include "userparms.h"

#define	  PPBSOC0 		0
#define	  PPBSOC1 		1
#define	  PPBSOC2 		2
#define	  PPBSOC3 		3
#define	  PPBSOC4 		4
#define	  PPBSOC5 		5
#define	  PPBSOC6 		6
#define	  PPBSOC7 		7
#define	  PPBSOC8 		8
#define	  PPBSOC9 		9
#define	  PPBSOC10 		10
#define	  PPBSOC11 		11
#define	  PPBSOC12 		12
#define	  PPBSOC13 		13
#define	  PPBSOC14 		14
#define	  PPBSOC15 		15
/* 
* Set the resolution and signalmode for a given ADC. This will ensure that
* the correct trim is loaded. 
*/
void InitADC(void)
{
	EALLOW;

	//write configurations
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
#ifdef	_16BIT_ADC
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL); // set ADC-A resolution
#endif
#ifndef	_16BIT_ADC
	AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); // set ADC-A resolution
#endif
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; 	//Set pulse positions to late
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; 	    //power up the ADC

	AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
#ifdef	_16BIT_ADC
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL); // set ADC-B resolution
#endif
#ifndef	_16BIT_ADC
	AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); // set ADC-B resolution
#endif
	AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1; 	//Set pulse positions to late
	AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1; 	//power up the ADC

	AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
#ifdef	_16BIT_ADC
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL); // set ADC-C resolution
#endif
#ifndef	_16BIT_ADC
	AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); // set ADC-C resolution
#endif
	AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1; 	//Set pulse positions to late
	AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1; 	//power up the ADC

	AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    //AdcSetMode(ADC_ADCD, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL); // set ADC-D resolution
	AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); // set ADC-D resolution
	AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1; 	//Set pulse positions to late
	AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1; 	//power up the ADC

	//delay for 1ms to allow ADC time to power up
	DELAY_US(1000);
/*
	//========  ADC-A : Sequence, Sampling Window, SOC Initialzation  ========//
	//MODULE1 interrupt
	AdcaRegs.ADCSOC0CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L1_P
	AdcaRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC1CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_IN_P
	AdcaRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC1CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC2CTL.bit.CHSEL  = 1;  //SOC will convert on ADC_V_MC_P
	AdcaRegs.ADCSOC2CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC2CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC3CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT1A
	AdcaRegs.ADCSOC3CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC3CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM10 SOCA
	//MODULE2 interrupt
	AdcaRegs.ADCSOC4CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L1_P
	AdcaRegs.ADCSOC4CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC4CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC5CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_IN_P
	AdcaRegs.ADCSOC5CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC5CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC6CTL.bit.CHSEL  = 1;  //SOC will convert on ADC_V_MC_P
	AdcaRegs.ADCSOC6CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC6CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC7CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT1A
	AdcaRegs.ADCSOC7CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC7CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM10 SOCA
	//MODULE3 interrupt
	AdcaRegs.ADCSOC8CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L1_P
	AdcaRegs.ADCSOC8CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC8CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC9CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_IN_P
	AdcaRegs.ADCSOC9CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC9CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC10CTL.bit.CHSEL  = 1;  //SOC will convert on ADC_V_MC_P
	AdcaRegs.ADCSOC10CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC10CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM10 SOCA
	AdcaRegs.ADCSOC11CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT1A
	AdcaRegs.ADCSOC11CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcaRegs.ADCSOC11CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM10 SOCA

	//========  ADC-B : Sequence, Sampling Window, SOC Initialzation  ========//
	//MODULE1 interrupt
	AdcbRegs.ADCSOC0CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC0CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC1CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC1CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC2CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC2CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC2CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC3CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC3CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC3CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM8 SOCA
	//MODULE2 interrupt
	AdcbRegs.ADCSOC4CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC4CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC4CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC5CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC5CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC5CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC6CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC6CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC6CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC7CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC7CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC7CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM8 SOCA
	//MODULE3 interrupt
	AdcbRegs.ADCSOC8CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC8CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC8CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC9CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC9CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC9CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC10CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC10CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC10CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM8 SOCA
	AdcbRegs.ADCSOC11CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT2A
	AdcbRegs.ADCSOC11CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC11CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM8 SOCA

	//========  ADC-C : Sequence, Sampling Window, SOC Initialzation  ========//
	//MODULE1 interrupt
	AdccRegs.ADCSOC0CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC0CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC1CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC1CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC2CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC2CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC2CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC3CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC3CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC3CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM2 SOCA

	//MODULE2 interrupt
	AdccRegs.ADCSOC4CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC4CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC4CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC5CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC5CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC5CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC6CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC6CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC6CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC7CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC7CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC7CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM2 SOCA

	//MODULE3 interrupt
	AdccRegs.ADCSOC8CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC8CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC8CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC9CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC9CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC9CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC10CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdccRegs.ADCSOC10CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC10CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM2 SOCA
	AdccRegs.ADCSOC11CTL.bit.CHSEL  = 4;  //SOC will convert on ADC_T_IGBT3A
	AdccRegs.ADCSOC11CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC11CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM2 SOCA


	//========  ADC-D : Sequence, Sampling Window, SOC Initialzation  ========//
	//MODULE1 interrupt
	AdcdRegs.ADCSOC0CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_OUT_P
	AdcdRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcdRegs.ADCSOC0CTL.bit.TRIGSEL =23; //SOC5 will begin conversion on ePWM4 SOCA
	//MODULE2 interrupt
	AdcdRegs.ADCSOC1CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_OUT_P
	AdcdRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcdRegs.ADCSOC1CTL.bit.TRIGSEL =19; //SOC5 will begin conversion on ePWM4 SOCA
	//MODULE3 interrupt
	AdcdRegs.ADCSOC2CTL.bit.CHSEL  = 0;  //SOC will convert on ADC_V_OUT_P
	AdcdRegs.ADCSOC2CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 7; //SOC5 will begin conversion on ePWM4 SOCA


	SOC Burst Trigger Source Select. Configures which trigger will start
	a burst conversion sequence.
	00h BURSTTRIG0 - Software only
	01h BURSTTRIG1 - CPU1 Timer 0, TINT0n
	02h BURSTTRIG2 - CPU1 Timer 1, TINT1n
	03h BURSTTRIG3 - CPU1 Timer 2, TINT2n
	04h BURSTTRIG4 - GPIO, Input X-Bar INPUT5
	05h BURSTTRIG5 - ePWM1, ADCSOCA
	06h BURSTTRIG6 - ePWM1, ADCSOCB
	07h BURSTTRIG7 - ePWM2, ADCSOCA
	08h BURSTTRIG8 - ePWM2, ADCSOCB
	09h BURSTTRIG9 - ePWM3, ADCSOCA
	0Ah BURSTTRIG10 - ePWM3, ADCSOCB
	0Bh BURSTTRIG11 - ePWM4, ADCSOCA
	0Ch BURSTTRIG12 - ePWM4, ADCSOCB
	0Dh BURSTTRIG13 - ePWM5, ADCSOCA
	0Eh BURSTTRIG14 - ePWM5, ADCSOCB
	0Fh BURSTTRIG15 - ePWM6, ADCSOCA
	10h BURSTTRIG16 - ePWM6, ADCSOCB
	11h BURSTTRIG17 - ePWM7, ADCSOCA
	12h BURSTTRIG18 - ePWM7, ADCSOCB
	13h BURSTTRIG19 - ePWM8, ADCSOCA
	14h BURSTTRIG20 - ePWM8, ADCSOCB
	15h BURSTTRIG21 - ePWM9, ADCSOCA
	16h BURSTTRIG22 - ePWM9, ADCSOCB
	17h BURSTTRIG23 - ePWM10, ADCSOCA
	18h BURSTTRIG24 - ePWM10, ADCSOCB
	19h BURSTTRIG25 - ePWM11, ADCSOCA
	1Ah BURSTTRIG26 - ePWM11, ADCSOCB
	1Bh BURSTTRIG27 - ePWM12, ADCSOCA
	1Ch BURSTTRIG28 - ePWM12, ADCSOCB
	1Dh BURSTTRIG29 - CPU2 Timer 0, TINT0n
	1Eh BURSTTRIG30 - CPU2 Timer 1, TINT1n
	1Fh BURSTTRIG31 - CPU2 Timer 2, TINT2n
	 */

	// ADC-A
	AdcaRegs.ADCSOC0CTL.bit.CHSEL  = 2;
	AdcaRegs.ADCSOC0CTL.bit.ACQPS  = 15;
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL= 0x05;
	AdcaRegs.ADCSOC1CTL.bit.CHSEL  = 3;
	AdcaRegs.ADCSOC1CTL.bit.ACQPS  = 15;
	AdcaRegs.ADCSOC1CTL.bit.TRIGSEL= 0x05;
	AdcaRegs.ADCSOC2CTL.bit.CHSEL  = 0;
	AdcaRegs.ADCSOC2CTL.bit.ACQPS  = 15;
	AdcaRegs.ADCSOC2CTL.bit.TRIGSEL= 0x05;

	// ADC-B
	AdcbRegs.ADCSOC0CTL.bit.CHSEL  = 2;  //SOC will convert ADCINA0 ( ADC_E2_i)
	AdcbRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC0CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA
	AdcbRegs.ADCSOC1CTL.bit.CHSEL  = 3;  //SOC will convert ADCINA1 ( ADC_E5_i)
	AdcbRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC1CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA
	AdcbRegs.ADCSOC2CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L2_P
	AdcbRegs.ADCSOC2CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcbRegs.ADCSOC2CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA

	// ADC-C
	AdccRegs.ADCSOC0CTL.bit.CHSEL  = 2;  //SOC will convert on ADC_I_L3_P
	AdccRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC0CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA
	AdccRegs.ADCSOC1CTL.bit.CHSEL  = 3;  //SOC will convert on ADC_AIN_V1
	AdccRegs.ADCSOC1CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdccRegs.ADCSOC1CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA

	// ADC-D
	AdcdRegs.ADCSOC0CTL.bit.CHSEL  = 14;  //SOC will convert on ADC_V_OUT_P
	AdcdRegs.ADCSOC0CTL.bit.ACQPS  = 15;  //SOC will use sample duration of 20 SYSCLK cycles
	AdcdRegs.ADCSOC0CTL.bit.TRIGSEL= 0x05; //SOC5 will begin conversion on ePWM1 SOCA

	//========  ADC Interrupt Initialzation  ========//
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 2;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

	EDIS;
}


void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode)
{
	Uint16 adcOffsetTrimOTPIndex; //index into OTP table of ADC offset trims
	Uint16 adcOffsetTrim; //temporary ADC offset trim
	
	//re-populate INL trim
	CalAdcINL(adc);
	
	if(0xFFFF != *((Uint16*)GetAdcOffsetTrimOTP)){
		//offset trim function is programmed into OTP, so call it

		//calculate the index into OTP table of offset trims and call
		//function to return the correct offset trim
		adcOffsetTrimOTPIndex = 4*adc + 2*resolution + 1*signalmode;
		adcOffsetTrim = (*GetAdcOffsetTrimOTP)(adcOffsetTrimOTPIndex);
	}
	else {
		//offset trim function is not populated, so set offset trim to 0
		adcOffsetTrim = 0;
	}

	//Apply the resolution and signalmode to the specified ADC.
	//Also apply the offset trim and, if needed, linearity trim correction.
	switch(adc){
		case ADC_ADCA:
			AdcaRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCB:
			AdcbRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCC:
			AdccRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCD:
			AdcdRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
	}
}

/* 
* Loads INL trim values from OTP into the trim registers of the specified ADC.
* Use only as part of AdcSetMode function, since linearity trim correction
* is needed for some modes.
*/
void CalAdcINL(Uint16 adc)
{
	switch(adc){
		case ADC_ADCA:
			if(0xFFFF != *((Uint16*)CalAdcaINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcaINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCB:
			if(0xFFFF != *((Uint16*)CalAdcbINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcbINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCC:
			if(0xFFFF != *((Uint16*)CalAdccINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdccINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCD:
			if(0xFFFF != *((Uint16*)CalAdcdINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcdINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
	}
}
