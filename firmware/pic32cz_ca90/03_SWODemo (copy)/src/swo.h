//
// File:   debug_logging.h
// Author: c14029
//
// Created on June 5, 2024, 9:44 PM
//

#ifndef _SWO_H    // Guard against multiple inclusion 
#define _SWO_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

void swo_init(void);
void ITM_SWO_PrintString(const char *s);
    
// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _SWO_H
