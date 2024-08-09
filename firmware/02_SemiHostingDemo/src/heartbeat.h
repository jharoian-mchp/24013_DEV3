//
// File:   heartbeat.h
// Author: c14029
//
// Created on May 20, 2024, 4:23 PM
//

#ifndef _HEARTBEAT_H    // Guard against multiple inclusion 
#define _HEARTBEAT_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif
    
enum HB_e {
    HB_ON = 0xff00,
    HB_OFF = 0x00ff
};

// Interface Functions
    
void heartbeat_init(void);
enum HB_e get_heartbeat_state(void);
void heartbeat_tasks(void);

// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _HEARTBEAT_H
