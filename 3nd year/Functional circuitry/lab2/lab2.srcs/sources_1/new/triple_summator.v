`timescale 1ns / 1ps
module triple_summator(
    input [9:0] a,
    input [9:0] b,
    input [9:0] d,
    output reg [10:0] out
    );
    reg [10:0] c;
    integer perenos = 0;
    integer i,j;
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
     for(j=0;j<=9;j=j+1) begin
            if (c[j]==0 && d[j]==0)begin
                if ( perenos == 0) begin
                    out[j] <= 0;
                    perenos = 0;
                end 
                else if ( perenos == 1) begin
                    out[j] <= 1;
                    perenos = 0;
                end
            end
            else if (c[j] == 1 && d[j] == 1) begin
                if ( perenos == 0) begin
                    out[j] <= 0;
                    perenos = 1;
                end
                else if ( perenos == 1) begin
                    out[j] <= 1;
                    perenos = 1;
                end
            end
            else if (c[j] != d[j]) begin
                if (perenos == 0) begin
                    out[j] <= 1;
                    perenos = 0;
                end
                else if ( perenos == 1) begin
                    out[j] <= 0;
                    perenos = 1;
                end
            end
       end
       if (perenos == 1) begin
            out[10] <= 1;
            perenos = 0;
       end
       else begin
            out[10] <= 0;
       end  
     
     end
endmodule

///(A+b)*2+b = 2a+2b+b