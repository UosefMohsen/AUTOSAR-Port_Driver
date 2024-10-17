#include "PortDriver.h"
#include "tm4c123gh6pm_registers.h"

static uint8 Init_Flag = 0;
/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ){
    #if (PORT_DEV_ERROR_Enable == 1)
        if (ConfigPtr == NULL_PTR)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_Init_SID, PORT_E_PARAM_CONFIG);
        }
        
    #endif
    uint8 i;
    for ( i = 0; i < Number_Of_Pins_Configured ; i++)
    {
    volatile uint32 *Port_Ptr = NULL_PTR;

    switch(ConfigPtr->Port_Number)
    {
        case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                 break;
        case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                 break;
        case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                 break;
        case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                 break;
        case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                 break;
        case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                 break;
    }

                                                        /* Lock & Commit Section */

if( ((ConfigPtr->Port_Number == 3) && (ConfigPtr->Pin_Number == 7)) || ((ConfigPtr->Port_Number == 5) && (ConfigPtr->Pin_Number == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->Pin_Number);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (ConfigPtr->Port_Number == 2) && (ConfigPtr->Pin_Number <= 3) ) /* PC0 to PC3 */
    {
       while(1);                                                                                //Stuck in a superloop for trying to configure JTAG
    }


                                                        /* Pin Direction Section */

if(ConfigPtr->Pin_Direction == OUTPUT)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->Pin_Number);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
    }
 else if(ConfigPtr->Pin_Direction == INPUT)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->Pin_Number);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
    }

                                                     /* Resistor Direction Section */

if(ConfigPtr->Resistor_Direction == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Pin_Number);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(ConfigPtr->Resistor_Direction == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Pin_Number);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Pin_Number);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Pin_Number);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }

                                                              /* Pin Level */

if(ConfigPtr->Pin_Level == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->Pin_Number);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
    else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->Pin_Number);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }

                                                     /* Analog or digital selection */
if(ConfigPtr->Pin_Analog_Selection == 1){
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Pin_Number);
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Pin_Number);
}
    else{
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Pin_Number);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Pin_Number);
    }

                                                        /* Pin Mode Selection */
if (ConfigPtr->Pin_Mode_Number == 0){
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Pin_Number);
    }
    else{
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Pin_Number);
        switch (ConfigPtr->Pin_Number)
        {
        case 0:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 0);
            break;

        case 1:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 4);
            break;

        case 2:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 8);
            break;

        case 3:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 12);
            break;

        case 4:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 16);
            break;

        case 5:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 20);
            break;

        case 6:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 24);
            break;

        case 7:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr->Pin_Mode_Number << 28);
            break;
          }
       }
    ConfigPtr++;
    }
    Init_Flag = 1;
};


/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number. 
                   Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
    #if (PORT_DEV_ERROR_Enable == 1)
        if (Pin > 42)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_SetPinDirection_SID, PORT_E_PARAM_PIN);
        }
    #endif

    volatile uint32 *Port_Ptr = NULL_PTR;
    uint8 port_num = Pin / 8;
    switch (port_num)
    {
        case  0:
             Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
		         break;
     	case  1:
             Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
		         break;
	    case  2:
              Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
		         break;
	    case  3:
              Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
		         break;
        case  4: 
              Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
		         break;
        case  5: 
              Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
		         break;
    }
    if(Direction == 1)
    {
	    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Pin);
    }
     else if(Direction == 0)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Pin);
    }
};

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module
************************************************************************************/
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo ){
    #if (PORT_DEV_ERROR_Enable == 1)
        if (Init_Flag != 1)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_RefreshPortDirection_SID, PORT_E_UNINIT);
        }
    #endif
        versioninfo->vendorID = Vendor_ID;
        versioninfo->moduleID = Module_ID;
        versioninfo->sw_major_version = Port_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = Port_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = Port_SW_PATCH_VERSION;
};

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number. 
                   Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode
************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
    #if (PORT_DEV_ERROR_Enable == 1)

        /* Checking if the pin value is correct */
        if (Pin > 42)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_SetPinDirection_SID, PORT_E_PARAM_PIN);
        }
        
        /* Checking if the Mode value is correct */
        else if (Mode >15)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_SetPinMode_SID, PORT_E_PARAM_INVALID_MODE);
        }

        /* checking if mode is changeable during runtime or not   */
        else if (Pin_Direction_Changable_RunTime == STD_OFF)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_SetPinMode_SID, PORT_E_MODE_UNCHANGEABLE);
        }
    #endif

    volatile uint32 *Port_Ptr = NULL_PTR;
    uint8 port_num = Pin / 8;
    uint8 pin_num = Pin - (8 * port_num);
    switch (port_num)
    {
        case  0:
             Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
		         break;
     	case  1:
             Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
		         break;
	    case  2:
              Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
		         break;
	    case  3:
              Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
		         break;
        case  4: 
              Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
		         break;
        case  5: 
              Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
		         break;
    }

    if (Mode == 0){
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
    }
    else{
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
        switch (pin_num)
        {
        case 0:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 0);
            break;

        case 1:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 4);
            break;

        case 2:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 8);
            break;

        case 3:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 12);
            break;

        case 4:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 16);
            break;

        case 5:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 20);
            break;

        case 6:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 24);
            break;

        case 7:
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << 28);
            break;
        }
    }
};

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
************************************************************************************/
void Port_RefreshPortDirection( void ){
    #if (PORT_DEV_ERROR_Enable == 1)
        if (Init_Flag != 1)
        {
            Det_ReportError(Module_ID, Module_Instance, Port_RefreshPortDirection_SID, PORT_E_UNINIT);
        }
    #endif
    uint8 i;
    for (i = 0 ; i < Number_Of_Pins_Configured ; i++)
    {
        volatile uint32 *Port_Ptr = NULL_PTR;
    switch (Port_Configuration_Test->Port_Number)
    {
        case  0:
             Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                 break;
        case  1:
             Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                 break;
        case  2:
              Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                 break;
        case  3:
              Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                 break;
        case  4:
              Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                 break;
        case  5:
              Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                 break;
    }
    if(Port_Configuration_Test->Pin_Direction == OUTPUT)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration_Test->Pin_Number);
    }
     else if(Port_Configuration_Test->Pin_Direction == INPUT)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration_Test->Pin_Number);
    }
    }

};
