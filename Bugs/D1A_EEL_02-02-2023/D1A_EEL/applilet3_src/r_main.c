/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/D1A V2.04.05.02 [08 Nov 2021]
* Device(s)    : R5F10DPJ
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 19-10-2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "fdl.h"
#include "fdl_descriptor.h"
#include "fdl_types.h"
#include "eel.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"
#include "eel_types.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
   unsigned long ODO_Val,R_ODO_Val;
   unsigned long TripA_Val,R_TripA_Val;
    
   unsigned long R_TripB_Val=23;
   unsigned long TripB_Val=5;
   unsigned long Read;
   unsigned long Write = 385;
   unsigned long Read_ID = 1;
   unsigned long Write_ID = 1;

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
{
    eel_request_t requester;
    uint8_t       read_id;
    uint8_t       ret;
    uint8_t       i;
    int8_t        buff[10];
    
    ret = R_EEL_Initialize();		/* Initialize EEL */
    ret = R_EEL_ExecuteWrite(Write,Write_ID);
    ret = R_EEL_ExecuteRead(&Read,Read_ID);
    ret = R_EEL_Close();     		/* Close EEPROM emulation */
    
    ret = R_EEL_ExecuteWrite(Write,Write_ID);
    ret = R_EEL_ExecuteRead(&Read,Read_ID);
    
    ODO_Val=300000;			/* Sample Data to be store */
    TripA_Val=324522;
    TripB_Val=234234;
    
    
    
    for (i=1;i<=20;i++)
    {

	ODO_Val = ODO_Val + (i*2);
	ret = R_EEL_ExecuteWrite(ODO_Val,ODO_ID);
	ret = R_EEL_ExecuteRead(&R_ODO_Val,ODO_ID);
	
	TripA_Val += i * 13;
	ret = R_EEL_ExecuteWrite(TripA_Val,TRIPA_ID);
	ret = R_EEL_ExecuteRead(&R_TripA_Val,TRIPA_ID);

	ret = R_EEL_ExecuteRead(&R_ODO_Val,ODO_ID);
	
	TripB_Val =  i;
	ret = R_EEL_ExecuteWrite(TripB_Val,TRIPB_ID);			
	ret = R_EEL_ExecuteRead(&R_TripB_Val,TRIPB_ID);	
	
    }
	
	
}
    while (1U);

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
