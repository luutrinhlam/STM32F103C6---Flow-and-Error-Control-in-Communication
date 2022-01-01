/*
 * uart_communiation_fsm.c
 *
 *  Created on: Dec 3, 2021
 *      Author: Admin
 */
#include "main.h"
#include "timer.h"
#include "command_parser_fsm.h"
#include "uart_communiation_fsm.h"
#include <string.h>
#include <stdio.h>

#define RESENDING_TIME 3000

enum uart_communiation_fsm_state {
	WAITING, CHECKING_COMMAND, RESEND
};
enum uart_communiation_fsm_state communiation_state = WAITING;

uint32_t ADC_value = 0;
int resend_flag = 0;
char str[10];
char *request = "RST";
char *ok = "OK";


void uart_communiation_fsm(void) {
	switch (communiation_state) {
	case WAITING:
		if (command_flag)
			communiation_state = CHECKING_COMMAND;
		break;
	case CHECKING_COMMAND:
		if (strcmp(command_data, request) == 0) {
			char str[10];
			ADC_value = HAL_ADC_GetValue(&hadc1);
			ADC_value = ADC_value*5/4095;
			HAL_UART_Transmit(&huart2, (void*) str,
					sprintf(str, "%ld\n", ADC_value), 1000);
			resend_flag = 1;
			setTimerResend(RESENDING_TIME);
		}
		if (strcmp(command_data, ok) == 0) {
			resend_flag = 0;
		}
		if(resend_flag == 1){
			communiation_state = RESEND;
		}else {
			communiation_state = WAITING;
		}
		command_data_size = 0;
		command_flag = 0;
		break;
	case RESEND:

		if(command_flag == 1){
			communiation_state = CHECKING_COMMAND;

		}
		if(timerResend_flag == 1){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			char str[10];
			HAL_UART_Transmit(&huart2, (void*) str,
					sprintf(str, "%ld\n", ADC_value), 1000);
			setTimerResend(RESENDING_TIME);
		}
		break;
	}
}

