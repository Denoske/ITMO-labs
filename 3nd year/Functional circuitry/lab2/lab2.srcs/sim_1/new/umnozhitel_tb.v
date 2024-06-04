`timescale 1ns / 1ps
module umnozhitel_tb;
    reg [9:0] AB;
    wire [10:0] out, out_master;
    
    umnozhitel umozh(
    .AB(AB),
    .out(out)
    );
    
    umnozhitel_master master(
    .AB(AB),
    .out_master(out_master)
    );
    
    
    initial begin
           AB = 8'b00000001;
        #1 AB = 8'b00000010;
        #1 AB = 8'b00000100;
        #1 AB = 8'b00001000;
        #1 AB = 8'b00010000;
        #1 AB = 8'b00100000;
        #1 AB = 8'b01000000;
        #1 AB = 8'b10000000;
        #1 AB = 8'b00110101;
        #1 AB = 8'b00001111;
        #1 AB = 8'b00111111;
    end
    initial begin

        $monitor("AB = %b, out = %b, out_master= %b",AB,out,out_master);
        #10 $stop;
    end
    
endmodule
