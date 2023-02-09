;*******************************************************************************
; Library       : EEPROM Emulation Library (T02)
;
; File Name     : $Source: eel_types.inc $
; Lib. Version  : $RL78_EEL_LIB_VERSION_T02_CCRL: V1.00 $
; Mod. Revision : $Revision: 1.4 $
; Mod. Date     : $Date: 2015/03/18 11:03:34MEZ $
; Device(s)     : RL78
; Description   : API definition of the EEPROM Emulation Library T02 (EEL)
;******************************************************************************
; DISCLAIMER
; This software is supplied by Renesas Electronics Corporation and is only
; intended for use with Renesas products. No other uses are authorized. This
; software is owned by Renesas Electronics Corporation and is protected under
; all applicable laws, including copyright laws.
; THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
; THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
; LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
; AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
; TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
; ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
; FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
; ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
; BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; Renesas reserves the right, without notice, to make changes to this software
; and to discontinue the availability of this software. By using this software,
; you agree to the additional terms and conditions found by accessing the
; following link:
; http://www.renesas.com/disclaimer
;
; Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
;*******************************************************************************


$IFDEF __EEL_TYPES_INC_INCLUDED

$ELSE
__EEL_TYPES_INC_INCLUDED .SET 1

;*******************************************************************************
; BEGIN OF CUSTOMIZABLE DECLARATION AREA
;*******************************************************************************

; Base number prefix/suffix mode selection for Assembler
; Numbers definition within the prefix mode: 0x05 
; Numbers definition within the suffix mode: 05H
;
; Suffix mode will be activated in case the symbol __EEL_TYPES_INC_BASE_NUMBER_SUFFIX  
; is defined. The definition of this symbol can be done by
; - un-commenting the line below or 
; - using the assembler command line option -D__EEL_TYPES_INC_BASE_NUMBER_SUFFIX or
; - by setting the define within the IDE

;__EEL_TYPES_INC_BASE_NUMBER_SUFFIX .SET 1
;*******************************************************************************
; END OF CUSTOMIZABLE DECLARATION AREA
;*******************************************************************************



;*******************************************************************************
; BEGIN OF UNTOUCHABLE DECLARATION AREA
;*******************************************************************************
$IFNDEF __EEL_TYPES_INC_BASE_NUMBER_SUFFIX
    ; EEL command code definitions
    ; -----------------------------------------------------
    EEL_CMD_UNDEFINED                 .EQU     (0x00)
    EEL_CMD_STARTUP                   .EQU     (0x00 | 0x01)
    EEL_CMD_WRITE                     .EQU     (0x00 | 0x02)
    EEL_CMD_READ                      .EQU     (0x00 | 0x03)
    EEL_CMD_REFRESH                   .EQU     (0x00 | 0x04)
    EEL_CMD_VERIFY                    .EQU     (0x00 | 0x05)
    EEL_CMD_FORMAT                    .EQU     (0x00 | 0x06)
    EEL_CMD_SHUTDOWN                  .EQU     (0x00 | 0x07)


    ; EEL driver operation status code definition
    ; -----------------------------------------------------
    EEL_DRIVER_PASSIVE                .EQU     (0x00 | 0x00)
    EEL_DRIVER_IDLE                   .EQU     (0x30 | 0x01)
    EEL_DRIVER_BUSY                   .EQU     (0x30 | 0x02)


    ; EEL error code definitions
    ; -----------------------------------------------------
    EEL_OK                            .EQU     (0x00 | 0x00)
    EEL_BUSY                          .EQU     (0x00 | 0x01)
    EEL_ERR_CONFIGURATION             .EQU     (0x80 | 0x02)
    EEL_ERR_INITIALIZATION            .EQU     (0x80 | 0x03)
    EEL_ERR_ACCESS_LOCKED             .EQU     (0x80 | 0x04)
    EEL_ERR_PARAMETER                 .EQU     (0x80 | 0x05)
    EEL_ERR_VERIFY                    .EQU     (0x80 | 0x06)
    EEL_ERR_REJECTED                  .EQU     (0x80 | 0x07)
    EEL_ERR_NO_INSTANCE               .EQU     (0x80 | 0x08)
    EEL_ERR_POOL_FULL                 .EQU     (0x80 | 0x09)
    EEL_ERR_POOL_INCONSISTENT         .EQU     (0x80 | 0x0A)
    EEL_ERR_POOL_EXHAUSTED            .EQU     (0x80 | 0x0B)
    EEL_ERR_INTERNAL                  .EQU     (0x80 | 0x0C)


    ; byte index within EEL-request structure
    ; -----------------------------------------------------
    EEL_REQUEST_ADDR                  .EQU     (0x00)
    EEL_REQUEST_IDENTIFIER            .EQU     (0x02)
    EEL_REQUEST_COMMAND               .EQU     (0x03)
    EEL_REQUEST_ERROR                 .EQU     (0x04)

$ELSE
    ; EEL command code definitions
    ; -----------------------------------------------------
    EEL_CMD_UNDEFINED                 .EQU     (00H)
    EEL_CMD_STARTUP                   .EQU     (000H | 001H)
    EEL_CMD_WRITE                     .EQU     (000H | 002H)
    EEL_CMD_READ                      .EQU     (000H | 003H)
    EEL_CMD_REFRESH                   .EQU     (000H | 004H)
    EEL_CMD_VERIFY                    .EQU     (000H | 005H)
    EEL_CMD_FORMAT                    .EQU     (000H | 006H)
    EEL_CMD_SHUTDOWN                  .EQU     (000H | 007H)


    ; EEL driver operation status code definition
    ; -----------------------------------------------------
    EEL_DRIVER_PASSIVE                .EQU     (000H | 000H)
    EEL_DRIVER_IDLE                   .EQU     (030H | 001H)
    EEL_DRIVER_BUSY                   .EQU     (030H | 002H)


    ; EEL error code definitions
    ; -----------------------------------------------------
    EEL_OK                            .EQU     (000H | 000H)
    EEL_BUSY                          .EQU     (000H | 001H)
    EEL_ERR_CONFIGURATION             .EQU     (080H | 002H)
    EEL_ERR_INITIALIZATION            .EQU     (080H | 003H)
    EEL_ERR_ACCESS_LOCKED             .EQU     (080H | 004H)
    EEL_ERR_PARAMETER                 .EQU     (080H | 005H)
    EEL_ERR_VERIFY                    .EQU     (080H | 006H)
    EEL_ERR_REJECTED                  .EQU     (080H | 007H)
    EEL_ERR_NO_INSTANCE               .EQU     (080H | 008H)
    EEL_ERR_POOL_FULL                 .EQU     (080H | 009H)
    EEL_ERR_POOL_INCONSISTENT         .EQU     (080H | 00AH)
    EEL_ERR_POOL_EXHAUSTED            .EQU     (080H | 00BH)
    EEL_ERR_INTERNAL                  .EQU     (080H | 00CH)


    ; byte index within EEL-request structure
    ; -----------------------------------------------------
    EEL_REQUEST_ADDR                  .EQU     (000H)
    EEL_REQUEST_IDENTIFIER            .EQU     (002H)
    EEL_REQUEST_COMMAND               .EQU     (003H)
    EEL_REQUEST_ERROR                 .EQU     (004H)
$ENDIF
;*******************************************************************************
; END OF UNTOUCHABLE DECLARATION AREA
;*******************************************************************************

$ENDIF
