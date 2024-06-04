`timescale 1ns / 1ps

module Frequency_Divider(
    input clk,
    input rst_n, //импульс сброса
    output reg o_clk
    );
 reg [1:0] cnt;

always@(posedge clk) begin // убрал or negedge rst_n
  if (rst_n)                /// было !rst_n
    cnt <= 0;
  else if (cnt == 3) // 0 ~ 3
    cnt <= 0;
  else
    cnt <= cnt + 1;
end

always@(posedge clk) begin // убрал or negedge rst_n
  if (rst_n)                /// было !rst_n
    o_clk <= 0;
  else if (cnt < 2) // 0 ~ 1
    o_clk = 0;
  else              // 2 ~ 3
    o_clk = 1;    
end   
    
endmodule
