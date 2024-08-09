
//
// File:   debug_logging.c
// Author: c14029
//
// Created on June 2, 2024, 9:10 PM
//

// Semihosting documentation:
// Section 9.4.1 of the MPLAB X IDE User's Guide
// https://onlinedocs.microchip.com/oxy/GUID-D79ACEBE-41BD-43EF-8E1B-9462847AE13E-en-US-10/GUID-795DF1E5-F11A-4446-B56D-436192F8826C.html

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "debug_logging.h"

// The following extern function call exists in 
extern void initialise_monitor_handles(void);

#define BUFFER_PRINTF_SIZE 1024
char buffer_printf[BUFFER_PRINTF_SIZE];

void debug_logging_init() {
    initialise_monitor_handles();

    // Optional memory buffer for printf for enhanced performance
    setvbuf(stdout, buffer_printf, _IOFBF, BUFFER_PRINTF_SIZE);   
}

void debug_logging_heartbeat_tasks(void) {
    printf("[D: heartbeat_tasks()]\n\r");
}

void debug_logging_switch1_tasks(void) {
    printf("[D: switch1_tasks()]\n\r");
}

void debug_logging_switch2_tasks(void) {
    printf("[D: switch2_tasks()]\n\r");
}
