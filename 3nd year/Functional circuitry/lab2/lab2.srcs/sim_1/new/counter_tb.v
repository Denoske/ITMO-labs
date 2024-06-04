module counter_tb;
  reg clk,reset,load,ud,rst;
  reg [7:0] data;
  wire [7:0] count;
  reg [7:0] master;
 
  // instance counter design
  simple_counter ct_1(
  .clk(clk),
  .reset(reset),
  .ud(ud),
  .load(load),
  .data(data),
  .count(count),
  .rst(rst)
  );
  //clock generator
  initial begin
    clk = 1'b0;
    repeat(100) #1 clk= ~clk;
   end
  //входной сигнал
   initial begin 
        rst = 1'b0;
        reset=1'b1;
        #4 reset=1'b0;
        #11 rst = 1'b1;
        #1 rst = 1'b0; 
        #60 reset=1'b1;
        #2 reset=1'b0;
   end
   initial begin
        load = 1'b0;
        #23 load=1'b1; 
        #5 load=1'b0;
   end
   initial begin
        ud = 1'b0;
        #2 ud=1'b1;
        #24 ud=1'b0;
   end
   initial begin
        data=8'b11111000;
        #14 data=8'b11111101;
        #2 data=8'b11111111;
   end
   initial begin
        master <= 8'b00000000;
        #4 master = master + 1 ;
        repeat(5)#2 master = master + 1 ;
        #1 master <= 8'b00000000;
        #1 master = master + 1 ;
        repeat(3) #2 master = master + 1 ;
        #2 master = 8'b11111111;
   end 
   initial begin
        $monitor("time=%0d,reset=%b,rst=%b,load=%b,ud=%b,data=%d,count=%d",
                               $time,reset,rst,load,ud,data,count);
   end
   initial begin
        #50 $stop;
   end
endmodule