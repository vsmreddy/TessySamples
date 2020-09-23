/**************************************************************************//**
*
* <b>Project:   Tessy Example - Plots </b>
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
* \file      Plots.c
* \date      $Date: 13.09.2018$
*
*******************************************************************************
* \brief
*  Functions for Plot
*  
*******************************************************************************
* History:
* 13.09.2018 update of the specification
* 02.05.2013 initial revision
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include <Plots.h>

/**************************************************************************//**
* Global functions
******************************************************************************/

/**************************************************************************//**
* Global variables
******************************************************************************/
signed long interpolate;
signed char sine_value;
unsigned char sine_values[SINEVALUES] = {100, 126, 150, 171, 187, 197,
                                         200, 197, 187, 171, 150, 126,
                                         100, 74, 50, 29, 13, 3, 0,
                                         3, 13, 29, 50, 74, 100};
/**************************************************************************//**
* Local functions
******************************************************************************/

/**************************************************************************//**
* Local variables
******************************************************************************/

/**************************************************************************//**
* External functions
******************************************************************************/

/**************************************************************************//**
* External variables
******************************************************************************/

/**************************************************************************//**
* Functions
******************************************************************************/

/*-----------------------------------------------------------------------------+
    CalcSine1()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Calculate sine value corresponding to the given radian input value.\n
    The calculation is using an array with the sine values.\n
    Do an interpolation, if requested.\n

    \param[in]       radian_value   radian input value
    \param[in]       interpolate    interpolation, if requested

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          sine_values\n

    <B>Execution steps:</B><BR>
    \li	Return the sine value corresponding to the given radian input value
    Do an interpolation, if requested.
*/
/*----------------------------------------------------------------------------*/
signed char CalcSine1(unsigned char radian_value, teYes_No interpolate)
{
	unsigned char index;
	signed char mod, diff=0;
	
	/* calculate index into values array */
	index = (unsigned short)(radian_value * 2) / 15;
	while (index >= SINEVALUES) {
		index = index - SINEVALUES;
	}
	
	/* do some interpolation, if requested */
	if (interpolate == yes) {

		mod = (unsigned short)(radian_value * 2) % 15;
		
		/* check for modulo remainder */
		if (mod) {
			diff = sine_values[index+1] - sine_values[index];
			
			/* interpolate difference value */
			if (mod > 7)
				if (mod > 10)
					diff = 7 * diff / 8;
				else
					diff = 5 * diff / 8;
			else
				if (mod > 3)
					diff = 3 * diff / 8;
				else
					diff = 1 * diff / 8;
		}
	}
	
	return sine_values[index] - 100 + diff;
}


/*-----------------------------------------------------------------------------+
    CalcSine2()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Simple sine calculation\n

    \param[in]       radian_value   radian unit

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          sine_value\n

    <B>Execution steps:</B><BR>
    \li	Calculate sine from radian value
*/
/*----------------------------------------------------------------------------*/
void CalcSine2(unsigned short radian_value)
{	
	double tmpVal1;
	double tmpVal2;
	double term1;
	double term2;
	double term3;
	double tmpAngle;
	
	tmpVal1 = ((double)radian_value)/100;
	
	if (tmpVal1 > dPI)
	{
		tmpAngle = tmpVal1 * (180 / dPI);
		tmpAngle = 180 - tmpAngle;
		tmpVal1 = tmpAngle * (dPI / 180);
	}
	/* Taylor */
	term1 = (tmpVal1*tmpVal1*tmpVal1)/(3*2);
	term2 = ((tmpVal1*tmpVal1*tmpVal1*tmpVal1*tmpVal1)/(5*4*3*2));
	term3 = ((tmpVal1*tmpVal1*tmpVal1*tmpVal1*tmpVal1*tmpVal1*tmpVal1)/(7*6*5*4*3*2));
	tmpVal2 = (tmpVal1 - term1 + term2 - term3);

	sine_value = (signed char)(tmpVal2 * 100);
}

/************************************ EOF ************************************/
