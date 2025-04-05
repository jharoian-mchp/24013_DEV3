//
// File:   switch2.h
// Author: c14029
//
// Created on May 23, 2024, 10:03 AM
//

#ifndef _SWITCH2_H    // Guard against multiple inclusion 
#define _SWITCH2_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

enum SW2_e {
    SW2_ON = 0xee00,
    SW2_OFF = 0x00ee
};
    
// Interface Functions
    
void switch2_init(void);
void switch2_tasks(void);

// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _SWITCH2_H
