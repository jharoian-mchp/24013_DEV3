//
// File:   debug_logging.h
// Author: c14029
//
// Created on June 2, 2024, 9:10 PM
//

#ifndef _DEBUG_LOGGING_H    // Guard against multiple inclusion 
#define _DEBUG_LOGGING_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

void debug_logging_init(void);
void debug_logging_heartbeat_tasks(void);
void debug_logging_switch1_tasks(void);
void debug_logging_switch2_tasks(void);
    
// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _DEBUG_LOGGING_H
