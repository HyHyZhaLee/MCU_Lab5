/*
 * scheduler.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include "main.h"
#include <stdint.h>

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

class Scheduler{
private:
	class sTask{
		friend class Scheduler;
		void (*pTask)(void); 	// Function pointer to do task
	    uint32_t delay; 		// Delay
	    uint32_t period; 		// Period
	    uint8_t runMe; 			// Flag to do task
	    sTask* next; 			// Pointer for linked list
	    sTask(void (*pTaskFunction)(void), uint32_t initDelay, uint32_t initPeriod, sTask* initNext = nullptr)
	        : pTask(pTaskFunction), delay(initDelay), period(initPeriod), runMe(0), next(initNext) {
	    }
	};
	sTask* SCH_tasks_G; 		// Pointer to head task
	uint8_t taskCounter; 		// To count task
	uint8_t Error_code_G; 		// For error checking
	void Timer_init(void){}; 		// Init timer
	void Watchdog_init(void){}; 	// Init watchdog

    uint8_t SCH_Delete_Task(sTask* delTask){ //For deleting task, returning number of task left
    	sTask*phead = this->SCH_tasks_G;
    	if(phead == NULL) return -1;
    	// Case head = delNode
    	if(phead == delTask) {
    		SCH_tasks_G = SCH_tasks_G->next;
    		delete delTask;
    		taskCounter--;
    		return taskCounter;
    	}
    	// Traverse to find delNode
    	while(phead->next!=NULL){
    		if(phead->next == delTask){
    			phead->next = phead->next->next;
    			delete delTask;
    			taskCounter--;
    			return taskCounter;
    		}
    		phead = phead->next;
    	}
    	// If find nothing, return -1
    	return -1;
    };

public:
    Scheduler(){
    	this->SCH_tasks_G = NULL;
    	taskCounter = 0;
    	Error_code_G = 0;
    	Timer_init();
    	Watchdog_init();
    }

    ~Scheduler(){
    	while(this->SCH_tasks_G != NULL){
    		sTask* delTask = this->SCH_tasks_G;
    		this->SCH_tasks_G = this->SCH_tasks_G->next;
    		delete delTask;
    	}
    }

    void SCH_Update(void){
    	if(SCH_tasks_G == NULL) return; //There is no task
		SCH_tasks_G->delay--;
		if(SCH_tasks_G->delay <=0) SCH_tasks_G->runMe = 1;
    };
    uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD){
    	sTask* newTask = new sTask(p_function, DELAY, PERIOD);
    	if(SCH_tasks_G == NULL){
    		SCH_tasks_G = newTask;
    		this->taskCounter++;
    		return taskCounter;
    	}
    	sTask* phead = this->SCH_tasks_G;
    	if(newTask->delay < phead->delay){
    		phead->delay -= newTask->delay;
    		newTask->next = phead;
    		SCH_tasks_G = newTask;
    		taskCounter++;
    		return taskCounter;
    	}
    	newTask->delay -= phead->delay;
    	while(phead->next!=NULL){
    		if(newTask->delay < phead->next->delay) break;
    		newTask->delay -= phead->next->delay;
    		phead = phead->next;
    	}
    	newTask->next = phead->next;
    	phead->next = newTask;
    	if(newTask->next!=NULL) newTask->next->delay -= newTask->delay;
    	taskCounter++;
    	return taskCounter;
    };

    void SCH_Dispatch_Tasks(void){
    	if(SCH_tasks_G == NULL) return;

    	if(SCH_tasks_G->runMe>0) {
    		(*SCH_tasks_G->pTask)(); 	// Run the task
    		SCH_tasks_G->runMe = 0; 	// Reduce the flag

    		void(*tempPTask)() = SCH_tasks_G->pTask;
    		uint32_t tempDELAY = SCH_tasks_G->period;
    		uint32_t tempPERIOD = SCH_tasks_G->period;
    		SCH_Delete_Task(SCH_tasks_G);

    		if(tempPERIOD >0) SCH_Add_Task(tempPTask, tempDELAY, tempPERIOD);
    	}
    	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    };
    uint8_t getNumberOfTask(){
    	return taskCounter;
    }

};
#endif /* INC_SCHEDULER_H_ */
