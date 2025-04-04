
//
// File:   messages.c
// Author: c14029
//
// Created on May 21, 2024, 2:25 PM
//

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "messages.h"
#include "peripheral/sercom/usart/plib_sercom7_usart.h"

struct MSDATA_s {
    uint32_t message_count;
    char temp_message_buffer[80];
    char count_buffer[16];
};

static struct MSDATA_s messageData;


void timestamp_message(void *buffer);

#define MESSAGES_SYS_OK         "[M:OK]\n\r"
#define MESSAGES_SW1_DOWN       "[M:SW1_DOWN]\n\r"
#define MESSAGES_SW1_UP         "[M:SW1_UP]\n\r"
#define MESSAGES_SW2_DOWN       "[M:SW2_DOWN]\n\r"
#define MESSAGES_SW2_UP         "[M:SW2_UP]\n\r"
#define MESSAGES_TEMP           "[M:TEMP:"

void messages_init() {
    messageData.message_count = 0;
}

void messages_system_ok() {
    timestamp_message(MESSAGES_SYS_OK);
}

void messages_SW1_down() {
    timestamp_message(MESSAGES_SW1_DOWN);
}

void messages_SW1_up() {
    timestamp_message(MESSAGES_SW1_UP);
}

void messages_SW2_down() {
    timestamp_message(MESSAGES_SW2_DOWN);
}

void messages_SW2_up() {
    timestamp_message(MESSAGES_SW2_UP);
}

void messages_temp(float temp) {
    sprintf(messageData.temp_message_buffer, "%s %f]\n\r", MESSAGES_TEMP, temp);
    timestamp_message(messageData.temp_message_buffer);
}

void timestamp_message(void *buffer) {
    messageData.message_count++;

    sprintf(messageData.count_buffer, "%ld: ", messageData.message_count);

    while(SERCOM7_USART_WriteIsBusy());

    assert(SERCOM7_USART_Write( messageData.count_buffer, \
                                strlen(messageData.count_buffer)));
    
    while(SERCOM7_USART_WriteIsBusy());

    assert(SERCOM7_USART_Write(buffer, strlen(buffer)));
}