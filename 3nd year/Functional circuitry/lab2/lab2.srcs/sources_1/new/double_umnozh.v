`timescale 1ns / 1ps
module double_umnozh(
input [9:0] A,
input [9:0] B,
    output reg [10:0] outA,
    output reg [10:0] outB
    );
    always @* begin
        outA <= {A[9:0], 1'b0};
        outB <= {B[9:0], 1'b0};
    end
endmodule
