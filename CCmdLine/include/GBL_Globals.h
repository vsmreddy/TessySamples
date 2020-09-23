/**************************************************************************//**
*
* <b>Project:   Tessy Example - Globals </b>
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
* \file      GBL_Globals.h
* \date      $Date: 02.05.2013$
*
*******************************************************************************
* \brief
*  Global definitions, types, enums, etc.
*  
*******************************************************************************
* History:
* 02.05.2013 initial revision
*
*******************************************************************************/
#ifndef _GBL_GLOBALS_H_
#define _GBL_GLOBALS_H_

/**************************************************************************//**
* Include files
******************************************************************************/

/**************************************************************************//**
* Defines
******************************************************************************/
#define NULL				0
#define FALSE				0
#define TRUE				1

#define CHAR_MIN			-128
#define CHAR_MAX			127

#define SHORT_MIN			-32768
#define SHORT_MAX			32767

#define LONG_MIN			-2147483648
#define LONG_MAX			2147483647

#define UCHAR_MAX			255u
#define USHORT_MAX			0xFFFFu
#define ULONG_MAX			0xFFFFFFFFu


/**************************************************************************//**
* Types
******************************************************************************/

/**************************************************************************//**
 * \enum       enFALSE_TRUE
 * \brief      Basic enum with FALSE and TRUE
 *****************************************************************************/
typedef enum enFALSE_TRUE{
	eFALSE = 0,
	eTRUE
}eFALSE_TRUE;


/**************************************************************************//**
* Variables
******************************************************************************/

/**************************************************************************//**
* Prototypes
******************************************************************************/

#endif /* _GBL_GLOBALS_H_ */