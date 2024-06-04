`timescale 1ns / 1ps
module Avtomat_v2_tb;
        reg [9:0] A,B;
        wire [10:0] result;

Avtomat_v2 avt(
    .value1(A),
    .value2(B),
    .result(result)
);
reg [10:0] result_master;

initial begin
        A = 8'b00000001; // 1
        B = 8'b00000001; // 1
        #2
        A = 8'b00010011; // 19
        B = 8'b00000101; // 5
        #2
        A = 8'b01000101; // 69
        B = 8'b00000101;  // 5 
        #2
        A = 8'b00011000; // 24 
        B = 8'b00111100; // 60
        #2
        A = 8'b11111111; // 255
        B = 8'b11111111; // 255
end           

initial begin
    assign result_master = ((A+B)*2+B);
    $monitor("A=%b,B=%b,Result=%b,Master = %b", A ,B , result, result_master);
    #10 $stop;
end

endmodule
