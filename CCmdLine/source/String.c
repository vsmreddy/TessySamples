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
*            $Revision 1.0.2$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      String.c
* \date      $Date: 12.07.2013$
*
*******************************************************************************
* \brief
*   String operations
*  
*******************************************************************************
* History:
* 02.05.2013 initial revision
* 12.07.2013 last changes
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include <Stack.h>

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
/* Constant with number characters up to base hexadecimal*/
static const char cDigit[]  = "0123456789ABCDEF";

/**************************************************************************//**
* External functions
******************************************************************************/
extern void push_Stack(unsigned long ulValue);

/**************************************************************************//**
* External variables
******************************************************************************/

/**************************************************************************//**
* Functions
******************************************************************************/

/*-----------------------------------------------------------------------------+
    IsStringNumber()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Evaluate string in a buffer if is a valid number write it on stack\n

    Conditions:
    - pCharBuf is a valid pointer
    - stack is running and not full

    \param[in] *pCharBuf  Pointer to a string
    \param[in] ulLen Number of characters which must be considered

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cDigit[]\n

    <B>Execution steps:</B><BR>
    - If the first character is '-' the string is a negative number
    - A length of 0 is no value
    When the sting is a correctly detected value
        - write value on the stack
        - return 1
    - else
        - return 0

    Error handling:
    - no

    \return Result, if the string is a valid number
    - 0 string is no number
    - 1 string is a number and on stack
*/
/*----------------------------------------------------------------------------*/
static unsigned long IsStringNumber ( char *pCharBuf , unsigned long ulLen)
{
    unsigned long i;
	unsigned long ii;
    unsigned long ulNumber;
    unsigned long ulSign;
    unsigned long ulFlag = 1;
    unsigned long ulFound = 0;
    unsigned long ulBase = 10;
    char cNextChar;

    cNextChar = *pCharBuf;

	ii = 0;
    ulNumber = 0;
    /* check sign */
    if ( (ulLen > 0) && (cNextChar == '-') )
    {
        ii++;
		pCharBuf++;
        ulSign = 1;         /* negative number*/
    }
    else
    {
        ulSign = 0;         /* positive number*/
    }

    while ((ii < ulLen) && (ulFlag == 1))
    {
        ulNumber *= ulBase;
        ulFound = 0;

        i = 0;
        cNextChar = *pCharBuf++;

        while (( i < ulBase) && (ulFound==0))
        {
            if (cNextChar == cDigit[i])
            {
                ulNumber += i;
                ulFound = 1;
            }
            i++;
        }
        if ( ulFound == 0 )
        {
            ulFlag = 0 ;
        }
		ii++;
    }

    if ( ulFound!=0 )
    {
        if (ulSign == 1 )
        {   /* convert into negative */
            ulNumber = ( 0xFFFFFFFFu - ulNumber + 1u);
        }
	push_Stack(ulNumber);
    }
    else
    {
        ulFlag = 0;
    }
    return ulFlag;
}
 

/*-----------------------------------------------------------------------------+
    StringNtToLong()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Convert a Null-terminated string into number\n

    Conditions:
    - pCharBuf is a valid pointer to a Null-terminated string

    \param[in] *pCharBuf  Pointer to a string

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cDigit[]\n

    <B>Execution steps:</B><BR>
    - If the first character is '-' the string is a negative number
    When the sting is a correctly detected value
        - return value of the string
    - else
        - return 0

    Error handling:
    - no

    \return Result, if the string is a valid number
    - 0 string is no number or number 0
    - !=0 number value of the string
*/
/*----------------------------------------------------------------------------*/
long StringNtToLong (char *pCharBuf)
{
    unsigned long i;
    unsigned long ulNumber;
    unsigned long ulSign;
    unsigned long ulFlag = 1;
    unsigned long ulFound = 0;
    unsigned long ulBase = 10;
    char cNextChar;

    cNextChar = *pCharBuf;

    ulNumber = 0;
    /* check sign */
    if ( (*pCharBuf != 0) && (cNextChar == '-') )
    {
        pCharBuf++;
        ulSign = 1;         /* negative number*/
    }
    else
    {
        ulSign = 0;         /* positive number*/
    }

    while ((*pCharBuf != 0 ) && (ulFlag==1))
    {
        ulNumber *= ulBase;
        ulFound = 0;

        i = 0;
        cNextChar = *pCharBuf++;

        while (( i < ulBase) && (ulFound==0))
        {
            if (cNextChar == cDigit[i])
            {
                ulNumber += i;
                ulFound = 1;
            }
            i++;
        }
        if ( ulFound == 0 )
        {
            ulFlag = 0 ;
        }
    }

    if ( ulFound!=0 )
    {
        if (ulSign == 1 )
        {   /* convert into negative */
            ulNumber = ( 0xFFFFFFFFu - ulNumber + 1u);
        }

    }
    else
    {
        ulFlag = 0;
        ulNumber = 0;
    }
    return ulNumber;
}


/*-----------------------------------------------------------------------------+
    StringToLong()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Convert string into number\n

    Conditions:
    - pCharBuf is a valid pointer

    \param[in] *pCharBuf  Pointer to a string
    \param[in] ulLen Number of characters which must be considered

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cDigit[]\n

    <B>Execution steps:</B><BR>
    - If the first character is '-' the string is a negative number
    - A length of 0 is no value
    When the sting is a correctly detected value
        - return value of the string
    - else
        - return 0

    Error handling:
    - no

    \return Result, if the string is a valid number
    - 0 string is no number or number 0
    - Not 0, number value of the string
*/
/*----------------------------------------------------------------------------*/
long StringToLong (char *pCharBuf, unsigned long ulLen)
{
    unsigned long i;
	unsigned long ii;
    unsigned long ulNumber;
    unsigned long ulSign;
    unsigned long ulFlag = 1;
    unsigned long ulFound = 0;
    unsigned long ulBase = 10;
    char cNextChar;

    cNextChar = *pCharBuf;

	ii = 0;
    ulNumber = 0;
    /* check sign */
    if ( (ulLen > 0) && (cNextChar == '-') )
    {
        ii++;
		pCharBuf++;
        ulSign = 1;         /* negative number*/
    }
    else
    {
        ulSign = 0;         /* positive number*/
    }

    while ((ii < ulLen) && (ulFlag == 1))
    {
        ulNumber *= ulBase;
        ulFound = 0;

        i = 0;
        cNextChar = *pCharBuf++;

        while (( i < ulBase) && (ulFound==0))
        {
            if (cNextChar == cDigit[i])
            {
                ulNumber += i;
                ulFound = 1;
            }
            i++;
        }
        if ( ulFound == 0 )
        {
            ulFlag = 0 ;
        }
		ii++;
    }

    if ( ulFound!=0 )
    {
        if (ulSign == 1 )
        {   /* convert into negative */
            ulNumber = ( 0xFFFFFFFFu - ulNumber + 1u);
        }
    }
    else
    {
        ulFlag = 0;
        ulNumber = 0;
    }
    return ulNumber;
}


/*-----------------------------------------------------------------------------+
    StackToNtString()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Pop number from stack and convert it into a null-terminated string,\n
    return length of the string.

    Conditions:
    - pCharBuf is a valid pointer
    - stack is running and not empty

    \param[in] *pCharBuf   pointer to the string buffer

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          cDigit[]\n

    <B>Execution steps:</B><BR>
    - read value from stack and convert it into string
    - write null-terminated string into Buffer
    - return length of the string
    - else
        - return 0

    Error handling:
    - no

    \return Result, if the string is a valid number
    - length of the string
*/
/*----------------------------------------------------------------------------*/
unsigned long StackToNtString(char * const pCharBuf)
{
    unsigned long const ulBase = 10;
    char *pTemp;
	long lStackVar;
    long lShifter;
	unsigned long ulReturn = 0;
	
	pTemp = pCharBuf;
	lStackVar = pop_Stack();
    if(lStackVar < 0)
	{
        *pTemp++ = '-';
		ulReturn++;
        lStackVar = lStackVar*(-1);
    }
    lShifter = lStackVar;
    do
	{ /* Move to end of string */
		ulReturn++;
        ++pTemp;
        lShifter = lShifter/ulBase;
    } while(lShifter != 0);
	/* write null-termination */
    *pTemp = '\0';

    do
	{ /* Move back and inserting digits */
        *--pTemp = cDigit[lStackVar%ulBase];
        lStackVar = lStackVar/ulBase;
    }while(lStackVar != 0);
	return ulReturn;
}
