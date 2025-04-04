
//
// File:   debug_logging.c
// Author: c14029
//
// Created on June 2, 2024, 9:10 PM
//

// SWO documentation:
// Section 5.4.5 of the MPLAB ICD 5 In-Circuit Debugger User's Guide
// https://onlinedocs.microchip.com/oxy/GUID-1FB866E7-F8EE-4F6C-92ED-0F60E926A717-en-US-2/GUID-46892059-4305-4FCA-BB07-EE0AED798EE5.html

#include "debug_logging.h"
#include "swo.h"

void debug_logging_init() {
}

void debug_logging_heartbeat_tasks(void) {
    ITM_SWO_PrintString("[D: heartbeat_tasks()]\n");
}

void debug_logging_switch1_tasks(void) {
    ITM_SWO_PrintString("[D: switch1_tasks()]\n");
}

void debug_logging_switch2_tasks(void) {
    ITM_SWO_PrintString("[D: switch2_tasks()]\n");
}
