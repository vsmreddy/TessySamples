/**************************************************************************//**
*
* <b>Project:   Project - TESSY seminar </b>
*
* \author    $Author: Razorcat Development GmbH$                             \n
*            Razorcat Development GmbH                                       \n
*            Witzlebenplatz 4                                                \n
*            D-14057 Berlin                                                  \n
*            http://www.razorcat.com                                         \n
*                                                                            \n
*            $Revision 1.0.1$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      TrafficLightCtrl.h
* \date      $Date: 25.06.2013$
*
*******************************************************************************
* \brief
*  Header of TrafficLightCtrl.h
*  
*******************************************************************************
* History:
* 25.06.2013 initial revision
*
*******************************************************************************/
#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_

/* light codes */
#define dOFF                0x00
#define dRED                0x01
#define dREDYELLOW          0x02
#define dGREEN              0x04
#define dYELLOW             0x08
#define dYELLOWBLINKING     0x10

/* Phase time in ms */
#define dPHASE_RED			30000
#define dPHASE_REDYELLOW	1000
#define dPHASE_GREEN		45000
#define dPHASE_YELLOW		2000

/**************************************************************************//**
* Include files
******************************************************************************/

/**************************************************************************//**
* Defines
******************************************************************************/
#define NULL		0

/**************************************************************************//**
* Types
******************************************************************************/
typedef enum eFALSE_TRUEs{
	eFALSE,
	eTRUE
}eFALSE_TRUE;

typedef enum eERR_RESULTs{
	eERROR,
	eOK
}eERR_RESULT;

/* Traffic light operating states */
typedef enum eTLStates{
    eTLreset,                    /* reset      not initialized  */
	eTLinactive,                 /* inactive   all lights off   */
	eTLactive,                   /* active     normal operating */
	eTLfail                      /* fail       yellow blinking  */
}teTLState;

/* States of the lighting */
typedef enum eLightStates{
    eOff,
	eRed, 
	eYellow,
	eGreen, 
	eRedYellow, 
    eYellowBlinking
}teLightState;

/* Traffic Light main structure */
typedef struct stTrafficlights{
	teTLState eTLState;              /* operating state */
	teLightState eLightState;        /* lighting state  */
	unsigned long ulPhaseTime;       /* current phase time */
	unsigned long ulLastActiveTime;
}tstTrafficLight;

/**************************************************************************//**
* Variables
******************************************************************************/

/**************************************************************************//**
* Prototypes
******************************************************************************/


#endif /* _TRAFFICLIGHT_H_ */

/************************************ EOF ************************************/
