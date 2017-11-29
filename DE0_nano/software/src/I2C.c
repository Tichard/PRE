// --------------------------------------------------------------------
// Copyright (c) 2007 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------
#include "I2C.h"

//SDA 1->0 while SCL=1
void i2c_start(alt_u32 clk_base, alt_u32 data_base){
    
    // make sure it is in normal state
    SDA_DIR_OUT(data_base);  // data output enabled
    
    
    
    // start condition
    SDA_HIGH(data_base); // data high
    SCL_HIGH(clk_base);
    SCL_DELAY;
     
    SDA_LOW(data_base); // data low
    SCL_DELAY; 
    SCL_LOW(clk_base); // clock low
    SCL_DELAY;
}

// SDA 0->1 while SCL=1
void i2c_stop(alt_u32 clk_base, alt_u32 data_base){
    // assume SCL = 0
    
    SDA_DIR_OUT(data_base);  // data output enabled
    SDA_LOW(data_base); // Data Low
    //SCL_DELAY; 
    SCL_HIGH(clk_base);  // clock high
    SCL_DELAY; // clock high long delay
    SDA_HIGH(data_base); // data high
    SCL_DELAY; // data high delay
    

    
}

bool i2c_write(alt_u32 clk_base, alt_u32 data_base, alt_u8 Data){ // return true if device response ack
    alt_u8 Mask = 0x80;
    bool bAck;
    int i;
    
    // assume, SCL = 0
    
    SDA_DIR_OUT(data_base);  // data write mode
    
    for(i=0;i<8;i++){
        SCL_LOW(clk_base);  // new, make sure data change at clk low
        // output data on bus
        if (Data & Mask){ // there is a delay in this command
            SDA_HIGH(data_base);
        }else{    
            SDA_LOW(data_base);
        }
        Mask >>= 1; // there is a delay in this command
        // clock high
        SCL_HIGH(clk_base);
        SCL_DELAY;
        SCL_LOW(clk_base);
        SCL_DELAY;
    }
    
    //===== get ack
    SDA_DIR_IN(data_base);  // data read mode
    //SCL_DELAY;
    // clock high
    SCL_HIGH(clk_base);  // clock high
    SCL_DELAY;  // clock high delay
    bAck = SDA_READ(data_base)?FALSE:TRUE;  // get ack
    //SCL_DELAY;
    //SDA_DIR_OUT;
    SCL_LOW(clk_base); // clock low         
    SCL_DELAY; // clock low delay
    return bAck;
}    

void i2c_read(alt_u32 clk_base, alt_u32 data_base, alt_u8 *pData, bool bAck){ // return true if device response ack
    alt_u8 Data=0;
    int i;
    
    // assume SCL = low
    
    SDA_DIR_IN(data_base);  // set data read mode
    SCL_LOW(clk_base); // clock low
    SCL_DELAY; // clock low delay

    for(i=0;i<8;i++){
        Data <<= 1;
        SCL_HIGH(clk_base);  // clock high
        SCL_DELAY;
        if (SDA_READ(data_base))  // read data   
            Data |= 0x01;
        SCL_LOW(clk_base);  // clock log  
        SCL_DELAY;
    }
    
    // send ACK
    SCL_LOW(clk_base);  // new, make sure data change at clk low
    SDA_DIR_OUT(data_base);  // set data write mode
    if (bAck)
        SDA_LOW(data_base);
    else
        SDA_HIGH(data_base);
    SCL_HIGH(clk_base); // clock high
    SCL_DELAY; // clock high  delay
    SCL_LOW(clk_base); // clock low
    SCL_DELAY; // clock low delay
    SDA_LOW(data_base);  // data low
    SCL_DELAY; // data low delay
//    SDA_DIR_IN;  // set data read mode
    
    *pData = Data;
}

