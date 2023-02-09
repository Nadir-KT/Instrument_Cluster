/*******************************************************************************
* Library       : EEPROM Emulation Library (T02)
*
* File Name     : $Source: eel_types.h $
* Lib. Version  : $RL78_EEL_LIB_VERSION_T02_CCRL: V1.00 $
* Mod. Revision : $Revision: 1.3 $
* Mod. Date     : $Date: 2015/03/11 16:09:45MEZ $
* Device(s)     : RL78
* Description   : type definitions of the EEPROM Emulation Library (EEL)
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

#ifndef __EEL_TYPES_H_INCLUDED
#define __EEL_TYPES_H_INCLUDED


/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       eel_u08;
typedef unsigned int                        eel_u16;
typedef unsigned long int                   eel_u32;


/*==============================================================================================*/
/* global constant definitions                                                                  */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/



/* EEL command set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_CMD_UNDEFINED         = (0x00 | 0x00),  /* 0x00, undefined command (initial value)              */
                EEL_CMD_STARTUP           = (0x00 | 0x01),  /* 0x01, plausibility check of the EEL data and driver  */
                EEL_CMD_WRITE             = (0x00 | 0x02),  /* 0x02, creates a new instance of EEL variable         */
                EEL_CMD_READ              = (0x00 | 0x03),  /* 0x03, reads last instance of the EEL variable        */
                EEL_CMD_REFRESH           = (0x00 | 0x04),  /* 0x04, copy all last instances into a new active block*/
                EEL_CMD_VERIFY            = (0x00 | 0x05),  /* 0x05, verifies electrically byte by byte the         */
                                                            /*       complete active block                          */
                EEL_CMD_FORMAT            = (0x00 | 0x06),  /* 0x06, format the EEL pool, all instances are lost    */
                EEL_CMD_SHUTDOWN          = (0x00 | 0x07)   /* 0x07, deactivates the EEL in secure state            */
              } eel_command_t;                              /* ---------------------------------------------------- */


/* type of the EEL driver operation status */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_DRIVER_PASSIVE        = (0x00 | 0x00),  /* 0x00, when library is not yet started                */
                EEL_DRIVER_IDLE           = (0x30 | 0x01),  /* 0x31, no command is being executed                   */
                EEL_DRIVER_BUSY           = (0x30 | 0x02)   /* 0x32, any command is just being executed             */
              } eel_driver_status_t;                        /* ---------------------------------------------------- */


/* EEL status set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_OK                    = (0x00 | 0x00),  /* 0x00, no error occurred                              */
                EEL_BUSY                  = (0x00 | 0x01),  /* 0x01, request is under processing                    */
                EEL_ERR_CONFIGURATION     = (0x80 | 0x02),  /* 0x82, bad FDL or EEL configuration                   */
                EEL_ERR_INITIALIZATION    = (0x80 | 0x03),  /* 0x83, EEL_Init(), EEL_Open missed                    */
                EEL_ERR_ACCESS_LOCKED     = (0x80 | 0x04),  /* 0x84, STARTUP missing or fatal operation error       */
                EEL_ERR_PARAMETER         = (0x80 | 0x05),  /* 0x85, wrong parameter (wrong command or identifier)  */
                EEL_ERR_VERIFY            = (0x80 | 0x06),  /* 0x86, verify error on any byte in active block       */
                EEL_ERR_REJECTED          = (0x80 | 0x07),  /* 0x87, another request already under processing       */
                EEL_ERR_NO_INSTANCE       = (0x80 | 0x08),  /* 0x88, no instance found (variable never written)     */
                EEL_ERR_POOL_FULL         = (0x80 | 0x09),  /* 0x89, no space for writing data                      */
                EEL_ERR_POOL_INCONSISTENT = (0x80 | 0x0A),  /* 0x8A, no active block found within EEL-pool          */
                EEL_ERR_POOL_EXHAUSTED    = (0x80 | 0x0B),  /* 0x8B, EEL pool to small for correct operation        */
                EEL_ERR_INTERNAL          = (0x80 | 0x0C)   /* 0x8C, internal error (should never occur)            */
              } eel_status_t;                               /* ---------------------------------------------------- */


/* EEL request type */
typedef struct {                                            /* ---------------------------------------------------- */
                  __near eel_u08*       address_pu08;       /* 2, r/w, source/destination RAM-address               */
                         eel_u08        identifier_u08;     /* 1, w,   variable identifier                          */
                         eel_command_t  command_enu;        /* 1, w,   command has to be processed                  */
                         eel_status_t   status_enu;         /* 1, r,   error code after command execution           */
                } eel_request_t;                            /* ---------------------------------------------------- */
                                                            /* 5 bytes in total                                     */
							    
/* type of the internal EEL driver status */
//typedef struct {                                              /* -------------------------------------------------- */
//                 eel_operation_status_t eel_driver_status_t;  /* 1, operation status of the EEL driver              */
//                 eel_access_status_t    accessStatus_enu;     /* 1, access rights indicator                         */
//                 eel_status_t           backgroundStatus_enu; /* 1, error status of the background process          */
//               } eel_driver_status_t;                         /* -------------------------------------------------- */
//                                                              /* 3 bytes in total    							    


/*==============================================================================================*/
/* type definition plausibility check                                                           */
/*==============================================================================================*/

/* The following checks are implemented in order to check the correct size of the EEL type      */
/* definitions at compile time. In case of a compilation error in the following lines, please   */
/* check your compiler options for enumeration types and structures and contact your local      */
/* support, if necessary.                                                                       */

#define R_EELT02_ASSERT_CONCAT_(a, b) a##b
#define R_EELT02_ASSERT_CONCAT(a, b) R_EELT02_ASSERT_CONCAT_(a, b)
#define R_EELT02_STATIC_ASSERT(e) enum { R_EELT02_ASSERT_CONCAT(R_EELT02_ASSERT_LINE_, __LINE__) = 1/(!!(e)) }


/* assertion if unsigned data type size is not correct, please evaluate compiler settings for integer types */
R_EELT02_STATIC_ASSERT(sizeof(eel_u08)==1);
R_EELT02_STATIC_ASSERT(sizeof(eel_u16)==2);
R_EELT02_STATIC_ASSERT(sizeof(eel_u32)==4);

/* assertion if enumeration type size is not correct, please evaluate compiler settings for enumeration types */
R_EELT02_STATIC_ASSERT(sizeof(eel_command_t)==1);
R_EELT02_STATIC_ASSERT(sizeof(eel_driver_status_t)==1);
R_EELT02_STATIC_ASSERT(sizeof(eel_status_t)==1);

/* assertion if structure type size is not correct, please evaluate compiler settings for structure types */
R_EELT02_STATIC_ASSERT(sizeof(eel_request_t)>=5);/* sizeof(eel_request_t) == 5 for packed structures */
R_EELT02_STATIC_ASSERT(sizeof(eel_request_t)<=6);/* sizeof(eel_request_t) == 6 for unpacked structures */


#endif
