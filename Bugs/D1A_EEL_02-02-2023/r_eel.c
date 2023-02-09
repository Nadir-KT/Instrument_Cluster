

/***********************************************************************************************************************
* File Name    : r_eel.c
* Version      : CodeGenerator for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2012/07/06
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "fdl.h"
#include "fdl_descriptor.h"
#include "fdl_types.h"
#include "eel.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"
#include "eel_types.h"

#include <stdlib.h>
#include <string.h>
/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint8_t Write_value[4];
uint8_t Data_id;
uint8_t Read_value[4];
 /*int8_t  g_upper_string[LCD_SIZE + 1];
 int8_t  g_downer_string[LCD_SIZE + 1];
*/
/***********************************************************************************************************************
* Function Name: R_EEL_Initialize
* Description  : This function initializes data flash.
* Arguments    : None
* Return Value : EEL_OK - 
                     Success initializing EEPROM emulation
                 EEL_NG - 
                     Fail initializing EEPROM emulation
***********************************************************************************************************************/
uint8_t R_EEL_Initialize(void)
{
    uint8_t       ret;
    eel_request_t requester;
    
    /* ---- Initialize requester ---- */
    requester.status_enu     = 0;
    requester.address_pu08   = 0;
    requester.identifier_u08 = 0;
    requester.command_enu    = 0;
    //requester.timeout_u08    = 0; 
    
    
    ret = FDL_Init(&fdl_descriptor_str);                       /* Initialize FAL */
    
    /* **** When initialization(FAL) is success **** */
    if(ret == FDL_OK)
    {
        ret = EEL_Init();                                                           /* Initialize EEL */

        /* ==== When initialize(EEL) is success ==== */
        if(ret == EEL_OK)
        {
            EEL_Open();                                                             /* Prepare EEL */
            
			/* ---- Loop until STARTUP command is success ---- */
			do
            {
                /* ---- Setting for STARTUP command ---- */
                requester.command_enu = EEL_CMD_STARTUP;
                //requester.timeout_u08 = EEL_MODE_ENFORCED;        
                EEL_Execute(&requester);                                            /* STARTUP command execution */

                /* ---- When status is EEL_ERR_POOL_INCONSISTENT ---- */
                if(requester.status_enu == EEL_ERR_POOL_INCONSISTENT)
                {
                    /* ---- Setting for FORMAT command ---- */
                    requester.command_enu = EEL_CMD_FORMAT;
                    //requester.timeout_u08 = EEL_MODE_ENFORCED;           
                    EEL_Execute(&requester);                                        /* FORMAT command execution */
                }
                else
                {
                    /* Do nothing */
                }
            }
            while((requester.status_enu == EEL_OK) && (requester.command_enu == EEL_CMD_FORMAT));

            /* ---- When STARTUP command is success ---- */
            if(requester.status_enu == EEL_OK)
            {
                R_EEL_Maintenance();                                                /* Maintenance mode */
                ret = EEL_OK;
            }
            else
            {
                ret = EEL_NG;
            }
        }
        else
        {
            ret = EEL_NG;
        }
    }
    else
    {
        ret = EEL_NG;
    }

    return ret;
}        

/***********************************************************************************************************************
* Function Name: R_EEL_Maintenence
* Description  : This function does maintenance of data flash.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_EEL_Maintenance(void)
{
    int                        counter = 0;
    __near eel_driver_status_t status;
    
    /* ==== Loop until end of maintenance ==== */
    while(counter < 4)
    {
        EEL_Handler(/*EEL_MODE_POLLING*/);                                              /* Check block status */
        EEL_GetDriverStatus(&status);                                               /* Check execute status */

        /* ---- When status is EEL_OPERATION_IDLE ---- */
//        if(status.operationStatus_enu == EEL_DRIVER_IDLE)
//        {
//            counter++;
//        }
//        else
//        {
//            counter = 0;
//        }
    }
}

/***********************************************************************************************************************
* Function Name: R_EEL_ExcecuteWrite
* Description  : This function writes data to the data flash.
* Arguments    : None
* Return Value : EEL_OK - 
                     Success writing to data flash
                 EEL_NG - 
                     Fail writing to data flash
***********************************************************************************************************************/
uint8_t R_EEL_ExecuteWrite(unsigned long Val, unsigned char Id)
{
    eel_request_t requester;
    uint8_t       ret;
    int8_t        i;
        
    /* LED0 ON */
    ret  = R_EEL_Initialize();                                                      /* Initialize EEL */
	
	/* **** When EEL initialization is success **** */
    if(ret == EEL_OK)
    {
	 for(i=0;i<4;i++)
	 {
		 Write_value[i] = Val>>(i*8);
	 }
	 Data_id = Id;
        /* ---- Setting for WRITE command ---- */
        requester.address_pu08   = &Write_value[0];
        requester.identifier_u08 = Data_id;
        requester.command_enu    = EEL_CMD_WRITE;
        //requester.timeout_u08    = EEL_MODE_ENFORCED;
        EEL_Execute(&requester);                                                    /* Write execution */
		
        /* **** When WRITE command is success **** */
        if(requester.status_enu == EEL_OK)
        {

                    ret = R_EEL_Close();                                            /* Close EEPROM emulation */
        }
        else
        {
            ret = EEL_NG;
        }
    }
    else
    {
        ret = EEL_NG;
    }
	R_EEL_Close();
    return ret;
}

uint8_t R_EEL_ExecuteRead(unsigned long* Val, unsigned char Id)
{
    eel_request_t requester;
    uint8_t       ret,i;
        
    /* LED0 ON */
    ret  = R_EEL_Initialize();                                                      /* Initialize EEL */
	
	/* **** When EEL initialization is success **** */
    if(ret == EEL_OK)
    {
	Data_id = Id;    
        /* ---- Setting for WRITE command ---- */
        requester.address_pu08   = &Read_value[0];
        requester.identifier_u08 = Data_id;
        requester.command_enu    = EEL_CMD_READ;
        //requester.timeout_u08    = EEL_MODE_ENFORCED;
        EEL_Execute(&requester);                                                    /* Write execution */
		
        /* **** When WRITE command is success **** */
        if(requester.status_enu == EEL_OK)
        {
			for(i=0;i<4;i++)
			*Val = Read_value[3-i] | (*Val<<8);

                    ret = R_EEL_Close();                                            /* Close EEPROM emulation */
        }
        else
        {
            ret = EEL_NG;
        }
    }
    else
    {
        ret = EEL_NG;
    }
//	R_EEL_Close();
    return ret;
}

/***********************************************************************************************************************
* Function Name: R_EEL_ClearDataFlash
* Description  : This function clears data flash.
* Arguments    : None
* Return Value : EEL_OK - 
                     Success clear data flash
                 EEL_NG - 
                     Fail clear data flash
***********************************************************************************************************************/
uint8_t R_EEL_ClearDataFlash(void)
{
    uint8_t       ret;
    uint8_t       read_id;
    eel_request_t requester;
    
    /* LED0 ON */
    ret  = R_EEL_Initialize();                                                      /* Initialize EEL */
    
    /* ==== When EEL initialization is success ==== */
    if(ret == EEL_OK)
    {
        /* ---- Setting for FORMAT command ---- */
        requester.command_enu = EEL_CMD_FORMAT;
        //requester.timeout_u08 = EEL_MODE_ENFORCED;        
        EEL_Execute(&requester);                                                    /* FORMAT command execution */

        /* ---- When FORMAT command is success ---- */
        if(requester.status_enu == EEL_OK)
        {
//            for(read_id = 0x01; read_id <= 0x03; read_id++)
//	        {
//                strncpy(g_downer_string + (3 * (read_id - 1)), "XX", 2);            /* Set display data ("XX") */
//	        }

            ret = R_EEL_Close();                                                    /* Close EEPROM emulation */
        }
        else
        {
            ret = EEL_NG;
        }
    }
    else
    {
        ret = EEL_NG;
    }

    /* LED0 OFF */
    return ret;
}

/***********************************************************************************************************************
* Function Name: R_EEL_Close
* Description  : This function stops EEPROM emulation.
* Arguments    : none
* Return Value : EEL_OK - 
                     Success closing EEPROM emulation
                 EEL_NG - 
                     Fail closing EEPROM emulation
***********************************************************************************************************************/
uint8_t R_EEL_Close(void)
{
    uint8_t       ret;
    eel_request_t requester;
    
    /* ---- Setting for SHUTDOWN command ---- */
    requester.command_enu = EEL_CMD_SHUTDOWN;
    //requester.timeout_u08 = EEL_MODE_ENFORCED;    
    EEL_Execute(&requester);                                                        /* SHUTDOWN command execution */

    /* ---- When SHUTDOWN command is success ---- */
    if(requester.status_enu == EEL_OK)
    {
        ret = EEL_OK;
    }
    else
    {
        ret = EEL_NG;
    }
    EEL_Close();                                                                    /* Close EEPROM emulation */
    
    return ret;
}
/* End user code. Do not edit comment generated here */
