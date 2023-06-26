//###########################################################################
//
// FILE:   F2837xD_EPwm_defines.h
//
// TITLE:  #defines used in EPwm examples
//
//###########################################################################
// $TI Release: F2837xD Support Library v190 $
// $Release Date: Mon Feb  1 16:51:57 CST 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2837xD_EPWM_DEFINES_H
#define F2837xD_EPWM_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

// TBCTL (Time-Base Control)
//==========================
// CTRMODE bits
#define	TB_COUNT_UP		0x0
#define	TB_COUNT_DOWN	0x1
#define	TB_COUNT_UPDOWN	0x2
#define	TB_FREEZE		0x3
// PHSEN bit
#define	TB_DISABLE		0x0
#define	TB_ENABLE		0x1
// PRDLD bit
#define	TB_SHADOW		0x0
#define	TB_IMMEDIATE	0x1
// SYNCOSEL bits
#define	TB_SYNC_IN		0x0
#define	TB_CTR_ZERO		0x1
#define	TB_CTR_CMPB		0x2
#define	TB_SYNC_DISABLE	0x3
// HSPCLKDIV and CLKDIV bits
#define	TB_DIV1			0x0
#define	TB_DIV2			0x1
#define	TB_DIV4			0x2
// PHSDIR bit
#define	TB_DOWN			0x0
#define	TB_UP			0x1

// CMPCTL (Compare Control)
//==========================
// LOADAMODE and LOADBMODE bits
#define	CC_CTR_ZERO		0x0
#define	CC_CTR_PRD		0x1
#define	CC_CTR_ZERO_PRD	0x2
#define	CC_LD_DISABLE	0x3
// SHDWAMODE and SHDWBMODE bits
#define	CC_SHADOW		0x0
#define	CC_IMMEDIATE	0x1

// AQCTLA and AQCTLB (Action Qualifier Control)
//=============================================
// ZRO, PRD, CAU, CAD, CBU, CBD bits
#define	AQ_NO_ACTION	0x0
#define	AQ_CLEAR		0x1
#define	AQ_SET			0x2
#define	AQ_TOGGLE		0x3

// DBCTL (Dead-Band Control)
//==========================
// OUT MODE bits
#define	DB_DISABLE		0x0
#define	DBB_ENABLE		0x1
#define	DBA_ENABLE		0x2
#define	DB_FULL_ENABLE	0x3
// POLSEL bits
#define	DB_ACTV_HI		0x0
#define	DB_ACTV_LOC		0x1
#define	DB_ACTV_HIC		0x2
#define	DB_ACTV_LO		0x3
// IN MODE
#define DBA_ALL         0x0
#define DBB_RED_DBA_FED 0x1
#define DBA_RED_DBB_FED 0x2
#define DBB_ALL         0x3

// OUTSWAP Dead Band Output Swap Control
#define DB_NO_SWAP      0x0
#define DB_OUTA_ONLY    0x1
#define DB_OUTB_ONLY    0x2
#define DB_EN_SWAP      0x3

// CHPCTL (chopper control)
//==========================
// CHPEN bit
#define	CHP_DISABLE		0x0
#define	CHP_ENABLE		0x1
// CHPFREQ bits
#define	CHP_DIV1		0x0
#define	CHP_DIV2		0x1
#define	CHP_DIV3		0x2
#define	CHP_DIV4		0x3
#define	CHP_DIV5		0x4
#define	CHP_DIV6		0x5
#define	CHP_DIV7		0x6
#define	CHP_DIV8		0x7
// CHPDUTY bits
#define	CHP1_8TH		0x0
#define	CHP2_8TH		0x1
#define	CHP3_8TH		0x2
#define	CHP4_8TH		0x3
#define	CHP5_8TH		0x4
#define	CHP6_8TH		0x5
#define	CHP7_8TH		0x6

// TZSEL (Trip Zone Select)
//==========================
// CBCn and OSHTn bits
#define	TZ_DISABLE		0x0
#define	TZ_ENABLE		0x1

// TZCTL (Trip Zone Control)
//==========================
// TZA and TZB bits
#define	TZ_HIZ			0x0
#define	TZ_FORCE_HI		0x1
#define	TZ_FORCE_LO		0x2
#define	TZ_NO_CHANGE	0x3

// TZDCSEL (Trip Zone Digital Compare)
//==========================
// DCAEVT1, DCAEVT2, DCBEVT1, DCBEVT2 bits
#define TZ_EVT_DISABLE      0x0
#define TZ_DCAH_LOW         0x1
#define TZ_DCAH_HI          0x2
#define TZ_DCAL_LOW         0x3
#define TZ_DCAL_HI          0x4
#define TZ_DCAL_HI_DCAH_LOW 0x5

#define TZ_DCBH_LOW         0x1
#define TZ_DCBH_HI          0x2
#define TZ_DCBL_LOW         0x3
#define TZ_DCBL_HI          0x4
#define TZ_DCBL_HI_DCBH_LOW 0x5

// ETSEL (Event Trigger Select)
//=============================
#define ET_DCAEVT1SOC   0x0
#define	ET_CTR_ZERO	    0x1 // Enable event time-base counter equal to zero. (TBCTR = 0x00)
#define	ET_CTR_PRD	    0x2 //Enable event time-base counter equal to period (TBCTR = TBPRD)
#define ET_CTR_PRDZERO  0x3 //Enable event time-base counter equal to zero or period (TBCTR = 0x00 or TBCTR = TBPRD). This mode is useful in updown count mode.
#define	ET_CTRU_CMPA	0x4
#define	ET_CTRD_CMPA	0x5
#define	ET_CTRU_CMPB	0x6
#define	ET_CTRD_CMPB	0x7

// ETPS (Event Trigger Pre-scale)
//===============================
// INTPRD, SOCAPRD, SOCBPRD bits
#define	ET_DISABLE		0x0
#define	ET_1ST			0x1
#define	ET_2ND			0x2
#define	ET_3RD			0x3

//--------------------------------
// HRPWM (High Resolution PWM)
// HRCNFG
#define    HR_DISABLE        0x0
#define    HR_REP            0x1
#define    HR_FEP            0x2
#define    HR_BEP            0x3

#define    HR_CMP            0x0
#define    HR_PHS            0x1

#define    HR_CTR_ZERO       0x0
#define    HR_CTR_PRD        0x1
#define HR_CTR_ZERO_PRD      0x2

#define HR_NORM_B            0x0
#define HR_INVERT_B          0x1

//--------------------------------
// DC (Digital Compare)
//================================
// DCTRIPSEL
#define DC_TZ1           0x0
#define DC_TZ2           0x1
#define DC_TZ3           0x2
#define DC_COMP1OUT      0x8
#define DC_COMP2OUT      0x9
#define DC_COMP3OUT      0xA
// DCFCTL
#define DC_SRC_DCAEVT1   0x0
#define DC_SRC_DCAEVT2   0x1
#define DC_SRC_DCBEVT1   0x2
#define DC_SRC_DCBEVT2   0x3

#define DC_PULSESEL_PRD  0x0
#define DC_PULSESEL_ZERO 0x1

#define	DC_BLANK_DISABLE 0x0
#define	DC_BLANK_ENABLE  0x1

#define DC_BLANK_NOTINV  0x0
#define DC_BLANK_INV     0x1
//DCACTL/DCBCTL
#define DC_EVT1          0x0
#define DC_EVT2          0x0
#define DC_EVT_FLT       0x1
#define DC_EVT_SYNC      0x0
#define DC_EVT_ASYNC     0x1
#define	DC_SOC_DISABLE   0x0
#define	DC_SOC_ENABLE    0x1


// Configure the period for each timer
#define EPWM1_TIMER_TBPRD  20000  // Period register
#define EPWM1_TIMER_TBPRDx1_2  10000  // Period register
#define EPWM1_TIMER_TBPRDx1_3  6667  // Period register
#define EPWM1_TIMER_TBPRDx2_3  13333  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

#define EPWM2_TIMER_TBPRD  2000  // Period register
#define EPWM2_MAX_CMPA     1950
#define EPWM2_MIN_CMPA       50
#define EPWM2_MAX_CMPB     1950
#define EPWM2_MIN_CMPB       50

#define EPWM3_TIMER_TBPRD  2000  // Period register
#define EPWM3_MAX_CMPA      950
#define EPWM3_MIN_CMPA       50
#define EPWM3_MAX_CMPB     1950
#define EPWM3_MIN_CMPB     1050

#define EPWM4_TIMER_TBPRD  2000  // Period register
#define EPWM4_MAX_CMPA      950
#define EPWM4_MIN_CMPA       50
#define EPWM4_MAX_CMPB     1950
#define EPWM4_MIN_CMPB     1050

// To keep track of which way the compare value is moving
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_EPWM_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
