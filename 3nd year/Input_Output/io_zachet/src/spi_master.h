#ifndef _SPI_MASTER_H
#define _SPI_MASTER_H

#include "systemc.h"

#define SPI_ADDR_SIZE 8
#define SPI_DATA_SIZE 8
#define SPI_TRANS_SIZE (SPI_ADDR_SIZE + SPI_DATA_SIZE)

#define CMD_REG_ADDR   0
#define DATA_SEND_ADDR 1
#define DATA_REC_ADDR  2

// CMD_REG bits
#define CMD_BUSY_BIT 0x01
#define CMD_SEND_BIT 0x02

SC_MODULE(SPIMaster)
{
    sc_in<bool>  clk_i;
    sc_in<int>   addr_bi;
    sc_in<int>   data_bi;
    sc_out<int>  data_bo;
    sc_in<bool>  wr_i;
    sc_in<bool>  rd_i;

    sc_out<bool> mosi_o;
    sc_in<bool>  miso_i;
    sc_out<bool> cs_o;
    
    SC_HAS_PROCESS(SPIMaster);
    
    SPIMaster(sc_module_name nm);
    ~SPIMaster();
    
    void bus_write();
    void bus_read();
    void spi_send();
    
private: 
    int cmd_reg;
    int data_send_reg;

    int send_bits_ctr;
    
};


#endif // _SPI_MASTER_H
