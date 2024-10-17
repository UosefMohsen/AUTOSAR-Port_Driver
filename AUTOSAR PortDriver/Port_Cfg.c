#ifndef PORT_CFG_C
#define PORT_CFG_C

#include    "PortDriver.h"

Port_ConfigType Port_Configuration_Test[Number_Of_Pins_Configured] = {
/*                          Port A                    */
{0, 0, 0, INPUT, OFF, OFF, STD_OFF },
{0, 1, 0, INPUT, OFF, OFF, STD_OFF },
{0, 2, 0, INPUT, OFF, OFF, STD_OFF },
{0, 3, 0, INPUT, OFF, OFF, STD_OFF },
{0, 4, 0, INPUT, OFF, OFF, STD_OFF },
{0, 5, 0, INPUT, OFF, OFF, STD_OFF },
{0, 6, 0, INPUT, OFF, OFF, STD_OFF },
{0, 7, 0, INPUT, OFF, OFF, STD_OFF },

/*                          Port B                     */
{1, 0, 0, INPUT, OFF, OFF, STD_OFF },
{1, 1, 0, INPUT, OFF, OFF, STD_OFF },
{1, 2, 0, INPUT, OFF, OFF, STD_OFF },
{1, 3, 0, INPUT, OFF, OFF, STD_OFF },
{1, 4, 0, INPUT, OFF, OFF, STD_OFF },
{1, 5, 0, INPUT, OFF, OFF, STD_OFF },
{1, 6, 0, INPUT, OFF, OFF, STD_OFF },
{1, 7, 0, INPUT, OFF, OFF, STD_OFF },
/*                          Port C                     */
{2, 4, 0, INPUT, OFF, OFF, STD_OFF },
{2, 5, 0, INPUT, OFF, OFF, STD_OFF },
{2, 6, 0, INPUT, OFF, OFF, STD_OFF },
{2, 7, 0, INPUT, OFF, OFF, STD_OFF },

/*                          Port D                     */
{3, 0, 0, INPUT, OFF, OFF, STD_OFF },
{3, 1, 0, INPUT, OFF, OFF, STD_OFF },
{3, 2, 0, INPUT, OFF, OFF, STD_OFF },
{3, 3, 0, INPUT, OFF, OFF, STD_OFF },
{3, 4, 0, INPUT, OFF, OFF, STD_OFF },
{3, 5, 0, INPUT, OFF, OFF, STD_OFF },
{3, 6, 0, INPUT, OFF, OFF, STD_OFF },
{3, 7, 0, INPUT, OFF, OFF, STD_OFF },

/*                          Port E                     */
{4, 0, 0, INPUT, OFF, OFF, STD_OFF },
{4, 1, 0, INPUT, OFF, OFF, STD_OFF },
{4, 2, 0, INPUT, OFF, OFF, STD_OFF },
{4, 3, 0, INPUT, OFF, OFF, STD_OFF },
{4, 4, 0, INPUT, OFF, OFF, STD_OFF },
{4, 5, 0, INPUT, OFF, OFF, STD_OFF },


/*                          Port F                     */
{5, 0, 0, INPUT, OFF, OFF, STD_OFF },
{5, 1, 0, OUTPUT, OFF, STD_OFF, STD_OFF },
{5, 2, 0, INPUT, OFF, OFF, STD_OFF },
{5, 3, 0, INPUT, OFF, OFF, STD_OFF },
{5, 4, 0, INPUT, PULL_UP, STD_OFF, STD_OFF },
};

#endif
