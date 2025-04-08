//
// File:   messages.h
// Author: c14029
//
// Created on May 21, 2024, 2:25 PM
//

#ifndef _MESSAGES_H    // Guard against multiple inclusion 
#define _MESSAGES_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
    
void messages_init(void);
void messages_system_ok(void);
void messages_SW1_down(void);
void messages_SW1_up(void);
void messages_SW2_down(void);
void messages_SW2_up(void);
void messages_temp(float temp);
    
// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _MESSAGES_H
