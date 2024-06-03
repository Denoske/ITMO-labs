#ifndef _CPU_H
#define _CPU_H

#include "systemc.h"

SC_MODULE(CPU)
{
    sc_in<bool>  clk_i;
    sc_out<int>  addr_bo;
    sc_in<int>   data_bi;
    sc_out<int>  data_bo;
    sc_out<bool> wr_o;
    sc_out<bool> rd_o;
    
    SC_HAS_PROCESS(CPU);
    
    CPU(sc_module_name nm);
    ~CPU();
    
    void mainThread();
private:

    void bus_write(int addr, int data);
    int  bus_read(int addr);

    void spi_write(int addr, int data);
    int spi_read(int addr);

};


#endif
