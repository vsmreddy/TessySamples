/**************************************************************************//**
*
* <b>Project:   Project - File Description </b>
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
* \file      Memory.c
* \date      $Date: 02.05.2013$
*
*******************************************************************************
* \brief
*   Memory test
*  
*******************************************************************************
* History:
* 02.05.2013 initial revision
* 06.10.2017 Format for Doxygen adapted
*
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include <Memory.h>

/**************************************************************************//**
* Global functions
******************************************************************************/

/**************************************************************************//**
* Global variables
******************************************************************************/

/**************************************************************************//**
* Local functions
******************************************************************************/

/**************************************************************************//**
* Local variables
******************************************************************************/
static unsigned long ulMemory[MEMORYSIZE];
static tstMemoryState stMemoryState;

/**************************************************************************//**
* External functions
******************************************************************************/
/* Insert External functions declaration */
#ifdef TESSY
extern void TS_FaultInsertionInit(unsigned long TS_Address);
extern void TS_FaultInsertionMemory(unsigned long TS_Address);
#endif /* TESSY */

/**************************************************************************//**
* External variables
******************************************************************************/
/* Insert External variable declaration */
#ifdef TESSY
extern unsigned long TS_FaultAddress;
extern unsigned long TS_FaultExecute;
#endif /* TESSY */

/**************************************************************************//**
* Functions
******************************************************************************/

/*-----------------------------------------------------------------------------+
    initMemory()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Initialize the memory structure \n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          tstMemoryStates[]\n

    <B>Execution steps:</B><BR>
    \li	Clear memory structure
*/
/*----------------------------------------------------------------------------*/
void initMemory(void)
{
	stMemoryState.MemCounter = 0;
	stMemoryState.LastErrAddr = 0x00000000;
}


/*-----------------------------------------------------------------------------+
    CheckMemory()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Test memory \n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          stMemoryState ulMemory[]\n

    <B>Execution steps:</B><BR>
    \li	Test memory and return Error Counter
*/
/*----------------------------------------------------------------------------*/
unsigned long CheckMemory (void)
{
    unsigned long i;

/* Insert initialization */
#ifdef TESSY
TS_FaultInsertionInit ((unsigned long)&ulMemory[0]);
#endif /* TESSY */

	initMemory();
    for ( i=0;i<MEMORYSIZE;i++ )
    {
        ulMemory[i] = 0xAAAAAAAA;
		
/* Insert changes for first loop */
#ifdef TESSY
TS_FaultInsertionMemory((unsigned long)&ulMemory[i]);
#endif /* TESSY */

    }

    for ( i=0;i < MEMORYSIZE;i++ )
    {
        if ( ulMemory[i] != 0xAAAAAAAA )
        {
        	stMemoryState.MemCounter++;
            stMemoryState.LastErrAddr=(unsigned long)&ulMemory[i]-(unsigned long)&ulMemory[0];
        }
    }
    return stMemoryState.MemCounter;
}


/************************************ EOF ************************************/
