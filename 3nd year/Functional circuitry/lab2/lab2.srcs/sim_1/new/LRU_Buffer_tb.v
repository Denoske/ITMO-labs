`timescale 1ns / 1ps

module LRU_Buffer_tb;
    reg clk; //takt signal
    reg rst; // асинхронный сигнал сброса
    reg razresh;
    wire o_clk;
    reg [7:0] data;
    wire [7:0] d1,d2,d3,d4,d5,d6,d7,d8;
    wire [7:0] coun1,coun2,coun3,coun4,coun5,coun6,coun7,coun8;
    wire [63:0] result;
    LRU_Buffer b1(
        .clk(clk),
        .rst(rst),
        .razresh(razresh),
        .o_clk(o_clk),
        .data(data),
        .d1(d1),.d2(d2),.d3(d3),.d4(d4),.d5(d5),.d6(d6),.d7(d7),.d8(d8),
        .coun1(coun1),.coun2(coun2),.coun3(coun3),.coun4(coun4),.coun5(coun5),.coun6(coun6),.coun7(coun7),.coun8(coun8),
        .result(result)
        );
    initial begin
        clk = 1'b0;
        repeat(200) #1 clk= ~clk;
    end  
    initial begin
        razresh = 1'b1;
        rst=1'b0;
        #1 rst = 1'b1;
        #1 rst = 1'b0;
    end
    initial begin
           data = 8'b00000000;
        #7 data = 8'b00000001;
        #8 data = 8'b00000010;
        #8 data = 8'b00000100;
        #8 data = 8'b00001000;
        #8 data = 8'b00010000;
        #8 data = 8'b00100000;
        #8 data = 8'b01000000;
        #8 data = 8'b10000000;
        #8 data = 8'b10000001;
        #8 data = 8'b00000010;
        #8 data = 8'b00000100;
        #8 data = 8'b00001000;
        #8 data = 8'b00010000;
        #8 data = 8'b00100000;
        #8 data = 8'b01000000;
        #8 data = 8'b10000000;
        #8 data = 8'b00000001;
        #8 data = 8'b00000010;
        #8 data = 8'b00000100;
        #8 data = 8'b00001000;
        #8 data = 8'b00010000;
        #8 data = 8'b00100000;
        #8 data = 8'b01000000;
        #8 data = 8'b10000000; 
    end  
    initial begin
        #200 $stop;
    end
endmodule