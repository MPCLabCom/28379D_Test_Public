
/* ==========================================================================
System Name: 	EPT

File Name:		USERDEFINES.H

Description:	Parameter & Math constants
          		
Originator:
================================================================================
 History:
--------------------------------------------------------------------------------
 04-15-2005	Version 0.1
================================================================================*/
#ifndef USERDEFINES_H
#define USERDEFINES_H

/* Linker Command Mode Selection */
#define       __FLASH_PROGRAM


typedef struct {
	unsigned    PWM:1;			    //PWM Enable 						1.
	unsigned	CurSenCal:1;        //Sensor Offset Check 				2.
	unsigned 	OLControl:1;		//Openloop Control 					3.
	unsigned	Oper_Ready:1;		//Operation Ready 					4.
	unsigned	EMG_Stop:1;         //EMG Stop  						5.
	unsigned	Const_Vc:1;   		//Constant Voltage SVM				6.
	unsigned	D_Axis_Test:1;		//									7.
} FLAGS;
#define FLAGS_DEFAULTS {0,0,0,0,0,0,0}

struct ERR_FLAGS_BITS{
    Uint32      OC:1;               // Over Current                     1
    Uint32      OV_DCLINK:1;        // DC_Link over voltage             2
    Uint32      LV_DCLINK:1;        // DC_Link low voltage              3
    Uint32      ZC:1;               // Zero Sequence Current            4
    Uint32      OV_LOAD:1;          // Over Load                        5
    Uint32      SEN_ERR:1;          // Sensor connection fault          6
    Uint32      HW_Fault_FB:1;      // Hardware Fault                   7.
    Uint32      MPC_Gate_FLT:1;     // Gate Drive Fault                 8.
    Uint32      GD_RDY_FLT:1;       // Gate Drive non-ready             9.
    Uint32      GD_Desat_FLT:1;     // Gate Drive desaturation Fault    10.
    Uint32      GD_Gate_OT:1;       // GD Over Temperature              12
    Uint32      OVSPD:1;            // Overspeed                        13.
    Uint32      reserved1:22;       // Reserved                         12~32.
};

union ERR_FLAGS {
	Uint32                 all;
   struct ERR_FLAGS_BITS  bit;
};

typedef struct {
    volatile Uint16     *raw;
    float32     offset;
    float32     gain;
    float32     lpf;
} FOR_ADC;

typedef struct {
    volatile Uint16     *raw;
    float32             offset;
    float32             gain;
    float32             lpf;
} FOR_ADC2;

typedef struct {
    float32     a_ph;
    float32     b_ph;
    float32     c_ph;
    float32     a_ph_lpf;
    float32     b_ph_lpf;
    float32     c_ph_lpf;
    float32     alpha;
    float32     beta;
    float32     zero;
    float32     d_;
    float32     q_;
} COORDINATE;

typedef struct {
    float32     a_ph_out;
    float32     b_ph_out;
    float32     c_ph_out;
    float32     a_ph_out_lim;
    float32     b_ph_out_lim;
    float32     c_ph_out_lim;
    float32     a_ph_out_err;
    float32     b_ph_out_err;
    float32     c_ph_out_err;
    float32      Ta;
    float32     Tb;
    float32     Tc;
    float32     max;
    float32     min;
    float32     offVol;
} SVM_OFFSET;

typedef struct {
    float32     eTheta;
    float32     mTheta;
    float32     eOmega;
    float32     eOmega_LPF;
    float32     mOmega;
    float32     mRpm;
    float32     mRpm_LPF;
    float32     cos_val;
    float32     sin_val;
    float32     eTheta_old;
} POS_SEN;

typedef struct {
    float32     set;
    float32     ref;
    float32     test;
    float32     kp;
    float32     ki;
    float32     ka;
    float32     err;
    float32     sum;
    float32     out;
    float32     sum_lmt;
    float32     Out_err;
    float32     Decoeff;
} PI_CON;

typedef struct {
    float32     PWM_Carr_Freq;
    float32     PWM_Freq;
    float32     PWM_Tsmp;
    float32     Spd_Freq;
    float32     Spd_Tsmp;
    Uint16      Spd_Prescaler;
    Uint16      Tmax;
    float32     ReqPWM_Freq;
    float32     ReqPWM_VariFreq_Amp;
    float32     ReqPWM_VariFreq_Freq;
    float32     Theta;  //rad
} VARI_FREQ;

typedef struct {
    float32     Rs;
    float32     Ld;
    float32     Lq;
    float32     phi;
} MOT_PARA;

typedef struct {
    float32     eTheta;
    float32     eOmega;
    float32     eOmega_lpf;
    float32     cos_val;
    float32     sin_val;
    float32     eTheta_dot_lpf;
    float32     d_;
    float32     q_;
    float32     d_lpf;
    float32     q_lpf;
    float32     offset;
    float32     eTheta_com;
} PLL_POS;

typedef struct{
	 Uint16   	OC;				// Over Current            			1
	 Uint16		OV;				// Grid High Voltage	     		2
	 Uint16		LV;   			// Grid Low Voltage					3
	 Uint16		NOCONNECTION;	// Grid voltage no connection		4
	 Uint16		OV_DCLINK;		// DC_Link over voltage				5
	 Uint16		LV_DCLINK;		// DC_Link low voltage				6
	 Uint16		ZC;				// Zero Sequence Current			7
	 Uint16		FLT;			// IGBT Saturation, IGBT short		8
	 Uint16		OT;				// Over Temperature					9
	 Uint16		OV_LOAD;		// Over Load						10
	 Uint16		UNBAL_V;		// Unbalance Voltage				11
	 Uint16		OC_OUT;			// Over DC Out current 				12
	 Uint16		OVSPD;		    // Over Modulation					13
	 Uint16		PLL_ERR;		// PLL (delta_theta) Error			14
} ERR_VAULE;
#define ERR_VAULE_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0}

typedef struct{
     float32    EMG_TRIP;
     float32    OFF_TRIP;
} FLT_TRIP;

typedef struct{
    FLT_TRIP      OC_FLT;               // Over Current                     1
    FLT_TRIP      OV_DCLINK_FLT;        // DC_Link over voltage             2
    FLT_TRIP      LV_DCLINK_FLT;        // DC_Link low voltage              3
    FLT_TRIP      ZC_FLT;               // Zero Sequence Current            4

    FLT_TRIP      OV_LOAD_FLT;          // Over Load                  5
    float32       SEN_MAX_ERR;          // Sensor connection fault     6
    float32       SEN_MIN_ERR;          // Sensor connection fault     7

    FLT_TRIP      OVSPD_FLT;            // Over Load                    8
} INV_FLT_TRIP;

typedef struct {
    float32     a_ph;
    float32     b_ph;
    float32     c_ph;
}THREE_PH;


typedef struct{
	int16 	Rpm_cmd;			//Voltage Command from user
	int16	Ramp_Time;			//Ramp response time from user

	int16	TINV_I_q_cmd;		//Load motor speed
	int16	Torque_Test_Motor;  //Torque command test motor
	int16	RPM_Load_Motor_Ref;	//Load Motor Speed Reference
	//int16	I_Out_Limit;		//Ouput Current Limit
	Uint16	PC_CAN_CNT;			//PC_CAN_CNT
	int16	BTS_V_dc_in;
	int16	BTS_V_dc_in_ref;
	int16	BTS_V_dc_out;
	int16	BTS_I_out;
	int16	BTS_P_out;
	Uint16	BTS_tx_cnt;
	Uint16   Fault_Load_No;		//Fault_Set_No
	Uint16   Turning_Value;		//Fault_Set_No
} EXTERNAL_VAULE;
#define EXTERNAL_VAULE_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0}

typedef struct{
	unsigned	_1ms:1;								//1ms  flag
	unsigned	_2ms:1;								//2ms  flag
	unsigned 	_10ms:1;							//10ms flag
	unsigned 	_100ms:1;							//100ms flag
	unsigned 	_1s:1;								//1s flag
	unsigned	INV_RST_Flaut:1;					//Reset flag
} TIME_FLAGS;
#define TIME_FLAGS_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0}



typedef struct {
    float32     alpha;
    float32     beta;
}ST_DQ;

typedef struct {
    float32     d_;
    float32     q_;
}SY_DQ;

typedef struct {
    float64     d_;
    float64     q_;
}SY_DQ64;



#define DEV_VALUE_DEFAULTS {0,0.0,0.0,0.0}

#define BOUND_RAD(RAW)               if(RAW > _2PI){RAW = RAW-_2PI;} else if(RAW < 0.0){RAW = RAW+_2PI;}
#define BOUND_PI_RAD(RAW)            if(RAW > PI){RAW = RAW-_2PI;} else if(RAW < -PI){RAW = RAW+_2PI;}
#define BOUND_DEG(RAW)               if(RAW > 360.0){RAW = RAW-360.0;} else if(RAW < 0.0){RAW = RAW+360.0;}
#define BOUND_VAL(RAW , MAX, MIN)    if(RAW > MAX){RAW = MAX;} else if(RAW < MIN){RAW = MIN;}
#define BOUND_MAGVAL(RAW , MAG)      if(RAW > MAG){RAW = MAG;} else if(RAW < -MAG){RAW = -MAG;}
#define BOUND_VAL_SET_ERRFLAG(RAW , MAX, MIN, ERR_FLAG)    if(RAW > MAX){RAW = MAX;ERR_FLAG =  SET;} else if(RAW < MIN){RAW = MIN; ERR_FLAG =  SET;}


#define ADC_TO_REAL( RAW , GAIN, OFFSET)    ((RAW - OFFSET) * (GAIN))

#define ABC_TO_ALPHA( APH , BPH, CPH)       ((2.0*APH - BPH - CPH)*_1_OVER3)
#define ABC_TO_BETA( BPH , CPH)             (_1_SQRT3*BPH - _1_SQRT3*CPH)
#define ABC_TO_ZERO( APH , BPH, CPH)        (_SQRT2_3*(APH + BPH + CPH))

#define STDQ_TO_DAXIS( ALPHA , BETA, COS, SIN)      ( ALPHA*COS + BETA*SIN)
#define STDQ_TO_QAXIS( ALPHA , BETA, COS, SIN)       (-ALPHA*SIN + BETA*COS)

#define RTDQ_TO_ALPHA( D_AXIS, Q_AXIS, COS, SIN)    ( D_AXIS*COS - Q_AXIS*SIN)
#define RTDQ_TO_BETA( D_AXIS, Q_AXIS, COS, SIN)     ( D_AXIS*SIN + Q_AXIS*COS)

#define LPF_FCN( IN, OUT, FIL_IN, FIL_OUT)    ( IN*FIL_IN + OUT*FIL_OUT)

#endif

//===========================================================================
// No more.
//===========================================================================
