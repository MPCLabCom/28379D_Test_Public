//###########################################################################
//
// FILE:    Example_posspeed.h
//
// TITLE:   Pos/speed measurement using EQEP peripheral
//
// DESCRIPTION:
//
// Header file containing data type and object definitions and
// initializers.
//
//###########################################################################
// $TI Release: F2837xD Support Library v180 $
// $Release Date: Fri Nov  6 16:19:46 CST 2015 $
// $Copyright: Copyright (C) 2013-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __POSSPEED__
#define __POSSPEED__

/*-----------------------------------------------------------------------------
Define the structure of the POSSPEED Object
-----------------------------------------------------------------------------*/
typedef struct {int theta_elec;         // Output: Motor Electrical angle (Q15)
                int theta_mech;         // Output: Motor Mechanical Angle (Q15)
                int DirectionQep;       // Output: Motor rotation direction (Q0)
                int QEP_cnt_idx;        // Variable: Encoder counter index (Q0)
                int theta_raw;          // Variable: Raw angle from Timer 2 (Q0)
                int mech_scaler;        // Parameter: 0.9999/total count, total count = 4000 (Q26)
                int pole_pairs;         // Parameter: Number of pole pairs (Q0)
                int cal_angle;          // Parameter: Raw angular offset between encoder and phase a (Q0)
                int index_sync_flag;    // Output: Index sync status (Q0)

                Uint32 SpeedScaler;     // Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0) - independently with global Q
                _iq Speed_pr;           // Output :  speed in per-unit
                float BaseRpm;         // Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed - independently with global Q
                float SpeedRpm_pr;      // Output : speed in r.p.m. (Q0) - independently with global Q

                _iq  oldpos;            // Input: Electrical angle (pu)
                float Speed_fr;           // Output :  speed in per-unit
                float SpeedRpm_fr;      // Output : Speed in rpm  (Q0) - independently with global Q
}  POSSPEED;

/*-----------------------------------------------------------------------------
Define a POSSPEED_handle
-----------------------------------------------------------------------------*/
typedef POSSPEED *POSSPEED_handle;

/*-----------------------------------------------------------------------------
Default initializer for the POSSPEED Object.
-----------------------------------------------------------------------------*/
// Applied-motion PMSM motor: 6-pole, 1000 line encoder, CalibratedAngle = 0
// MechScaler = 1/4000
 #define POSSPEED_DEFAULTS {0x0, 0x0,0x0,0x0,0x0,16776,3,891,0x0,\
        250,0,6000,0,\
        0,0,0,}

//SPM Dyanamo Motor  1.3kW 8.3Nm 8Pole, 8192 = 2^13
#define SPM_DYANAMO_QEP_DEFAULTS { 0x0, 0x0,0x0,0x0,0x0,2797,4,4725,0x0,  \
    250,0,6000,0,\
           0,0,0,}

// Applied-motion PMSM motor: 8-pole, 6000 line encoder, CalibratedAngle = 0
//SPM 0.3kW 3.0Nm
#define SPM_TEST_QEP_DEFAULTS { 0x0, 0x0,0x0,0x0,0x0,_IQ30(4.166666666666667e-5),4,9025,0x0,  \
        250,0,6000,0,\
               0,0,0,}

//#define QEP_DEFAULTS { 0x0, 0x0,0x0,0x0,0x0,_IQ30(0.00025),1000,3,435,0x0,  \


/*-----------------------------------------------------------------------------
Prototypes for the functions in posspeed.c
-----------------------------------------------------------------------------*/
void POSSPEED_Init(void);
void POSSPEED_Calc(POSSPEED_handle);

#endif /*  __POSSPEED__ */

