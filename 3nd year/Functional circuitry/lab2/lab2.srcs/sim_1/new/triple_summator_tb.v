`timescale 1ns / 1ps

module triple_summator_tb;
    reg [9:0] a,b,d;
    wire [10:0] c;
    reg [10:0] out_putin;
    triple_summator summa (
        .a(a),
        .b(b),
        .d(d),
        .out(c)
    );

 initial begin
        a = 8'b00000001; // 1
        b = 8'b00000001; // 1
        d = 8'b00000001; // 1
        #2
        a = 8'b00010011; // 19
        b = 8'b00000101; // 5
        d = 8'b01110001; // 
        #2
        a = 8'b10000101; // 133
        b = 8'b00000101;  // 5
        d = 8'b00000101; // 
        #2
        a = 8'b00011000; // 24 
        b = 8'b11111100; // 252
        d = 8'b00110001; // 
        #2
        a = 8'b11111111; // 255 
        b = 8'b11111111; // 255
        d = 8'b11111111; // 
    end
        
    initial begin 
        assign out_putin = a + b + d;
        $monitor("A=%b , B=%b, D,=%b SUM=%b, Sum_master=%b", a, b, d, c, out_putin);
    
        #10 $stop;
    end

endmodule
