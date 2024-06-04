`timescale 1ns / 1ps
module LRU_Buffer (
    input clk, //takt signal
    input rst, // асинхронный сигнал сброса
    input razresh,
    output wire o_clk,
    input [7:0] data,
    output reg [7:0] d1,d2,d3,d4,d5,d6,d7,d8,
    output wire [7:0] coun1,coun2,coun3,coun4,coun5,coun6,coun7,coun8,
    output reg [63:0] result
);
reg rst1,rst2,rst3,rst4,rst5,rst6,rst7,rst8; //сигналы сброса таймера пушта обратилисб к переменной
integer i;
Frequency_Divider delite1 ( // делитель частоты
  .clk(clk),
  .rst_n(rst),
  .o_clk(o_clk)
);

simple_counter count1( //инициализаци€ таймеров на каждую переменную буфера 
    .clk(o_clk),
    .rst(rst1),
    .ud(razresh),
    .count(coun1)
);
simple_counter count2(
    .clk(o_clk),
    .rst(rst2),
    .ud(razresh),
    .count(coun2)
);
simple_counter count3(
    .clk(o_clk),
    .rst(rst3),
    .ud(razresh),
    .count(coun3)
);
simple_counter count4(
    .clk(o_clk),
    .rst(rst4),
    .ud(razresh),
    .count(coun4)
);
simple_counter count5(
    .clk(o_clk),
    .rst(rst5),
    .ud(razresh),
    .count(coun5)
);
simple_counter count6(
    .clk(o_clk),
    .rst(rst6),
    .ud(razresh),
    .count(coun6)
);
simple_counter count7(
    .clk(o_clk),
    .rst(rst7),
    .ud(razresh),
    .count(coun7)
);
simple_counter count8(
    .clk(o_clk),
    .rst(rst8),
    .ud(razresh),
    .count(coun8)
);

always@(posedge o_clk) begin 
if(razresh == 1)begin // если разрешающий сигнал включен
    if (d1 == 0 || data == d1)begin // запись значени€ в свободную €чейку
        d1 <= data;
        rst1 = 1;
    end
    else if (d2 == 0 && data != d1 || data == d2) begin
        d2 <= data;
        rst2 = 1;
    end
    else if (d3 == 0 && data != d1 && data != d2 || data == d3)begin
        d3 <= data;
        rst3 = 1;
    end
    else if (d4 == 0 && data != d1 && data != d2 && data != d3 || data == d4)begin
        d4 <= data;
        rst4 = 1;
    end
    else if (d5 == 0 && data != d1 && data != d2 && data != d3 && data != d4 || data == d5)begin
        d5 <= data;
        rst5 = 1;
    end
    else if(d6 == 0 && data != d1 && data != d2 && data != d3 && data != d4 && data != d5 || data == d6)begin
        d6 <= data;
        rst6 = 1;
    end
    else if(d7 == 0 && data != d1 && data != d2 && data != d3 && data != d4 && data != d5 && data != d6 || data == d7)begin
        d7 <= data;
        rst7 = 1;
    end
    else if(d8 == 0 && data != d1 && data != d2 && data != d3 && data != d4 && data != d5 && data != d6 && data != d7 || data == d8)begin
        d8 <= data;
        rst8 = 1;
    end    
    else if(data != d1 && data != d2 && data != d3 && data != d4 && data != d5 && data != d6 && data != d7 && data != d8)begin // если все €чейки зан€ты, то идет обращение к самому забытому (у кого больше таймер)
        if      (coun1 > coun2 && coun1 > coun3 && coun1 > coun4 && coun1 > coun5 && coun1 > coun6 && coun1 > coun7 && coun1 > coun8)begin
            d1 <= data;
            rst1 <= 1;
        end 
        else if (coun2 > coun1 && coun2 > coun3 && coun2 > coun4 && coun2 > coun5 && coun2 > coun6 && coun2 > coun7 && coun2 > coun8)begin
            d2 <= data;
            rst2 <= 1;
        end
        else if (coun3 > coun1 && coun3 > coun2 && coun3 > coun4 && coun3 > coun5 && coun3 > coun6 && coun3 > coun7 && coun3 > coun8)begin
            d3 <= data;
            rst3 <= 1;
        end
        else if (coun4 > coun1 && coun4 > coun2 && coun4 > coun3 && coun4 > coun5 && coun4 > coun6 && coun4 > coun7 && coun4 > coun8)begin
            d4 <= data;
            rst4 <= 1;
        end
        else if (coun5 > coun1 && coun5 > coun2 && coun5 > coun3 && coun5 > coun4 && coun5 > coun6 && coun5 > coun7 && coun5 > coun8)begin
            d5 <= data;
            rst5 <=1;
        end
        else if (coun6 > coun1 && coun6 > coun2 && coun6 > coun3 && coun6 > coun4 && coun6 > coun5 && coun6 > coun7 && coun6 > coun8)begin
            d6 <= data;
            rst6 <=1;
        end
        else if (coun7 > coun1 && coun7 > coun2 && coun7 > coun3 && coun7 > coun4 && coun7 > coun5 && coun7 > coun6 && coun7 > coun8)begin
            d7 <= data;
            rst7 <=1;
        end
        else if (coun8 > coun1 && coun8 > coun2 && coun8> coun3 && coun8> coun4 && coun8 > coun5 && coun8 > coun6 && coun8 > coun7)begin
            d8 <= data;
            rst8 <= 1;
        end
    end
end
end

always@(negedge o_clk) begin       // колено обнулени€ счетчика в один такт
    for(i=0;i<=7;i=i+1)begin
        result[i] = coun1[i];
        result[i+8] = coun2[i];
        result[i+16] = coun3[i];
        result[i+24] = coun4[i];
        result[i+32] = coun5[i];
        result[i+40] = coun6[i];
        result[i+48] = coun7[i];
        result[i+56] = coun8[i];        
    end  
    if (rst1 == 1 && d1 != 0) begin
        rst1 <= 0;
    end
    if (rst2 == 1 && d2 != 0) begin
        rst2 <= 0;
    end
    if (rst3 == 1 && d3 != 0) begin
        rst3 <= 0;
    end
    if (rst4 == 1 && d4 != 0) begin
        rst4 <=0;
    end
    if (rst5 == 1 && d5 != 0) begin
        rst5 <=0;
    end
    if (rst6 == 1 && d6 != 0) begin
        rst6 <=0;
    end
    if (rst7 == 1 && d7 != 0) begin
        rst7 <=0;
    end
    if (rst8 == 1 && d8 !=0) begin
        rst8 <=0;
    end
end



always@(posedge rst) begin  // инициализаци€ переменных какнули
    result <= 0;
    d1<=0;
    d2<=0;
    d3<=0;
    d4<=0;
    d5<=0;
    d6<=0;
    d7<=0;
    d8<=0;
    rst1 <= 1;
    rst2 <= 1;
    rst3 <= 1;
    rst4 <= 1;
    rst5 <= 1;
    rst6 <= 1;
    rst7 <= 1;
    rst8 <= 1;
end

endmodule // досвидани€!