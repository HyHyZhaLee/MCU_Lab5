/*
 * software_timer.h
 *
 *  Created on: Sep 23, 2023
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#ifdef __cplusplus
extern "C" {
#endif

#define NO_OF_TIMER	3
#define TICK 10

// Function declarations
extern int timer_flag[NO_OF_TIMER];
void setTimer(int duration, int ID);
void timerRun();
void initTimer(int delay);

#ifdef __cplusplus
}
#endif
#endif /* INC_SOFTWARE_TIMER_H_ */
