/**************************************************************************//**
*
* <b>Project:   TESSY Seminar </b>
*
* \author    $Author: Razorcat Development GmbH$                             \n
*            Razorcat Development GmbH                                       \n
*            Witzlebenplatz 4                                                \n
*            D-14057 Berlin                                                  \n
*            http://www.razorcat.com                                         \n
*                                                                            \n
*            $Revision: 1.0.2$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      Defines.h
* \date      $Date: 12.09.2013$
*
*******************************************************************************
* \brief
*   Examples using define TESSY
*  
*******************************************************************************
* History:                                                                   \n
* 02.05.2013 initial revision                                                \n
* 12.09.2013 revised macro ERROR_FATAL
*
*******************************************************************************/
#ifndef _DEFINES_H_
#define _DEFINES_H_


/* Macro for function calls into an endless loop */
/* extern void err_fatal(unsigned long ulErrNo); */
/* The intention of the macros are to return from the test object in case of an endless loop */
/* By using TESSY the macros implement a return at he end of the "endless" loop */
/* In the release the macros implement nothing and the endless loop will be executed */
/* The macros are split for test objects with and without a return value */
/* Original function call: */
/*   err_fatal(ulErrNo); */
/* replaced with the macro for test objects without a return value: */
/*   ERROR_FATAL(x); */
/* replaced with the macro for test objects with a return value: */
/*   ERROR_FATAL_0(x); */
#ifdef TESSY

    /* This macro is used in function without a return value */
	#define ERROR_FATAL(x)     err_fatal(x); return
    /* This macro is used in function with a return value */
	#define ERROR_FATAL_0(x)   err_fatal(x); return 0
    
#else

	/* This macros is used in the application */
    /* This macro is used in function without a return value */
	#define ERROR_FATAL(x)     err_fatal(x)

    /* This macro is used in function with a return value */
	#define ERROR_FATAL_0(x)   err_fatal(x)

#endif /* TESSY */

    
/* Macro for an endless loop with while(1); */
#ifdef TESSY
	unsigned long TS_Loop;
	#define MC_HALT

#else

    /* This macros is used in the application */
	#define MC_HALT    while(1)
    
#endif /* TESSY */


/* Macro for an endless loop with a loop counter  */
#ifdef TESSY
	unsigned long TS_Loop;
	#define FOREVER    while( TS_Loop-- > 0 )

#else

    /* This macros is used in the application */
	#define FOREVER    while(1)
    
#endif /* TESSY */


/* Macro for configuration data, to be able to change values in the tests */
/* Instead of the key word const, the macro is used, for example: */
/* Usage in the application without the macro: */
/* const unsigned long myConfig;               */

/* Usage in the application with the macro: */
/* CONFIGDATA unsigned long myConfig;       */

#ifdef TESSY
	#define CONFIGDATA
    
#else

    /* This macros is used in the application */
	#define CONFIGDATA const
    
#endif /* TESSY */

#endif /* _DEFINES_H_ */

/************************************ EOF ************************************/
