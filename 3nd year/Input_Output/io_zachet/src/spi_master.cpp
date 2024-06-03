#include "spi_master.h"

SPIMaster::SPIMaster(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bi("addr_bi"),
    data_bi("data_bi"),
    data_bo("data_bo"),
    wr_i("wr_i"),
    rd_i("rd_i"),
    mosi_o("mosi_o"),
    miso_i("miso_i"),
    cs_o("cs_o")
     
{
    data_bo.initialize(0);
    cs_o.initialize(true);
    mosi_o.initialize(0);

    send_bits_ctr = 0;
    
    SC_METHOD(bus_write);
    sensitive << clk_i.pos();
    
    SC_METHOD(bus_read);
    sensitive << clk_i.pos();

    SC_METHOD(spi_send);
    sensitive << clk_i.pos();

}

SPIMaster::~SPIMaster()
{
}

void SPIMaster::spi_send()
{
    if(cmd_reg & CMD_SEND_BIT) {
        cs_o.write(0);
        cmd_reg = 0;
        mosi_o.write(data_send_reg & (1 << (SPI_TRANS_SIZE - 1)));
        data_send_reg = (data_send_reg << 1) & 0xFFFF;
        send_bits_ctr = SPI_TRANS_SIZE;
    }

    if(cs_o.read() == 0) {
        mosi_o.write(data_send_reg & (1 << (SPI_TRANS_SIZE - 1)));
        data_send_reg = (data_send_reg << 1) & 0xFFFF;
        send_bits_ctr--;

        if(send_bits_ctr == 0)
            cs_o.write(1);
    }
}

void SPIMaster::bus_read()
{
    int addr = addr_bi.read();
    if(wr_i.read()) {
        switch(addr) {
            case CMD_REG_ADDR: 
                cmd_reg = data_bi.read() & 0x00FF;
                break;
            case DATA_SEND_ADDR:
                data_send_reg = data_bi.read(); 
                //cout << hex << "data_send_reg = " << data_send_reg << endl;
                break;
        }
    }
}

void SPIMaster::bus_write()
{
    if(rd_i.read()) {
        switch(addr_bi.read()) {
            case CMD_REG_ADDR: data_bo.write((cmd_reg | !cs_o.read()) & 0x00FF);
                break;
            case DATA_SEND_ADDR: data_bo.write(data_send_reg);
                break;
        }
    }
}
