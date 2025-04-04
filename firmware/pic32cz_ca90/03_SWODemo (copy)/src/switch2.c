//
// File:   switch2.c
// Author: c14029
//
// Created on May 23, 2024, 10:03 AM
//

#include "switch2.h"
#include "messages.h"
#include "peripheral/port/plib_port.h"
#include "peripheral/eic/plib_eic.h"
#include "debug_logging.h"


struct SW2DATA_s {
    enum SW2_e switch2_last_state;
    volatile enum SW2_e switch2_interrupt_state;
};

static struct SW2DATA_s sw2Data;

void switch2(uintptr_t context);

void switch2_init() {
    sw2Data.switch2_last_state = SW2_OFF;
    sw2Data.switch2_interrupt_state = SW2_OFF;

    EIC_CallbackRegister(EIC_PIN_1, switch2, (uintptr_t) NULL);
    EIC_InterruptEnable(EIC_PIN_1);
}

void switch2(uintptr_t context) {
    if(sw2Data.switch2_interrupt_state == SW2_OFF) {
        sw2Data.switch2_interrupt_state = SW2_ON;
    } else {
        if(sw2Data.switch2_interrupt_state == SW2_ON) {
            sw2Data.switch2_interrupt_state = SW2_OFF;
        }
    }
}

void switch2_tasks() {
    enum SW2_e sw2_temp;

    debug_logging_switch2_tasks();
    
    sw2_temp = sw2Data.switch2_interrupt_state;
    if(sw2_temp != sw2Data.switch2_last_state) {
        if(sw2_temp == SW2_ON) {
            LED1_Clear();
            messages_SW2_down();
        }
        if(sw2_temp == SW2_OFF) {
            LED1_Set();
            messages_SW2_up();
        }
        sw2Data.switch2_last_state = sw2_temp;
    }
}
