//
// File:   mcp9804.h
// Author: c14029
//
// Created on May 28, 2024, 3:22 PM
//

#ifndef _MCP9804_H    // Guard against multiple inclusion 
#define _MCP9804_H

// Provide C++ Compatibility 
#ifdef __cplusplus
extern "C" {
#endif

// Interface Functions
    
void mcp9804_init(void);
void mcp9804_read_temp(void);

// Provide C++ Compatibility
#ifdef __cplusplus
}
#endif

#endif // _MCP9804_H
