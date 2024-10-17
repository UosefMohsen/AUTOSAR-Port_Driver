#ifndef _PORTDRIVER_H_
#define _PORTDRIVER_H_

/* Standard AUTOSAR types */
#include    "Std_Types.h"
#include    "Common_Macros.h"
#include    "Port_Cfg.h"

#if (PORT_DEV_ERROR_Enable == 1)
#include    "Det.h"
#endif

/* Vendor's ID */
#define Vendor_ID   (3000U)

/* Module ID */
#define Module_ID   (124U)

/* Module Instance */
#define Module_Instance (0U)

/* Module Version 1.0.0 */
#define Port_SW_MAJOR_VERSION           (1U)
#define Port_SW_MINOR_VERSION           (0U)
#define Port_SW_PATCH_VERSION           (0U)

/* Autosar Version */
#define Port_AR_RELEASE_MAJOR_VERSION   (3U)
#define Port_AR_RELEASE_MINOR_VERSION   (2U)
#define Port_AR_RELEASE_PATCH_VERSION   (0U)

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;



/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init Function */
#define Port_Init_SID   0x00

/* Service ID for Port_SetPinDirection Function */
#define Port_SetPinDirection_SID    0x01

/* Service ID for Port_RefreshPortDirection Function */
#define Port_RefreshPortDirection_SID   0x02

/* Service ID for Port_GetVersionInfo */
#define Port_GetVersionInfo_SID 0x03

/* Service ID for Port_SetPinMode */
#define Port_SetPinMode_SID 0x04

/*******************************************************************************
 *                            DET Error Codes                                   *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                         0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE            0x0B

/* API Port_Init service */
#define PORT_E_PARAM_CONFIG                      0x0C

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE                0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                 0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                            0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                     0x10


/*******************************************************************************
 *                            Types Definitions                                 *
 *******************************************************************************/

/* Data type for the symbolic name of a port pin */
typedef uint8   Port_PinType;

/* Possible directions of a port pin */
typedef uint8   Port_PinDirectionType;

/* Different port pin modes */
typedef uint8   Port_PinModeType;

/* data structure containing the initialization data for this module */
typedef struct {
    uint8 Port_Number;                              //DONE
    uint8 Pin_Number;                               //DONE
    Port_PinModeType Pin_Mode_Number;               //DONE
    Port_PinDirectionType Pin_Direction;            //DONE
    Port_InternalResistor Resistor_Direction;       //DONE
    uint8 Pin_Level;                                //DONE
    uint8 Pin_Analog_Selection;                     //DONE
}Port_ConfigType;

extern Port_ConfigType Port_Configuration_Test[Number_Of_Pins_Configured];

/*******************************************************************************
 *                        Functions Prototypes                                  *
 *******************************************************************************/

/* Initializes the Port Driver module takes Pointer to configuration set */

void Port_Init( const Port_ConfigType* ConfigPtr );

/* Sets the Pin Direction */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );

/* Refreshes Port Direction */
void Port_RefreshPortDirection( void );

/* Returns the version information of this module */
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );

/* Sets the Port Pin Mode */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );

#endif



