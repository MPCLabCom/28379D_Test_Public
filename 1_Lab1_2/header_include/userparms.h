
/*==========================================================================
System Name:  	EPT
File Name:		USERPARMS.H
Description:	Parameter & Math constants
Originator:		CMD Lab.@POSTECH
Application:    AC/DC Converter(PWM Converter)

Date:			02/09/2007  440VLL -> Changed
=============================================================================*/

#ifndef USERPARMS_H
#define USERPARMS_H

//EPWM parameters
#define	SYSCLK		200E6	/* 200MHz */
#define	TBCLK		200E6	/* 200MHz */

#define	_5KHZ_PWM

/* Linker Command Mode Selection */
//#define     __FLASH_PROGRAM
//PWM frequency
//===========================================================================

#define	PWMCARRIER			5000		/* 5000Hz */
#define PWM_FREQ 			10000        //5kHz
#define	SPD_FREQ			1000		//1kHz
#define PWM_PERIOD 			0.0001		//1/10000
#define	PWM_TSMP			0.0001  	//1/10000
#define	SPD_TSMP			0.001	   	//1/10000*10
#define SPD_PRESCALE        9           //10
#define	TIME_DIV_1ms		10
#define	TIME_DIV_2ms		20
#define	TIME_DIV_10ms		100
#define	TIME_DIV_100ms		1000
#define	TIME_DIV_1s			10000
#define TMAX_EPWM			20000       //SYSCLK/TBCLK/2
#define TMAX_EPWM_HALF		10000       //SYSCLK/TBCLK/2


// General constants
//===========================================================================
#define 	FALSE 		0
#define		RESET 		0
#define 	CLEAR		0
#define 	TRUE		1
#define		SET			1

// Math constants
//===========================================================================
#define PI 			3.14159265358979
#define	PI_2		1.57079632679
#define	_2PI		6.28318530718
#define	_2PI_12_	75.39822368616 //=> 360/75.39822368616
#define	_PI_12_		37.69911184308 //=> 360/75.39822368616
#define PI2_3 		4.71238898037

#define	OMEGA_TO_RPM	9.549296586 //60/2/pi
#define	RPM_TO_OMEGA	0.10471975512 //60/2/pi
#define	DEG_TO_RAD		0.01745329251994329576923690768489 //60/2/pi

#define	SQRT3		    1.7320508
#define SQRT3_DIV_2     0.866025404
#define	_1_SQRT3	    0.57735026919
#define	_2_SQRT3	    1.15470053838
#define _2_OVER3        0.66666666667
#define _1_SQRT2	    0.707106781
#define _SQRT2_3	    0.47140452
#define	_1_OVER3	    0.33333333333

#define getbit(x,y) 		((x)>>(y) & (0x1))
#define setbit(x,y) 		(x)|=((0x1)<<(y))
#define clrbit(x,y) 		(x)&=~((0x1)<<(y))
#define clrbit_no(x,y) 		(x)&(~((0x1)<<(y)))


#define POLE_PAIR2           4.0
#define _1_DIV_PP           0.25

/*======================================================================
			GPIO Define
======================================================================*/
#define 	PWM_EN 				GpioDataRegs.GPDCLEAR.bit.GPIO124 //GpioDataRegs.GPCDAT.bit.GPIO67
#define 	PWM_DIS 			GpioDataRegs.GPDSET.bit.GPIO124
#define 	RED_LED_TOGG		GpioDataRegs.GPBTOGGLE.bit.GPIO41


// Fault and EMG_Trip_Value
#define		OC_CUR_EMG_TRIP						2.5		//756.6749665 	// Irated = 152A =>  152*sqrt(2) = 215A => 215*1.2 = 258A =>258*1.2 = 309.6
#define		OC_CUR_FAULT_TRIP					4.0		//861.2560595 	// I_a_Gain * 2048 = 500A

#define		OV_DCLINK_VOL_EMG_TRIP				35.0		//700.0    // 650 * 1.12 = 694
#define		OV_DCLINK_VOL_FAULT_TRIP			38.0		//790.0    // 650 * 1.28 = 793 Max voltage = V_dc_Gain *4098 = 814.030848

#define		LV_DCLINK_VOL_EMG_TRIP				1.2		//520.0    // 380*1.35 = 513
#define		LV_DCLINK_VOL_FAULT_TRIP			0.5  		//500.0    // Max voltage = V_dc_Gain *4098 = 814.030848

#define		LV_DCLINK_VOL_EMG_TRIP_PWMON		10.2		//520.0    // 380*1.35 = 513
#define		LV_DCLINK_VOL_FAULT_TRIP_PWMON		8.0	    	//500.0    // Max voltage = V_dc_Gain *4098 = 814.030848

#define		ZC_CUR_EMG_TRIP						1.0    	 //86.7  //50.0    // Irated = 152A =>  152*sqrt(2) = 215A => 215A*0.2 = 43A
#define		ZC_CUR_FAULT_TRIP					2.0  //169.7056275	 //100.0 //80.25   // Irated = 152A =>  152*sqrt(2) = 215A => 215A*0.3 = 75.25A

#define		OV_SPD_EMG_TRIP						2300.0		//520.0    // 380*1.35 = 513
#define		OV_SPD_FAULT_TRIP					2500.0  	//500.0    // Max voltage = V_dc_Gain *4098 = 814.030848


#endif

//===========================================================================
// No more.
//===========================================================================
