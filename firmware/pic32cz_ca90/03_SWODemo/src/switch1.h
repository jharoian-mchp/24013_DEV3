//
// File:   switch1.h
// Author: c14029
//
// Created on May 25, 2024, 1:02 PM
//

#ifndef _SWITCH1_H    // Guard against multiple inclusion 
#define _SWITCH1_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

enum SW1_e {
    SW1_ON = 0xdd00,
    SW1_OFF = 0x00dd
};
    
// Interface Functions
    
void switch1_init(void);
void switch1_tasks(void);

// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _SWITCH1_H
