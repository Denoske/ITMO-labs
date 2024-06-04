`timescale 1ns / 1ps
module summator(
    input [9:0] a,
    input [9:0] b,
    output reg [10:0] c
    );
    integer perenos = 0;
    integer i;
    always@(*) begin
       for(i=0;i<=9;i=i+1) begin
            if (a[i]==0 && b[i]==0)begin
                if ( perenos == 0) begin
                    c[i] <= 0;
                    perenos = 0;
                end 
                else if ( perenos == 1) begin
                    c[i] <= 1;
                    perenos = 0;
                end
            end
            else if (a[i] == 1 && b[i] == 1) begin
                if ( perenos == 0) begin
                    c[i] <= 0;
                    perenos = 1;
                end
                else if ( perenos == 1) begin
                    c[i] <= 1;
                    perenos = 1;
                end
            end
            else if (a[i] != b[i]) begin
                if (perenos == 0) begin
                    c[i] <= 1;
                    perenos = 0;
                end
                else if ( perenos == 1) begin
                    c[i] <= 0;
                    perenos = 1;
                end
            end
       end
       if (perenos == 1) begin
            c[10] <= 1;
            perenos = 0;
       end
       else begin
            c[10] <= 0;
       end  
     end
endmodule