#include "cpu.h"
#include "spi_master.h"
#include "display.h"

int sc_main(int argc, char* argv[])
{
    
    CPU cpu_core("cpu");
    SPIMaster spi_master("spi_master");
    Display display("display");
    
    sc_clock clk("clk", sc_time(10, SC_NS));
    sc_signal<int> addr;
    sc_signal<int> data_cpu_bo;
    sc_signal<int> data_cpu_bi;
    sc_signal<bool> wr;
    sc_signal<bool> rd;
    sc_signal<bool> mosi;
    sc_signal<bool> miso;
    sc_signal<bool> cs;
    
    cpu_core.clk_i(clk);
    cpu_core.addr_bo(addr);
    cpu_core.data_bi(data_cpu_bi);
    cpu_core.data_bo(data_cpu_bo);
    cpu_core.wr_o(wr);
    cpu_core.rd_o(rd);
    
    spi_master.clk_i(clk);
    spi_master.addr_bi(addr);
    spi_master.data_bi(data_cpu_bo);
    spi_master.data_bo(data_cpu_bi);
    spi_master.wr_i(wr);
    spi_master.rd_i(rd);
    spi_master.mosi_o(mosi);
    spi_master.miso_i(miso);
    spi_master.cs_o(cs);

    display.sclk_i(clk);
    display.mosi_i(mosi);
    display.miso_o(miso);
    display.cs_i(cs);
    
    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, addr, "addr_bo");
    sc_trace(wf, data_cpu_bi, "data_bi");
    sc_trace(wf, data_cpu_bo, "data_bo");
    sc_trace(wf, wr, "wr");
    sc_trace(wf, rd, "rd");
    sc_trace(wf, mosi, "mosi");
    sc_trace(wf, miso, "miso");
    sc_trace(wf, cs, "cs");

    sc_start();

    sc_close_vcd_trace_file(wf);
    
    return(0);
    
}
