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
* File Name    : r_cg_userdefine.h
* Version      : Applilet3 for RL78/D1A V2.04.05.02 [08 Nov 2021]
* Device(s)    : R5F10DPJ
* Tool-Chain   : CCRL
* Description  : This file includes user definition.
* Creation Date: 19-10-2022
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
#define EEL_NG              (0x01)    /* Fail to EEPROM emulation */
#define EEL_MODE_ENFORCED   (0xFF)    /* Enforced mode */
#define EEL_MODE_POLLING    (0x00)    /* Polling mode */

#define ODO_ID 		0x01
#define TRIPA_ID 	0x02
#define TRIPB_ID 	0x03
#define ODO_OVER_ID 	0x04

uint8_t R_EEL_Initialize(void);
void    R_EEL_Maintenance(void);
uint8_t R_EEL_ClearDataFlash(void);
uint8_t R_EEL_Close(void);
uint8_t R_EEL_ExecuteWrite(unsigned long Val, unsigned char Id);
//uint8_t R_EEL_ExecuteRead(unsigned char Id);
uint8_t R_EEL_ExecuteRead(unsigned long* Val, unsigned char Id);

extern uint8_t Read_value[4];

/* End user code. Do not edit comment generated here */
#endif
