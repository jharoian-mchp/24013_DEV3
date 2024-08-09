//
// File:   mcp9804.c
// Author: c14029
//
// Created on May 28, 2024, 3:22 PM
//

#include <stdbool.h>
#include "mcp9804.h"
#include "peripheral/sercom/i2c_master/plib_sercom6_i2c_master.h"
#include "messages.h"

enum MCP9804_state_e {
    MCP9804_ON = 0xdd00,
    MPC_OFF = 0x00dd
};

struct MCP9804_DATA_s {
    enum MCP9804_state_e state;
    uint16_t adc_reading;
    float temp;
    bool valid_temp;
};

static struct MCP9804_DATA_s mcp9804Data;


void mcp9804_init() {
    mcp9804Data.state = 0;
    mcp9804Data.valid_temp = false;
}

void mcp9804_read_temp() {
    const uint16_t address = 0x0018;
    uint8_t write_seq[] = {0x05};
    uint8_t read_buffer[2];
    bool retval, i2c_busy, negative = false;
    float temperature;
    
    i2c_busy = SERCOM6_I2C_IsBusy();
    
    if(i2c_busy == false) {
        retval = SERCOM6_I2C_WriteRead( address, write_seq, sizeof(write_seq), \
                                        read_buffer, sizeof(read_buffer) );
        if(retval==true) {
            while(SERCOM6_I2C_IsBusy());
            if((read_buffer[0] & 0x10) == 0x10) {
                negative = true;
            }
            read_buffer[0] &= 0x0F;
            temperature =   (( (float) read_buffer[0] ) * 16.0 ) \
                            + (( (float) read_buffer[1] ) / 16.0 );
            if(negative == true) {
                temperature = 256.0 - temperature;
            }
            messages_temp(temperature);
        }
    }
}

//void SERCOM6_I2C_Initialize(void);
//bool SERCOM6_I2C_Read(uint16_t address, uint8_t* rdData, uint32_t rdLength);
//bool SERCOM6_I2C_Write(uint16_t address, uint8_t* wrData, uint32_t wrLength);
//bool SERCOM6_I2C_WriteRead(uint16_t address, uint8_t* wrData, uint32_t wrLength, uint8_t* rdData, uint32_t rdLength);
