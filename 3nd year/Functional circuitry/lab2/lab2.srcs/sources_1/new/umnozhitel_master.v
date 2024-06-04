`timescale 1ns / 1ps
module umnozhitel_master(
    input [9:0] AB,
    output reg [10:0] out_master
    );
    always @* begin
        out_master <= AB*2;
    end
    
endmodule
