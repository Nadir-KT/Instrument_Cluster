;*******************************************************************************
; Library       : Data Flash Access Library T02
;
; File Name     : $Source: fdl.inc $
; Lib. Version  : $RL78_FDL_LIB_VERSION_T02_CCRL: V1.01 $
; Mod. Revision : $Revision: 1.9 $
; Mod. Date     : $Date: 2015/03/19 08:17:45MEZ $
; Device(s)     : RL78
; Description   : Assembler API definition of the Flash Access Library
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
; Copyright (C) 2014, 2015 Renesas Electronics Corporation. All rights reserved.
;*******************************************************************************



$IFDEF __FDL_INC_INCLUDED

$ELSE
__FDL_INC_INCLUDED .SET 1



;*******************************************************************************
; BEGIN OF CUSTOMIZABLE DECLARATION AREA
;*******************************************************************************

; Base number prefix/suffix mode selection for Assembler
; Numbers definition within the prefix mode: 0x05 
; Numbers definition within the suffix mode: 05H
;
; Suffix mode will be activated in case the symbol __FDL_INC_BASE_NUMBER_SUFFIX  
; is defined. The definition of this symbol can be done by
; - un-commenting the line below or 
; - using the assembler command line option -D__FDL_INC_BASE_NUMBER_SUFFIX or
; - by setting the define within the IDE

;__FDL_INC_BASE_NUMBER_SUFFIX .SET 1
;*******************************************************************************
; END OF CUSTOMIZABLE DECLARATION AREA
;*******************************************************************************

  
  
;*******************************************************************************
; BEGIN OF UNTOUCHABLE DECLARATION AREA
;*******************************************************************************
;==============================================================================================
; constant definitions
;==============================================================================================

$IFNDEF __FDL_INC_BASE_NUMBER_SUFFIX
    ; FDL command code definitions
    ; -----------------------------------------------------

    FDL_CMD_READ_BYTES             .EQU     (0x00)
    FDL_CMD_IVERIFY_BYTES          .EQU     (0x01)
    FDL_CMD_BLANKCHECK_BYTES       .EQU     (0x02)
    FDL_CMD_WRITE_BYTES            .EQU     (0x03)
    FDL_CMD_ERASE_BLOCK            .EQU     (0x04)


    ; status code definitions returned by the FDL functions

    ; operation related status code
    FDL_OK                 .EQU       0x00
    FDL_BUSY               .EQU       0xFF
    FDL_ERR_INITIALIZATION .EQU       0x02
    FDL_ERR_REJECTED       .EQU       0x03
    FDL_ERR_ABORTED        .EQU       0x04
    FDL_ERR_PARAMETER      .EQU       0x05
    FDL_ERR_STANDBY        .EQU       0x06
    ; flash access related status code 
    FDL_ERR_ERASE          .EQU       0x1A
    FDL_ERR_BLANK_VERIFY   .EQU       0x1B
    FDL_ERR_WRITE          .EQU       0x1C
    ; configuration related status code
    FDL_ERR_CONFIGURATION  .EQU       0x01
$ELSE
    ; FDL command code definitions
    ; -----------------------------------------------------

    FDL_CMD_READ_BYTES             .EQU     (00H)
    FDL_CMD_IVERIFY_BYTES          .EQU     (01H)
    FDL_CMD_BLANKCHECK_BYTES       .EQU     (02H)
    FDL_CMD_WRITE_BYTES            .EQU     (03H)
    FDL_CMD_ERASE_BLOCK            .EQU     (04H)


    ; status code definitions returned by the FDL functions

    ; operation related status code
    FDL_OK                 .EQU       000H
    FDL_BUSY               .EQU       0FFH
    FDL_ERR_INITIALIZATION .EQU       002H
    FDL_ERR_REJECTED       .EQU       003H
    FDL_ERR_ABORTED        .EQU       004H
    FDL_ERR_PARAMETER      .EQU       005H
    FDL_ERR_STANDBY        .EQU       006H
    ; flash access related status code
    FDL_ERR_ERASE          .EQU       01AH
    FDL_ERR_BLANK_VERIFY   .EQU       01BH
    FDL_ERR_WRITE          .EQU       01CH
    ; configuration related status code
    FDL_ERR_CONFIGURATION  .EQU       001H
$ENDIF


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;   Purpose:      Initialization of the Flash Data Library.
;                 Several checks are performed during the initialization:
;                 - plausibility check of the pool configuration
;                 - frequency parameter check against supported device-specific range
;                 - initialization of all internal variables
;                 - initialization of the flash firmware
;                 - configuration of HOCO
;                 After initialization the FDL remains passive.
;                 FDL_Open() has to be executed to open access to the FDL pool.
;  Input:         DE = LOWW(descriptor)
;                  A = HIGH(descriptor)
;  Changed:       X, BC, DE, HL
;  Return:        A  = status: configuration related error code
;                 - FDL_OK:                 initialization done without problems
;                 - FDL_ERR_CONFIGURATION:  FDL pool-configuration error or HOCO isn't started
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Init


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Enable data flash access.
;                Pre-condition: The FDL initialization must be done before however no check is performed here.
;                If FDL is not yet initialized, FDL_Open() has no functionality.
;  Input:        -
;  Output:       -
;  Changed:      AX
;  Return:       -
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Open


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Disable data flash access.
;                Pre-condition: The initialization of the library must "opened" by the function FDL_Open.
;                If FDL is not yet "opened", the FDL_Close() has no functionality.
;                If any firmware command is just executed, FDL_Close will stop it by FW command first.
;                After that the flash clock is switched OFF.
;  Input:        -
;  Output:       -
;  Changed:      C
;  Return:       -
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Close


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Initiating execution of the FDL request related to the FDL pool part only.
;                The corresponding request variable has to be parameterized before.
;
;                my_request->index_u16        :   byte-index or block-number within FDL-pool
;                my_request->data_pu08        :   start address of the RAM data that should be read/written
;                my_request->bytecount_u16    :   number of bytes has to be passed in case of byte
;                                                 oriented commands
;                my_request->command_enu      :   command code
;                my_request->status_enu       :   request status
;
;  Input:        AX - pointer to request variable
;  Changed:      AX, BC, DE, HL
;  Output:       status inside the request variable
;  Return:       -
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Execute


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Continuation and status update of requests being under execution.
;                When no FDL request is being executed, this function has no functionality (idle).
;  Input:        -
;  Output:       status inside the request variable for command executed via FDL_Execute
;  Changed:      A, C, HL
;  Return:       -
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Handler


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      This function aborts immediately a potentially running block command (ERASE) independent
;                of the affected pool.
;  Input:        -
;  Output:       -
;  Changed:      BC, HL
;  Return:       A  = status:
;                - FDL_OK:                Either no command is running or erase has been aborted.
;                - FDL_BUSY:              Byte oriented command is still running.
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_Abort


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      This function stops the clock of the data flash and enters the library into StandBy mode.
;                Note :  It is not allowed to call any FDL function other than FDL_WakeUp when FDL is in
;                        StandBy mode.
;  Input:        -
;  Output:       -
;  Changed:      C, HL
;  Return:       A  = status:
;                - FDL_OK:                FDL entered StandBy mode.
;                - FDL_BUSY:              Any command is still running.
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_StandBy


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Continuation and status update of requests being under execution.
;                When no FDL request is being executed, this function has no functionality (idle).
;  Input:        -
;  Output:       -
;  Changed:      X
;  Return:       A  = status:
;                - FDL_OK:                FDL is up and running.
;                - FDL_ERR_REJECTED:      WakeUp cannot be performed.
;                                         REASON: Library isn't in StandBy mode.
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_WakeUp


; ---------------------------------------------------------------------------------------------------------------
;  Block type:   standard function
; ---------------------------------------------------------------------------------------------------------------
;  Purpose:      Return the start address of the library version string
;
;  Input:        -
;  Output:       -
;  Changed:      -
;  Return:       A  = HIGH-byte of starting address of the zero-terminated version string
;                DE = LOW-word of that address
; ---------------------------------------------------------------------------------------------------------------
.EXTERN FDL_GetVersionString


;*******************************************************************************
; END OF UNTOUCHABLE DECLARATION AREA
;*******************************************************************************

$ENDIF
