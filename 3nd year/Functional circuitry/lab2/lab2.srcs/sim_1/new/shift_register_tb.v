`timescale 1ns / 1ps
module shift_register_tb;
    reg clk, reset, enable, rst,load;
    reg [7:0] data;
    wire [7:0] register;
    wire out;
    reg [7:0] master_data;
    reg master;
    shift_register shift(
    .clk(clk),
    .reset(reset),
    .enable(enable),
    .out(out),
    .rst(rst),
    .load(load),
    .data(data),
    .register(register)
    );
initial begin
    clk = 1'b0;
    repeat(100) #1 clk= ~clk;
end
initial begin
    rst = 1'b0;
    reset = 1'b0;
    //#4 reset = 1'b0;
    //#11 rst = 1'b1;
    //#1 rst = 1'b0;
    //#60 reset = 1'b1;
    //#2 reset = 1'b0;
end
initial begin
    enable = 1'b1;
    #20 enable = 1'b0;
    #10 enable = 1'b1; 
end
initial begin

    load = 1'b0;
    data = 8'b00110101;
    #1 load = 1'b1;
    #1 load = 1'b0;
    //#3 data = 8'b10000111;
    data = 8'b11110000;
    #11 load = 1'b1;
    #1 load = 1'b0;
end
initial begin
        #1 master_data <= 8'b00110101;
        repeat(5)#2 master_data = {1'b0, master_data[7:1]};
        #2 master_data = 8'b11110000;
        repeat(3)#2 master_data = {1'b0, master_data[7:1]};
        #12 master_data = {1'b0, master_data[7:1]};
        repeat(5)#2 master_data = {1'b0, master_data[7:1]};
end
initial begin
        master <= 0;
     #3 master = master_data[0]&1;
     repeat(8) #2 master = master_data[0]&1;
     #12 master = master_data[0]&1;
     repeat(5)#2 master = master_data[0]&1;
end
initial begin
    $monitor("time=%0d,reset=%b,rst=%b,enable=%b,data=%b,register=%b,out=%b",
                        $time,reset,rst,enable,data,register,out);
end
initial begin
#60 $stop;
end
endmodule
