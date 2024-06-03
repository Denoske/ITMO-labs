#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "systemc.h"

#define DISPLAY_SIZE  16

#define SPI_ADDR_SIZE 8
#define SPI_DATA_SIZE 8
#define SPI_TRANS_SIZE (SPI_ADDR_SIZE + SPI_DATA_SIZE)

#define DISP_CMD_REG_ADDR 0
#define DISP_SYMBOL_ADDR  1 
#define DISP_CURSOR_ADDR  2

// cmd
#define DISP_UPDATE_CMD 1
#define DISP_CLEAR_CMD  2

SC_MODULE(Display)
{
    sc_in<bool>  sclk_i;
    sc_in<bool>  mosi_i;
    sc_out<bool> miso_o;
    sc_in<bool> cs_i;
    
    SC_HAS_PROCESS(Display);
    
    Display(sc_module_name nm);
    ~Display();

    void spi_receive();
    
private: 
    int cursor_reg;
    int data_rec_reg;
    int addr_reg;
    int data_reg;

    int rec_bits_ctr;

    char disp_buf[DISPLAY_SIZE+1]; // +1 = /0

    void update_cursor(int val);
    void clear();
};


#endif // _DISPLAY_H
