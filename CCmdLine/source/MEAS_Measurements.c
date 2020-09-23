/**************************************************************************//**
*
* <b>Project:   Tessy Example - Measurement of plant environment conditions </b>
*
* \author    $Author: Razorcat Development GmbH$                             \n
*            Razorcat Development GmbH                                       \n
*            Witzlebenplatz 4                                                \n
*            D-14057 Berlin                                                  \n
*            http://www.razorcat.com                                         \n
*                                                                            \n
*            $Revision 1.0.3$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      MEAS_Measurements.c
* \date      $Date: 13.09.2018$
*
*******************************************************************************
* \brief
*  Measurement of temperature and humidity and calculatingn the average
*  
*******************************************************************************
* History:
* 13.09.2018 update of the specification
* 06.10.2017 MEAS_Init_HumidityMeasurement()
* 20.02.2017 MEAS_CalcAverageHumidity()
* 02.05.2013 initial revision
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include <MEAS_Measurements.h>

/**************************************************************************//**
* Global functions
******************************************************************************/
void MEAS_Init_Measurements(void);
char MEAS_CalcAverageTemp(void);
unsigned short MEAS_CalcAverageHumidity(void);
/**************************************************************************//**
* Global variables
******************************************************************************/

/**************************************************************************//**
 * \var        cTempRecVals
 * \brief      Array with recorded temperature values to calculate the 
 *             average temperature
 *****************************************************************************/
static char cTempRecVals[dTEMP_REC_COUNT];

/**************************************************************************//**
 * \var        usHumidityRecVals
 * \brief      Array with recorded humidity values to calculate the 
 *             average humidity
 *             
 *****************************************************************************/
static unsigned short usHumidityRecVals[dHUMID_REC_COUNT];

/**************************************************************************//**
* Local functions
******************************************************************************/
void MEAS_Init_TempMeasurement(char cInitTempValue);
void MEAS_Init_HumidityMeasurement(unsigned short usInitHumidValue);
char MEAS_CalcAverage(char *cRecords, unsigned char ucLength);

/**************************************************************************//**
* Local variables
******************************************************************************/

/**************************************************************************//**
* External functions
******************************************************************************/
extern char TEMP_GetCurrentTemp(void);
extern unsigned short HUMID_GetCurrentHumidity(void);

/**************************************************************************//**
* External variables
******************************************************************************/

/**************************************************************************//**
* Functions
******************************************************************************/

/*-----------------------------------------------------------------------------+
    MEAS_Init_TempMeasurement()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.01<br>
    <B>Description</B><BR>
    Initialize the array with temperature values \n

    <B>Requirements:</B>\n
    \anchor REQID80_1
    REQID 80 All values have to be initialized with the current temperature value.\n

    \param[in]       cInitTempValue
					 Current temperature value for initializing\n
                     <I><B> Valid values: </B>\n
                     [0 .. 255] </I>\n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cTempRecVals[]\n

    <B>Execution steps:</B><BR>
    \li	Set array values to the current temperature value
*/
/*----------------------------------------------------------------------------*/
void MEAS_Init_TempMeasurement(char cInitTempValue)
{
	unsigned short i;	
	
	for(i = 0; i < dTEMP_REC_COUNT; i++)
	{
		cTempRecVals[i] = cInitTempValue;
	}
}


/*-----------------------------------------------------------------------------+
    MEAS_Init_HumidityMeasurement()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.02<br>
    <B>Description</B><BR>
    Initialize the array with humidity values\n

    <B>Requirements:</B>\n
    \anchor REQID81_1
    REQID 81 All values have to be initialized with the current humidity value.\n

    \param[in]       usInitHumidValue    Current humidity value for initializing\n
                                         <I><B> Valid values: </B>\n
                                         [0 .. 255] </I>\n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          usHumidityRecVals[]\n

    <B>Execution steps:</B><BR>
    \li	Set array values to the current humidity value
*/
/*----------------------------------------------------------------------------*/
void MEAS_Init_HumidityMeasurement(unsigned short usInitHumidValue)
{
	unsigned short i;	
	
	for(i = 0; i < dHUMID_REC_COUNT; i++)
	{
		usHumidityRecVals[i] = usInitHumidValue;
	}
}


/*-----------------------------------------------------------------------------+
    MEAS_Init_Measurements()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.03<br>
    <B>Description</B><BR>
    Initialize the measurement data\n

    <B>Requirements:</B>\n
    \anchor REQID82_1
    REQID 82 All record data for measurements have first to be initialized.\n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          -\n
    <B>Execution steps:</B><BR>
    \li	Initialize temperature values
	\li Initialize humidity values
	\li Initialize timeout counter for sending alarm
	\li Initialize counter for waiting until some measurements are executed
*/
/*----------------------------------------------------------------------------*/
void MEAS_Init_Measurements(void)
{
	char cCurrentTemp;
	unsigned short usCurrentHumidity;
	
	cCurrentTemp = TEMP_GetCurrentTemp();
	MEAS_Init_TempMeasurement(cCurrentTemp);
	
	usCurrentHumidity = HUMID_GetCurrentHumidity();
	MEAS_Init_HumidityMeasurement(usCurrentHumidity);
}


/*-----------------------------------------------------------------------------+
    MEAS_CalcAverage()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.04<br>
    <B>Description</B><BR>
    Calculates the average of values in an character array\n

    <B>Requirements:</B>\n
    \anchor REQID83_1
    REQID 83 Average have to be calculated by summarizing and dividing.\n
	
	\param[in]       *cRecords    Pointer to recorded values\n
                                  <I><B> Valid values: </B>\n
                                  [LONG_MIN .. LONG_MAX] </I>\n
	\param[in]       ucLength     Count of recorded values\n
                                  <I><B> Valid values: </B>\n
                                  [0 .. UCHAR_MAX] </I>\n
	
	\return    Calculated average of recorded values\n
		   <I><B>valid values:</B>\n
		   0\n</I>
	
    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          -\n
    <B>Execution steps:</B><BR>
    \li	Summarize n values
	\li Divide the sum by n
*/
/*----------------------------------------------------------------------------*/
char MEAS_CalcAverage(char *cRecords, unsigned char ucLength)
{
	unsigned char i;
	long lResult = 0;
	
	if ((cRecords != NULL) && (ucLength > 0U))
	{
		for(i = 0; i < ucLength; i++)
		{
			lResult = lResult + (long)cRecords[i];
		}
		lResult = lResult / ucLength;
	}
	else
	{
		/* Invalid pointer, return 0 */
		return 0;
	}
	return (char) lResult;
}


/*-----------------------------------------------------------------------------+
    MEAS_CalcAverageTemp()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.05<br>
    <B>Description</B><BR>
    Calculates the average value of the temperature\n

    <B>Requirements:</B>\n
    \anchor REQID84_2
    REQID 84 Average temperature has to be calculated by using recorded values.\n
	
	\return    Average temperature value\n
               <I><B>Valid values:</B>\n
               [CHAR_MIN .. CHAR_MAX]\n</I>
	
    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cTempRecVals[]\n
    <B>Execution steps:</B><BR>
    \li	Call the function to calculate the average of the temperature values
*/
/*----------------------------------------------------------------------------*/
char MEAS_CalcAverageTemp(void)
{
	char cRetval;
	
	cRetval = MEAS_CalcAverage((char*) cTempRecVals, (unsigned char) dTEMP_REC_COUNT);
	return cRetval;
}


/*-----------------------------------------------------------------------------+
    MEAS_CalcAverageHumidity()
+-----------------------------------------------------------------------------*/
/*!
    Function Nr SW123.06<br>
    <B>Description</B><BR>
    Calculates the average of the humidity\n

    <B>Requirements:</B>\n
	\anchor REQID83_2
    REQID 83 Average have to be calculated by summarizing and dividing.\n
    \anchor REQID85_2
    REQID 85 Average humidity has to be calculated by using recorded values.\n
	
	\return    Average humidity value\n
               <I><B>Valid values:</B>\n
               [0 .. USHORT_MAX]\n</I>
	
    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          usHumidityRecVals[]\n
    <B>Execution steps:</B><BR>
    \li	Calculates the average of the humidity values
*/
/*----------------------------------------------------------------------------*/
unsigned short MEAS_CalcAverageHumidity(void)
{
	unsigned char i;
	unsigned long ulResult = 0;
	
	//lRetval = MEAS_CalcAverage((long*) &usHumidityRecVals[0], (unsigned char) dHUMID_REC_COUNT);
	for(i = 0; i < dHUMID_REC_COUNT; i++)
	{
		ulResult = ulResult + (unsigned long) usHumidityRecVals[i];
	}
	ulResult = ulResult / dHUMID_REC_COUNT;
	
	return (unsigned short)ulResult;
}

/************************************ EOF ************************************/
