`timescale 1ns / 1ps

module Avtomat_v2(
    input [9:0] value1,
    input [9:0] value2,
    output [10:0] result
    );
    wire [10:0] outA,outB;
double_umnozh umnozh(
    .A(value1),
    .B(value2),
    .outA(outA),
    .outB(outB)
    );
 
 triple_summator summa(
    .a(outA),
    .b(outB),
    .d(value2),
    .out(result)
 );


endmodule
