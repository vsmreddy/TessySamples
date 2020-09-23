/**************************************************************************//**
*
* <b>Project:   Tessy Example - System file </b>
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
* \file      system.h
* \date      $Date: 02.05.2013$
*
*******************************************************************************
* \brief
*  Hardware Abstraction Layer
*  
*******************************************************************************
* History:
* 02.05.2013 initial revision
*
*******************************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H


/* Port8 */

typedef volatile union
{
	struct
	{
			unsigned int P0         :1;
			unsigned int P1         :1;
			unsigned int P2         :1;
			unsigned int P3         :1;
			unsigned int P4         :1;
			unsigned int P5         :1;
			unsigned int P6         :1;
			unsigned int P7         :1;
			unsigned int P8         :1;
			unsigned int P9         :1;
			unsigned int P10        :1;
			unsigned int P11        :1;
			unsigned int P12        :1;
			unsigned int P13        :1;
			unsigned int P14        :1;
			unsigned int P15        :1;
			unsigned int            :16;
	} B;

    int I;
	unsigned int U;

} P8_OUT_type;
#define P8_OUT          (*(P8_OUT_type*)  0xF0000E00)   /* P8 Data Output Register */


#endif /* SYSTEM_H */

