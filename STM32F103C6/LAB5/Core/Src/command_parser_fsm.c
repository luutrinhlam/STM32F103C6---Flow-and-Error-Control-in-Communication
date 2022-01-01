/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 3, 2021
 *      Author: Admin
 */
#include "main.h"
#include "timer.h"
#include "command_parser_fsm.h"
#include "uart_communiation_fsm.h"

enum command_parser_fsm_state{WAITING, PARSING};
enum command_parser_fsm_state command_state = WAITING;

uint8_t temp = 0;

int command_flag;
char command_data [MAX_BUFFER_SIZE+1];
int command_data_size = 0;

void command_parser_fsm(void){
	switch(command_state){
	case WAITING:
		if(temp == '!') command_state = PARSING;
		break;
	case PARSING:
		if(temp == '#') {
			command_data[command_data_size] = '\0';
			command_flag = 1;
			command_state = WAITING;
		}else if (temp == '!') command_data_size = 0;
		else{
			command_data[command_data_size++] = temp;

		}
		break;
	}
}


