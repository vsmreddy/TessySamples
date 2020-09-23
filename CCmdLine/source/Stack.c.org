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
*            $Revision 1.0.3$                                                \n
*                                                                            \n
*******************************************************************************
*
* \file      Stack.c
* \date      $Date: 13.09.2018$
*
*******************************************************************************
* \brief
*   Simulation of a microprocessor stack
*  
*******************************************************************************
* History:
* 13.09.2018 update of the specification
* 24.06.2013 initial revision
*******************************************************************************/

/**************************************************************************//**
* Includes
******************************************************************************/
#include "Stack.h"

/**************************************************************************//**
* Global functions
******************************************************************************/

/**************************************************************************//**
* Global variables
******************************************************************************/
tuErrorState uErrorState;

/**************************************************************************//**
* Local functions
******************************************************************************/

/**************************************************************************//**
* Local variables
******************************************************************************/
static unsigned long ulStack[STACKMAX];     /* Stack array to simulate a stack */
static unsigned long ulStackCounter;        /* Current stack position */
static unsigned long ulErrorState;          /* Error state, every bit is an error flag */
static teStackState eStackState = INIT; /* Stack state, indicates the status of the stack */

/**************************************************************************//**
* External functions
******************************************************************************/
/* Message on the UART */
extern void print_f(char* pChar);

/**************************************************************************//**
* External variables
******************************************************************************/

/**************************************************************************//**
* Functions
******************************************************************************/

/*-----------------------------------------------------------------------------+
    Init_Stack()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Initialize Stack module\n

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          ulStack[]\n
          ulErrorState\n
          ulStackCounter\n
          eStackState\n

    <B>Execution steps:</B><BR>
    Operation:
    - Set the stack pointer to 0
    - Initialize the full stack with 0
    - Clear error bits
    - Clear error state
    - Set stack state to RUNNING
*/
/*----------------------------------------------------------------------------*/
void Init_Stack(void)
{
    int i;

    for (i=0; i<STACKMAX; i++)
    {
        ulStack[i]=0;
    }
    ulErrorState        = ERR_no_error;
    uErrorState.ulValue = ERR_no_error;
    ulStackCounter      = 0;
    eStackState         = RUNNING;
}


/*-----------------------------------------------------------------------------+
    pop_Stack()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read value from top of the stack and return it\n

    Decrement the stack pointer and return the value from the top of the stack
    
    Conditions:
    - status of the stack is RUNNING
    - stack is not empty

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          ulStack[]\n
          ulErrorState\n
          ulStackCounter\n
          eStackState\n

    <B>Execution steps:</B><BR>
    Read value from top of the stack
    - stack state is RUNNING
    - stack counter is not Null

    Error handling:
    - Stack pointer is not changed
    - Call function print_f to print an error message on the UART
    - Set stack_underflow in ulErrorState
    - Set bit uErrorState.ulBits.stack_underflow
    - Set eStackState to ERROR
    - Set bit uErrorState.ulBits.stack_state_wrong
    - Return 0
    \return value from top of the stack or Null
*/
/*----------------------------------------------------------------------------*/
unsigned long pop_Stack(void)
{
    /* Definition and initialisation of the return value */
    unsigned long ulReturn = 0u;

    /* Check stack state */
    if (eStackState != RUNNING) 
	{
	    /* Write error message and set error flag */
        print_f ("Wrong stack state during pop stack!");
        ulErrorState |= ERR_stack_state;
        uErrorState.ulBits.stack_state_wrong = 1;
		eStackState = ERROR;
	}
    /* Check stack counter */
	else if (ulStackCounter == 0u)
	{
	    /* Write error message and set error flag */
        print_f ("Stack underflow!");
        ulErrorState |= ERR_stack_underflow;
        uErrorState.ulBits.stack_underflow = 1;
        eStackState = ERROR;
        uErrorState.ulBits.stack_state_wrong = 1;
	}
	else
    {
        /* Read value from top of stack */
        ulReturn = ulStack[--ulStackCounter];
    }
    return ulReturn;
}


/*-----------------------------------------------------------------------------+
    peek_Stack()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read value from top of the stack and return it\n

    Do not decrement the stack pointer and return the value from the top of the stack
    
    Conditions:
    - status of the stack is RUNNING
    - stack is not empty

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          ulStack[]\n
          ulErrorState\n
          ulStackCounter\n
          eStackState\n

    <B>Execution steps:</B><BR>
    Read value from top of the stack
    - stack state is RUNNING
    - Stack pointer is not changed

    Error handling:
    - Call function print_f to print an error message on the UART
    - Set stack_underflow in ulErrorState
    - Set bit uErrorState.ulBits.stack_underflow
    - Set eStackState to ERROR
    - Set bit uErrorState.ulBits.stack_state_wrong
    - Return 0
    \return value from top of the stack or Null
*/
/*----------------------------------------------------------------------------*/
unsigned long peek_Stack(void)
{
    /* Definition and initialisation of the return value */
    unsigned long ulReturn = 0u;

    /* Check stack counter */
    if (eStackState != RUNNING) 
	{
	    /* Write error message and set error flag */
        print_f ("Wrong stack state during peek stack!");
        ulErrorState |= ERR_stack_state;
        uErrorState.ulBits.stack_state_wrong = 1;
        eStackState = ERROR;
	}
    /* Check stack state */
	else if (ulStackCounter == 0u)
	{
	    /* Write error message and set error flag */
        print_f ("Stack underflow!");
        ulErrorState |= ERR_stack_underflow;
        uErrorState.ulBits.stack_underflow = 1;
        eStackState = ERROR;
        uErrorState.ulBits.stack_state_wrong = 1;
	}
	else
    {
        /* Read value from top of stack */
        ulReturn = ulStack[ulStackCounter - 1];
    }
    return ulReturn;
}


/*-----------------------------------------------------------------------------+
    push_Stack()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Save the parameter on the top of the stack\n

    Conditions:
    - status of the stack is RUNNING
    - stack is not empty

    \param[in] ulValue   value which should be saved on top of the stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          ulStack[]\n
          ulErrorState\n
          ulStackCounter\n
          eStackState\n

    <B>Execution steps:</B><BR>
    Save the parameter on the top of the stack:
    - first write the value to Stack
    - next increment the stack pointer (ulStackCounter)

    Error handling:
    - Don't save the value on the stack.
    - Don't increment the stack pointer.
    - Call the function print_f to provide an error message on the UART
    - Set ERROR_data_stack_overflow in ulErrorState
    - Set uErrorState.ulBits.data_stack_overflow to 1
    \return value from top of the stack or Null
*/
/*----------------------------------------------------------------------------*/
void push_Stack(unsigned long ulValue)
{
    /* Check stack counter */
    if (eStackState != RUNNING) 
	{
	    /* Write error message and set error flag */
        print_f ("Wrong stack state during push stack!");
        ulErrorState |= ERR_stack_state;
        uErrorState.ulBits.stack_state_wrong = 1;
        eStackState = ERROR;
	}
    /* Check if stack is full */
    else if (ulStackCounter >= STACKMAX)
    {
        /* Set error flag and write error message to UART */
        ulErrorState |= ERR_stack_overflow;
        uErrorState.ulBits.stack_overflow = 1;
        print_f ("Stack overflow");
        eStackState = ERROR;
    }
    else
    {
        /* Write value on top of stack and increment stack counter */
        ulStack[ulStackCounter++] = ulValue;
    }
}


/*-----------------------------------------------------------------------------+
    stack_Addition()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read two values from the top of the stack, add it and write the result back on the stack.\n

    Conditions:
    - valid values on stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n

    <B>Execution steps:</B><BR>
    - read two values from stack
    - add the values
    - write result on stack

    Error handling:
    - nothing
*/
/*----------------------------------------------------------------------------*/
void stack_Addition(void)
{
    unsigned long VarA;
    unsigned long VarB;

    VarA = pop_Stack();
    VarB = pop_Stack();
    /* Calculate sum and write back on stack */
    push_Stack(VarA + VarB);
}


/*-----------------------------------------------------------------------------+
    stack_Subtraction()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read two values from the top of the stack, calc the difference and write the result back on the stack.\n

    Conditions:
    - valid values on stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n

    <B>Execution steps:</B><BR>
    - read two values from stack
    - subtract second value from first one and write result on stack

    Error handling:
    - nothing
*/
/*----------------------------------------------------------------------------*/
void stack_Subtraction(void)
{
    /* Calculate difference and write back on stack */
    push_Stack(pop_Stack() - pop_Stack());
}



#if (DIVISION == 1)
/*-----------------------------------------------------------------------------+
    stack_Division()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read two values from the top of the stack, divide it and write the result back on the stack.\n

    Conditions:
    - valid values on stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n

    <B>Execution steps:</B><BR>
    - read two values from stack
    - divide second value from first one and write result on stack

    Error handling:
    - nothing
*/
/*----------------------------------------------------------------------------*/
void stack_Division(void)
{
    unsigned long VarA;
    unsigned long VarB;

    VarA = pop_Stack();
    VarB = pop_Stack();
	/* Calculate division and write back on stack */
    push_Stack(VarA / VarB);
}
#endif


#if (MULTIPLICATION == 1)
/*-----------------------------------------------------------------------------+
    stack_Multiplication()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read two values from the top of the stack, calc the multiplication and write the result back on the stack.\n

    Conditions:
    - valid values on stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n

    <B>Execution steps:</B><BR>
    - read two values from stack
    - multiply it and write result on stack

    Error handling:
    - nothing
*/
/*----------------------------------------------------------------------------*/
void stack_Multiplication(void)
{
    unsigned long VarA;
    unsigned long VarB;
    unsigned long VarC;

	/* Get Values from stack */
    VarA = pop_Stack();
    VarB = pop_Stack();

	/* Calculate multiplication and write back on stack */
	VarC = VarA * VarB;
    push_Stack(VarC);
}
#endif


/*-----------------------------------------------------------------------------+
    pop_pStack()
+-----------------------------------------------------------------------------*/
/*!
    <B>Description</B><BR>
    Read value from top of the stack and return it\n

    Decrement the stack pointer and return the value from the top of the stack
    
    Conditions:
    - status of the stack is RUNNING
    - stack is not empty

    \param[in] pStack    Pointer to stack

    \pre  nothing\n

    \post nothing\n

    \note Used global variables\n
          ulStack[]\n
          ulErrorState\n
          ulStackCounter\n
          eStackState\n

    <B>Execution steps:</B><BR>
    Read value from top of the stack
    - stack state is RUNNING
    - stack counter is not Null

    Error handling:
    - Stack pointer is not changed
    - Call function print_f to print an error message on the UART
    - Set stack_underflow in ulErrorState
    - Set bit uErrorState.ulBits.stack_underflow
    - Set eStackState to ERROR
    - Set bit uErrorState.ulBits.stack_state_wrong
    - Return 0
    \return value from top of the stack or Null
*/
/*----------------------------------------------------------------------------*/
unsigned long pop_pStack(unsigned long *pStack)
{
    /* Definition and initialisation of the return value */
    unsigned long ulReturn = 0u;

    /* Check stack counter */
    if (eStackState != RUNNING) 
	{
	    /* Write error message and set error flag */
        print_f ("Wrong stack state during pop stack!");
        ulErrorState |= ERR_stack_state;
        uErrorState.ulBits.stack_state_wrong = 1;
		eStackState = ERROR;
	}
    /* Check stack state */
	else if (ulStackCounter == 0u)
	{
	    /* Write error message and set error flag */
        print_f ("Stack underflow!");
        ulErrorState |= ERR_stack_underflow;
        uErrorState.ulBits.stack_underflow = 1;
        eStackState = ERROR;
        uErrorState.ulBits.stack_state_wrong = 1;
	}
	else
    {
        /* Read value from top of stack */
		ulStackCounter--;
        ulReturn = *(pStack + ulStackCounter);
    }
    return ulReturn;
}


/************************************ EOF ************************************/
