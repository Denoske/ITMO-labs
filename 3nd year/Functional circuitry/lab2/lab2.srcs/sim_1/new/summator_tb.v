`timescale 1ns / 1ps

module summator_tb;
    reg [10:0] a,b;
    wire [10:0] c;

summator sum (
    .a(a),
    .b(b),
    .c(c)
    );
    reg [10:0] out_putin;
    
    initial begin
        a = 8'b00000001; // 1
        b = 8'b00000001; // 1
        #2
        a = 8'b00010011; // 19
        b = 8'b00000101; // 5
        #2
        a = 8'b10000101; // 133
        b = 8'b00000101;  // 5
        #2
        a = 8'b00011000; // 24 
        b = 8'b11111100; // 252
        #2
        a = 8'b11111111; // 255 
        b = 8'b11111111; // 255
    end
        
    initial begin 
        assign out_putin = a + b;
        $monitor("A=%b , B=%b, SUM=%b, Sum_master=%b", a, b, c, out_putin);
    
        #10 $stop;
    end

endmodule
