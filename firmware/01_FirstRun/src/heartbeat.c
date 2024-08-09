//
// File:   heartbeat.c
// Author: c14029
//
// Created on May 20, 2024, 4:15 PM
//

#include "heartbeat.h"
#include "messages.h"
#include "peripheral/port/plib_port.h"
#include "peripheral/tc/plib_tc0.h"


struct HBDATA_s {
    enum HB_e heartbeat_last_state;
    volatile enum HB_e heartbeat_interrupt_state;
};

static struct HBDATA_s hbData;

void heartbeat(TC_TIMER_STATUS status, uintptr_t context);

void heartbeat_init() {
    hbData.heartbeat_last_state = HB_OFF;
    hbData.heartbeat_interrupt_state = HB_OFF;

    TC0_TimerCallbackRegister( heartbeat, (uintptr_t) NULL );
    TC0_TimerStart();
}

void heartbeat(TC_TIMER_STATUS status, uintptr_t context) {
    if(hbData.heartbeat_interrupt_state == HB_OFF) {
        hbData.heartbeat_interrupt_state = HB_ON;
    } else {
        hbData.heartbeat_interrupt_state = HB_OFF;
    }
}

void heartbeat_tasks() {
    enum HB_e hb_temp;

    hb_temp = hbData.heartbeat_interrupt_state;
    if(hb_temp != hbData.heartbeat_last_state) {
        if(hb_temp == HB_OFF) {
            LED2_Clear();
        }
        if(hb_temp == HB_ON) {
            LED2_Set();
            messages_system_ok();
        }
        hbData.heartbeat_last_state = hb_temp;
    }
}

