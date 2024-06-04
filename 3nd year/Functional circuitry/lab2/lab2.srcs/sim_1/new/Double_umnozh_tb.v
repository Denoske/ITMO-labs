`timescale 1ns / 1ps

module Double_umnozh_tb;
    reg [9:0] A,B;
    wire [10:0] outA,outB;
    reg [10:0] outA_master,outB_master;
    
    double_umnozh umozh(
    .A(A),
    .B(B),
    .outA(outA),
    .outB(outB)
    );

initial begin
           A = 8'b00000001; B = 8'b00000001;
        #1 A = 8'b00000010; B = 8'b00000010;
        #1 A = 8'b00000100; B = 8'b00000100;
        #1 A = 8'b00001000; B = 8'b00001000;
        #1 A = 8'b00010000; B = 8'b00010000;
        #1 A = 8'b00100000; B = 8'b00100000;
        #1 A = 8'b01000000; B = 8'b01000000;
        #1 A = 8'b10000000; B = 8'b10000000;
        #1 A = 8'b00110101; B = 8'b00110101;
        #1 A = 8'b00001111; B = 8'b00001111;
        #1 A = 8'b11111111; B = 8'b11111111;
    end
    initial begin
        assign outA_master = A*2;
        assign outB_master = B*2;

        $monitor("A = %b, B =%b, outA = %b, outB= %b, outA_master= %b, outB_master = %b"
                                ,A,B,outA,outB,outA_master, outB_master);
        #10 $stop;
    end

endmodule
