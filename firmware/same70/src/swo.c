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

#include "config/default/peripheral/port/plib_port.h"

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
    uint32_t _ITMPort  = 0;     // The stimulus port from which SWO data is 
                                // received and displayed.
    uint32_t CPUClock = 300000000; // CPU Clock in Hz
    uint32_t SWOBaudRate = 60000;   // Baud Rate in Hz
    uint32_t ITM_Clock_Prescale = (CPUClock / SWOBaudRate) - 1;   
    
    // Has to be calculated according to
                                // the CPU speed and the output baud rate
                                // 13 bit prescale.  CPU clock / targetDiv =
                                // SWO data rate
  
    // Trace Clock Setup 
    // GCLK_CM4_TRACE - PCHCTRL47
    // GCLK_CM7_TRACE - PCHCTRL63
//    GCLK_REGS->GCLK_PCHCTRL[63] = 0x40;
    GCLK_REGS->GCLK_PCHCTRL[63] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;

    while ((GCLK_REGS->GCLK_PCHCTRL[63] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
        /* Wait for synchronization */
    }

    // PIC32CX SG4/61 - SWO appears on PB30
    // Configure PB30 to Group H
//    PORT_REGS->GROUP[1].PORT_PMUX[15] = 0x07;

    // Configure PB30 to High Drive strength and SWO
//    PORT_REGS->GROUP[1].PORT_PINCFG[30] = 0x41;

    // PIC32CZ CA90 - SWO appears on PC19
    // Set PINCFG19.PMUXEN to 1 so peripheral overrides the GPIO
 //   PORT_REGS->GROUP[2].PORT_PINCFG[19] = 0x01;

    // Given PIN PC19, the PMUXm register is calculated as follows:
    // There are multiple GROUPS, or PORTS, based on the letter of the
    // pin designation.  A = 0, B = 1, C = 2, etc.
    // In this example, GROUP = 2 due to the pin belonging to PORT C.
    //
    // Each register contains even and odd, so the register number, m,
    // is calculated by int(n/2).  In this case, int(19/2) = int(9.5) = 9.
    // 19 is an odd number.
    
    // The value written to PORT_MUX.PMUXO is from Table 34-19.  In this case,
    // the value is 0x09 for SWO.
//    PORT_REGS->GROUP[2].PORT_PMUX[9] = (0x09 << 4);

    PORT_PinPeripheralFunctionConfig(PORT_PIN_PC19, PERIPHERAL_FUNCTION_J);
    
    //
    // Enable access to SWO registers
    //
    
    // Global Enable for all DWT and ITM features
    CoreDebug->DEMCR |= (1 << 24);
    
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
    TPI->ACPR = ITM_Clock_Prescale;          // Example: 300/300 = 1 MHz - 13 bit prescale
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

