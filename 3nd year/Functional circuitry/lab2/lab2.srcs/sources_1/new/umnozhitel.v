`timescale 1ns / 1ps
module umnozhitel(
    input [9:0] AB,
    output reg [10:0] out
    );
    always @* begin
        out <= {AB[9:0], 1'b0};
    end
endmodule
