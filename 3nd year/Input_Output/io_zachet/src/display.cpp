#include "display.h"

Display::Display(sc_module_name nm)
    :sc_module(nm),
    sclk_i("sclk_i"),
    mosi_i("mosi_i"),
    miso_o("miso_o"),
    cs_i("cs_i")
     
{
    miso_o.initialize(0);

    rec_bits_ctr = 0;
    clear();

    SC_METHOD(spi_receive);
    sensitive << sclk_i.neg();

}

void Display::spi_receive()
{
    if(cs_i.read() == 0) {
        data_rec_reg = ((data_rec_reg << 1) | mosi_i.read()) & 0x0000FFFF;

        rec_bits_ctr++;

        if(rec_bits_ctr == SPI_ADDR_SIZE) {
            addr_reg = data_rec_reg & 0x00FF;
            //cout << "DISPLAY | addr = " << addr_reg << endl;
        }

        if(rec_bits_ctr == SPI_TRANS_SIZE) {
            data_reg = data_rec_reg & 0x00FF;
            rec_bits_ctr = 0;
            //cout << "DISPLAY | data = " << data_reg << endl;

            switch(addr_reg) {
                case DISP_CMD_REG_ADDR:
                    if(data_reg == DISP_UPDATE_CMD) {
                        cout << disp_buf;
                    } 
                    if(data_reg == DISP_CLEAR_CMD)
                        clear();
                    break;
                case DISP_SYMBOL_ADDR:
                    disp_buf[cursor_reg] = data_reg;
                    update_cursor(cursor_reg + 1);
                    break;
                case DISP_CURSOR_ADDR:
                    update_cursor(data_reg);
                    break;
            }
        }
            
    }
}

 void Display::update_cursor(int val)
 {
    if((val >= 0) && (val < DISPLAY_SIZE))
        cursor_reg = val;
 }

 void Display::clear()
 {
    for(int i = 0; i < DISPLAY_SIZE; i++)
        disp_buf[i] = ' ';
    disp_buf[DISPLAY_SIZE] = '\n';
    cursor_reg = 0;
 }


Display::~Display()
{
}
