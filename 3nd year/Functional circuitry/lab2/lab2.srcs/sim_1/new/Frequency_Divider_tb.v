`timescale 1ns / 1ps

module Frequency_Divider_tb;
reg clk;
reg rst_n;
wire o_clk;
reg master_clk;

Frequency_Divider u0 (
  .clk(clk),
  .rst_n(rst_n),
  .o_clk(o_clk)
);

initial begin
  clk   = 1'b0;
  rst_n = 1'b0;
  #1 rst_n = 1'b1;
end

// 50MHz clk
initial begin
    clk = 1'b0;
    repeat(100) #1 clk= ~clk;
    end
 initial begin
    #1
    master_clk = 1'b0;
    repeat(100) #4 master_clk = ~master_clk;
    end
initial begin
    $monitor("clk=%b,rst_n=%b,o_clk=%b", clk ,rst_n , o_clk);
    #100 $stop;
end    
  
endmodule