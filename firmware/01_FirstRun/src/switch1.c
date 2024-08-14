//
// File:   switch1.c
// Author: c14029
//
// Created on May 25, 2024, 1:02 PM
//

#include "switch1.h"
#include "messages.h"
#include "peripheral/port/plib_port.h"
#include "peripheral/eic/plib_eic.h"
#include "mcp9804.h"


struct SW1DATA_s {
    enum SW1_e switch1_last_state;
    volatile enum SW1_e switch1_interrupt_state;
    uint32_t value;
};

static struct SW1DATA_s sw1Data;

void switch1(uintptr_t context);

void switch1_init() {
    sw1Data.switch1_last_state = SW1_OFF;
    sw1Data.switch1_interrupt_state = SW1_OFF;

    EIC_CallbackRegister(EIC_PIN_0, switch1, (uintptr_t) NULL);
    EIC_InterruptEnable(EIC_PIN_0);
}

void switch1(uintptr_t context) {
    if(sw1Data.switch1_interrupt_state == SW1_OFF) {
        sw1Data.switch1_interrupt_state = SW1_ON;
    } else {
        if(sw1Data.switch1_interrupt_state == SW1_ON) {
            sw1Data.switch1_interrupt_state = SW1_OFF;
        }
    }
}

void switch1_tasks() {
    enum SW1_e sw1_temp;
    uint32_t* addr = (uint32_t*)0x30000000;
    
    sw1_temp = sw1Data.switch1_interrupt_state;
    if(sw1_temp != sw1Data.switch1_last_state) {
        if(sw1_temp == SW1_ON) {
            messages_SW1_down();
            sw1Data.value = *addr;
            mcp9804_read_temp();
        }
        if(sw1_temp == SW1_OFF) {
            messages_SW1_up();
        }
        sw1Data.switch1_last_state = sw1_temp;
    }
}
