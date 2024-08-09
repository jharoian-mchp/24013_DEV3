/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "heartbeat.h"
#include "switch1.h"
#include "switch2.h"
#include "messages.h"
#include "mcp9804.h"
#include "debug_logging.h"

int main ( void )
{
    // Initialize all modules 
    SYS_Initialize ( NULL );

    debug_logging_init();
    messages_init();    
    heartbeat_init();
    switch1_init();
    switch2_init();
    mcp9804_init();
    
    while ( true )
    {
        // Maintain state machines of all polled MPLAB Harmony modules. 
        SYS_Tasks ( );
        
        heartbeat_tasks();
        switch1_tasks();
        //switch2_tasks();
    }

    // Execution should not come here during normal operation 
    return ( EXIT_FAILURE );
}

