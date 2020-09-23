/**************************************************************************//**
*
* <b>Project:   TESSY Seminar </b>
*
* \author    $Author: Razorcat Development GmbH$                                     \n
*            Razorcat Development GmbH                                       \n
*            Witzlebenplatz 4                                                \n
*            D-14057 Berlin                                                  \n
*            http://www.razorcat.com                                         \n
*                                                                            \n
*            $Revision 1.0.2$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      Stack.h
* \date      $Date: 12.07.2013$
*
*******************************************************************************
* \brief
*  Header of Stack.c
*  
*******************************************************************************
* History:
* 24.06.2013 initial revision
* 12.07.2013 last changes
*******************************************************************************/
#ifndef _STACK_H_
#define _STACK_H_

/**************************************************************************//**
* Include files
******************************************************************************/

/**************************************************************************//**
* Defines
******************************************************************************/
/* Enable functions  */
#define DIVISION          0  /* 1 = stack_Division() enabled, 0 = disabled   */
#define MULTIPLICATION    1  /* stack_Multiplication() enabled, 0 = disabled */

/* Error Flags  */
#define ERR_no_error              0x0000  /* Error Flag: no error */
#define ERR_stack_init            0x0001  /* Error Flag: stack initialisation */
#define ERR_stack_state           0x0002  /* Error Flag: stack state */
#define ERR_stack_underflow       0x0003  /* Error Flag: stack underflow */
#define ERR_stack_overflow        0x0004  /* Error Flag: stack overflow */
#define ERR_undefined             0x0005  /* Error Flag: undefined error */

/* Stack depth */
#define STACKMAX 30                       /* Depth of the data stack */

/* Alias names */
#define ERR_VALUE       uErrorState.ulValue
#define ERR_UNDERFLOW   uErrorState.ulBits.stack_underflow
#define ERR_OVERFLOW    uErrorState.ulBits.stack_overflow
#define ERR_STACKSTATE  uErrorState.ulBits.stack_state_wrong

/**************************************************************************//**
* Types
******************************************************************************/
/* Union for the error flags */
typedef union uErrorStates
{
    unsigned long ulValue;
    struct
    {
        unsigned long init_fail            : 1;     /* Error Flag: stack initialisation fails */
        unsigned long stack_state_wrong    : 1;     /* Error Flag: wrong stack state */
        unsigned long stack_underflow      : 1;     /* Error Flag: data stack underflow */
        unsigned long stack_overflow       : 1;     /* Error Flag: data stack overflow */
        unsigned long undefined            : 1;     /* Error Flag: undefined error */
    } ulBits;
} tuErrorState;

/* Enumeration to define the stack state */
typedef enum eStackStates
{
    INIT,            /* stack is not initialised */
    RUNNING,         /* stack is running */
    ERROR            /* stack error */
} teStackState;

/**************************************************************************//**
* Variables
******************************************************************************/

/**************************************************************************//**
* Prototypes
******************************************************************************/
extern void Init_Stack(void);
extern void push_Stack(unsigned long ulValue);
extern unsigned long peek_Stack(void);
extern unsigned long pop_Stack(void);
extern void stack_Addition(void);

#endif /* _STACK_H_ */

/************************************ EOF ************************************/
