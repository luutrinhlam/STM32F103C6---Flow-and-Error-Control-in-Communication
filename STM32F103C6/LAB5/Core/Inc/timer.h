/*
 * timer.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_


void setTimerResend(int duration);
void timer_run();

extern int timerResend_flag;

#endif /* INC_TIMER_H_ */
