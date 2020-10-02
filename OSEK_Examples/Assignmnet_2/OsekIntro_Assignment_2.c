/**
 * @file OsekIntro_Assignment_2.c
 * @author Shreef Mohamed
 * @brief  LED state machine using 3 Tasks only
 * @version 0.1
 * @date 2020-10-2
 *
 * @copyright Shreef Mohamed - All rights reserved
 *
 */
#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"
#include "hw_memmap.h"
#include "os.h"
#include "sysctl.h"
#include "tm4c123gh6pm.h"


#define NUMBER_OF_DELAY_CYCLES 0x003FFFFFU

DeclareTask(Task_Init);
DeclareTask(Task_ReadDoorStatus);
DeclareTask(Task_OpenAlarm);
DeclareTask(Task_CloseAlarm);


void SystemInit(void) {}
int main(void) {
  StartOS();
  return 0;
}

TASK(Task_ReadDoorStatus) {

  uint32_t Left_Door = 0U;
  uint32_t Right_Door = 0U;

  while (1) {

    Right_Door = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    Left_Door = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((Right_Door | Left_Door) == 0x11) 
		{
			// Doors are closed
			// lets Close Alarm
      ActivateTask(Task_CloseAlarm);
    } 
		else 
		{
			// At least one door is open
			// Lets Open Alarm
      ActivateTask(Task_OpenAlarm);
    }
  }
}

TASK(Task_OpenAlarm) {

  while (1) 
	{
		// Open Alarm --> Turn ON RED_LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1);
		// lets check door status
		TerminateTask();
  }
}

TASK(Task_CloseAlarm) {
	
	while (1) 
	{
		// Close Alarm --> Turn off RED_LED && Turn on GREEN_LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_3);
		// lets check door status
		TerminateTask();
  }
}


TASK(Task_Init) {

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIO_PORTF_LOCK_R = 0x4c4f434b;
  GPIO_PORTF_CR_R = 0x01f;
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);

  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA,
                   GPIO_PIN_TYPE_STD_WPU);

  TerminateTask();
}

