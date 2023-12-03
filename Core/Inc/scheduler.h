/*
 * scheduler.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#ifdef __cplusplus
extern "C" {
#endif


#define SCH_MAX_TASKS 			10
#define	NO_TASK_ID				0




#include "main.h"
#include "stdint.h"

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_ID);


#ifdef __cplusplus
}
#endif
#endif /* APP_SCHEDULER_H_ */
