/*******************************************************************************
	Module Name:		OsCfg.h
	Generation Date:	2020-October-Friday	02:02:48
	Tool Version: 		V.0
	Description: 		Os configuration header file


	All Rights Reserved - Sarea Alhariri
*******************************************************************************/

/******************************************************************************/
/*******************AUTO GENERATED FILE PLEASE DO NOT TOUCH********************/
/******************************************************************************/

#ifndef OS_CFG_H_
#define OS_CFG_H_
 
#include "OsTypes.h"

/*******************************************************************************
	Extern number of App Tasks
*******************************************************************************/
extern const uint8_t OsCfg_MAX_NUM_OF_TASKS;
/*******************************************************************************
	Define the number of alarms
*******************************************************************************/
extern const uint8_t OsCfg_MAX_NUM_OF_ALARMS;
/*******************************************************************************
	Define the number of resources
*******************************************************************************/
extern const uint8_t OsCfg_MAX_NUM_OF_RESOURCES; 
/*******************************************************************************
	OsCfg_ALL_STACK_SIZE
*******************************************************************************/
extern const uint16_t OsCfg_ALL_STACK_SIZE;
/*******************************************************************************
	Hook routines configurations
*******************************************************************************/
extern const uint8_t OsCfg_USE_ERROR_HOOK;
extern const uint8_t OsCfg_USE_PRETASK_HOOK;
extern const uint8_t OsCfg_USE_POSTTASK_HOOK;
extern const uint8_t OsCfg_USE_STARTUP_HOOK;
extern const uint8_t OsCfg_USE_STACK_OVER_FLOW_HOOK;


extern const uint8_t OsCfg_USE_PARAMETER_ACCESS;
extern const uint8_t OsCfg_USE_GET_SERVICE_ID;
extern const uint32_t OsCfg_SYSTEM_TICK_IN_MS;
extern const uint32_t OSTICKDURATION;
/*******************************************************************************
	System task functions prototypes
*******************************************************************************/
extern void OsTask_Task_ReadDoorStatus(void); 
extern void OsTask_Task_OpenAlarm(void); 
extern void OsTask_Task_CloseAlarm(void); 
extern void OsTask_Task_Init(void); 
extern void OsTask_IdleMechanism(void); 
/*******************************************************************************
	Task Identifiers
*******************************************************************************/
enum OsCfg_TaskIDs
{
	Task_ReadDoorStatus,
	Task_OpenAlarm,
	Task_CloseAlarm,
	Task_Init
};
/*******************************************************************************
	Symbolic names for wait events for each thread
*******************************************************************************/
/*Task_ReadDoorStatusEvents*/
/*Task_OpenAlarmEvents*/
/*Task_CloseAlarmEvents*/
/*Task_InitEvents*/

/*******************************************************************************
	Task Control Blocks Table
*******************************************************************************/
extern tcb_t OsCfg_TCBs[4+1/*for Idle mechanism */]; 

/*******************************************************************************
	Alarm control blocks table
*******************************************************************************/
extern acb_t OsCfg_Alarms[1]; /*Not used*/

/*******************************************************************************
	Stack size for each thread
*******************************************************************************/
extern const uint32_t OsCfg_StackSize[4];

/*******************************************************************************
	Stack Buffer For All Threads
*******************************************************************************/
extern uint32_t OsCfg_Stack[200+16/* 16 for Idle mechanism */]; 

/*******************************************************************************
	Rosource task authorization
*******************************************************************************/
extern const uint8_t OsCfg_ResourceTaskAuthorized[1][1]; /*Not used*/

/*******************************************************************************
	Ceiling priority for sysytem resources
*******************************************************************************/
extern const uint8_t OsCfg_ResourceCeilPri[1];/*Not used.*/
/*******************************************************************************
	Error code task buffer
*******************************************************************************/
extern StatusType SVCCnxt_ErrCodes[4/*OsCfg_MAX_NUM_OF_TASKS*/];
/*******************************************************************************
	SVC resource context
*******************************************************************************/
extern ResourceType SVCCnxt_ResMgrCnxt[1];/*Not used*/
/*******************************************************************************
	Resource control block table
*******************************************************************************/
extern RCB_t RCB[1];/*Not used*/
#endif
