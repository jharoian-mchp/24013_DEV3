
//
// File:   swo.c
// Author: c14029
//
// Created on June 5, 2024, 9:45 PM
//

// SWO documentation:
// Section 5.4.5 of the MPLAB ICD 5 In-Circuit Debugger User's Guide
// https://onlinedocs.microchip.com/oxy/GUID-1FB866E7-F8EE-4F6C-92ED-0F60E926A717-en-US-2/GUID-46892059-4305-4FCA-BB07-EE0AED798EE5.html

#include "swo.h"
#include "definitions.h"

static void ITM_SWO_Enable();

void swo_init() {
    ITM_SWO_Enable();
}

//
// ITM_SWO_Enable()
//
// Enable SWO
//

void ITM_SWO_Enable() {
    uint32_t StimulusRegs;
    uint32_t _ITMPort  = 0; // The stimulus port from which SWO data is received
                            // and displayed.
    uint32_t TargetDiv = 1; // Has to be calculated according to
                            // the CPU speed and the output baud rate
  
    // Trace Clock Setup
    GCLK_REGS->GCLK_PCHCTRL[47] = 0x40;
  
    // Configure PB30 to Group H
    PORT_REGS->GROUP[1].PORT_PMUX[15] = 0x07;

    // Configure PB30 to High Drive strength and SWO
    PORT_REGS->GROUP[1].PORT_PINCFG[30] = 0x41;
    
    //
    // Enable access to SWO registers
    //
    CoreDebug->DEMCR |= (1 << 24);
    ITM->LAR = 0xC5ACCE55;
  
    //
    // Initially disable ITM and stimulus port
    // To make sure that nothing is transferred via SWO
    // when changing the SWO prescaler etc.
    //
  
    StimulusRegs = ITM->TER;
    StimulusRegs &= ~(1 << _ITMPort);
    ITM->TER = StimulusRegs;            // Disable ITM stimulus port
    ITM->TCR = 0;                       // Disable ITM
  
    //
    // Initialize SWO (prescaler, etc.)
    //
  
    TPI->SPPR = 0x00000002;             // Select NRZ mode
    TPI->ACPR = TargetDiv - 1;          // Example: 72/48 = 1,5 MHz
    ITM->TPR = 0x00000000;
    DWT->CTRL = 0x400003FE;
    TPI->FFCR = 0x00000100;
  
    //
    // Enable ITM and stimulus port
    //
    ITM->TCR = 0x1000D;                 // Enable ITM
    ITM->TER =  StimulusRegs | \
                (1 << _ITMPort);        // Enable ITM stimulus port
}

//
// ITM_SWO_PrintString(const char *s)
//
// Print a string over SWO via ITM
//

void ITM_SWO_PrintString(const char *s) {
  while (*s) {
    ITM_SendChar(*s++);
  }
}

