/**************************************************************************//**
*
* <b>Project:   Tessy Example</b>
*
* \author    $Author: Razorcat Development GmbH$                             \n
*            Razorcat Development GmbH                                       \n
*            Witzlebenplatz 4                                                \n
*            D-14057 Berlin                                                  \n
*            http://www.razorcat.com                                         \n
*                                                                            \n
*            $Revision 1.0.2$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      TrafficLightCtrl.c
* \date      $Date: 13.09.2018$
*
*******************************************************************************
* \brief
* Single Traffic Light
*******************************************************************************
* History:
* 13.09.2018 update of the specification
* 20.04.2013 initial revision
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include <TrafficLightCtrl.h>
#include <ErrorManager.h>

/**************************************************************************//**
* Global functions
******************************************************************************/

/**************************************************************************//**
* Global variables
******************************************************************************/

/**************************************************************************//**
* Local functions
******************************************************************************/
void TL_Init(void);
void TL_TickHandler(void);
unsigned long TL_GetPhaseTime(void);
void TL_ClearPhaseTime(void);

/**************************************************************************//**
* Local variables
******************************************************************************/
static tstTrafficLight stTrafficLight;
static teTLState eTLState;
static unsigned long ulSysLastTime;
static unsigned long ulSysCurrentTime;

/**************************************************************************//**
* External functions
******************************************************************************/
extern void SetPort(unsigned long ulValue);
extern void ErrorHandler(teERR_State eErrorState);

/**************************************************************************//**
* External variables
******************************************************************************/
extern unsigned long SYS_ulTimerCNT;
/**************************************************************************//**
* Functions
******************************************************************************/


void TL_Init(void)
{
	stTrafficLight.eLightState = eYellow;
	stTrafficLight.ulPhaseTime = 0;
	SetPort(dYELLOW);
}

/*-----------------------------------------------------------------------------+
    TL_TickHandler()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Handler for switching from one trafficlight state to another\n

    <B>Requirements:</B>\n
    \anchor REQID90_1
    REQID 90 Hier steht die Beschreibung der Anforderung.\n

    \param[in]       \n
                     <I><B>Valid values:</B>\n
                     </I>\n
    \param[in, out]  \n
                     <I><B>Valid values:</B>\n
                     </I>\n
    \param[out]       \n
                     <I><B>Valid values:</B>\n
                     </I>

    \return    \n
               <I><B>valid values:</B>\n
               \n</I>

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          \n

    <B>Execution steps:</B><BR>
    \li
*/
/*----------------------------------------------------------------------------*/
void TL_Handler(void)
{
	teTLState leTLState = stTrafficLight.eTLState;
	teLightState leLightState = stTrafficLight.eLightState;
	unsigned long ulTime = TL_GetPhaseTime();
	
	if (leTLState == eTLactive)
	{
		switch (leLightState)
		{
			case eRed:
			{
				if(ulTime >= dPHASE_RED)
				{
					stTrafficLight.eLightState = eRedYellow;
					ulSysLastTime=ulSysCurrentTime;
					SetPort(dREDYELLOW);
				}
				break;
			}
			case eRedYellow:
			{
				if(ulTime >= dPHASE_REDYELLOW)
				{
					ulTime = 0;
					stTrafficLight.eLightState = eGreen;
					ulSysLastTime=ulSysCurrentTime;
					SetPort(dGREEN);
				}
				break;

			}
			case eGreen:
			{
				if(ulTime >= dPHASE_GREEN)
				{
					ulTime = 0;
					stTrafficLight.eLightState = eYellow;
					ulSysLastTime=ulSysCurrentTime;
					SetPort(dYELLOW);
				}
				break;
			}
			case eYellow:
			{
				if(ulTime >= dPHASE_YELLOW)
				{
					ulTime = 0;
					stTrafficLight.eLightState = eRed;
					ulSysLastTime=ulSysCurrentTime;
					SetPort(dRED);
				}
				break;
			}
			case eYellowBlinking:
			{
				SetPort(dYELLOWBLINKING);
				break;
			}
			default:
			{
				stTrafficLight.eTLState = eTLfail;
				ErrorHandler(eERR_STATE);
			}
		}
		stTrafficLight.ulPhaseTime = ulTime;
	} 
	else if (eTLState == eTLinactive)
	{
		SetPort(dOFF);
	}
	else if (eTLState == eTLfail)
	{
		SetPort(dYELLOWBLINKING);
	}
	else if (eTLState == eTLreset)
	{
		stTrafficLight.eTLState = eTLfail;
		ErrorHandler(eERR_INIT);
	}
	else
	{
		stTrafficLight.eTLState = eTLfail;
		ErrorHandler(eERR_STATE);
	}

}


void TL_SimpleHandler(void)
{
	teLightState leLightState = stTrafficLight.eLightState;
	unsigned long ulTime = TL_GetPhaseTime();
	
	switch (leLightState)
	{
		case eOff:
		{
			SetPort(dOFF);
			break;
		}
		case eRed:
		{
			if(ulTime >= dPHASE_RED)
			{
				ulTime = 0;
				stTrafficLight.eLightState = eRedYellow;
				TL_ClearPhaseTime();
				SetPort(dREDYELLOW);
			}
			break;
		}
		case eRedYellow:
		{
			if(ulTime >= dPHASE_REDYELLOW)
			{
				ulTime = 0;
				stTrafficLight.eLightState = eGreen;
				TL_ClearPhaseTime();
				SetPort(dGREEN);
			}
			break;

		}
		case eGreen:
		{
			if(ulTime >= dPHASE_GREEN)
			{
				ulTime = 0;
				stTrafficLight.eLightState = eYellow;
				TL_ClearPhaseTime();
				SetPort(dYELLOW);
			}
			break;
		}
		case eYellow:
		{
			if(ulTime >= dPHASE_YELLOW)
			{
				ulTime = 0;
				stTrafficLight.eLightState = eRed;
				TL_ClearPhaseTime();
				SetPort(dRED);
			}
			break;
		}
		case eYellowBlinking:
		{
			SetPort(dYELLOWBLINKING);
			break;
		}
		default:
		{
			ErrorHandler(eERR_STATE);
			stTrafficLight.eLightState = eYellowBlinking;
			SetPort(dYELLOWBLINKING);
		}
	}
	stTrafficLight.ulPhaseTime = ulTime;

}

unsigned long TL_GetPhaseTime(void)
{
	unsigned long ulReturn;

	/* Get current system counter */
	ulSysCurrentTime = SYS_ulTimerCNT;
	/* underflow is okay, difference needed */
	ulReturn = ulSysCurrentTime - ulSysLastTime;

	return ulReturn;
}

void TL_ClearPhaseTime(void)
{
	ulSysLastTime=ulSysCurrentTime;
}



void TL_InitConfig()
{

	
	
}



void TL_Tick()
{
	TL_Handler();
}

/************************************ EOF ************************************/
