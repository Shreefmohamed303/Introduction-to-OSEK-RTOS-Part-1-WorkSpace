/**
 * @file OsekIntro_Assignment_1.c
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
DeclareTask(Task_BasicTask);
DeclareTask(Task_RGB);
DeclareTask(Task_BGR);


static void SetLedCurrentState(void);
static void RGB_Blinking(void);
static void BGR_Blinking(void);
void SystemInit(void) {}
int main(void) {
  StartOS();
  return 0;
}

TASK(Task_BasicState) {

  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {

    SetLedCurrentState();
    SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) 
		{
      ActivateTask(Task_RGB);
    } 
		else if ((l_PF0 | l_PF4) == 0x01) 
		{
      ActivateTask(Task_BGR);
    }
  }
}

TASK(Task_RGB) {
  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {

    SetLedCurrentState();
    //SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) 
		{
      /* Do Nothing */
    } 
		else if ((l_PF0 | l_PF4) == 0x01) 
		{
      ChainTask(Task_BGR);
    } 
		else 
		{
      TerminateTask();
    }
  }
}

TASK(Task_BGR) {
  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {
    SetLedCurrentState();
    //SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) 
		{
      ChainTask(Task_RGB);
    } 
		else if ((l_PF0 | l_PF4) == 0x01) 
		{
      /* Do Nothing */
    } 
		else 
		{
      TerminateTask();
    }
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

static void SetLedCurrentState(void) {
  TaskType l_CurrentTask = (TaskType)0;
  GetTaskID(&l_CurrentTask);

  switch (l_CurrentTask) {
  case Task_BasicState:
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    break;
  case Task_RGB:
		RGB_Blinking();
    break;
  case Task_BGR:
		BGR_Blinking();
    break;
  default:
    break;
  }
}

static void RGB_Blinking(void)
{
	//Blink Red LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
	//Blink Green LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
							 GPIO_PIN_3);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
	//Blink Blue LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
							 GPIO_PIN_2);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
}

static void BGR_Blinking(void)
{
//Blink Blue LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
							 GPIO_PIN_2);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
	//Blink Green LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
							 GPIO_PIN_3);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
	//Blink Red LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1);
	// Delay
	SysCtlDelay(NUMBER_OF_DELAY_CYCLES);
}
