`timescale 1ns / 1ps
module Count_zeroes_tb;
    reg clk,rst,measure_req_i,ready_i;
    wire o_clk,result_rsp_o,busy_o;
    wire [7:0] result_data_o;

Count_zeroes fn (
  .clk(clk),
  .rst(rst),
  .measure_req_i(measure_req_i),
  .ready_i(ready_i),
  .o_clk(o_clk),
  .result_data_o(result_data_o),
  .result_rsp_o(result_rsp_o),
  .busy_o(busy_o)
);

initial begin
  rst = 1'b0;
  #1 rst = 1'b1;
  #2 rst = 1'b0;
end
initial begin
    ready_i = 1'b1;
    measure_req_i = 1'b0;
    #3 measure_req_i = 1'b1;
    #1 measure_req_i = 1'b0;
    #40 measure_req_i = 1'b1;
    #1 measure_req_i = 1'b0;
    //#3 ready_i = 1'b1;
    //#1 ready_i = 1'b0;

end
initial begin
    clk = 1'b0;
    repeat(100) #1 clk= ~clk;
    end

  
initial begin
    //$monitor("clk=%b,rst_n=%b,o_clk=%b", clk ,rst , o_clk);
    #50 $stop;
end    
endmodule
