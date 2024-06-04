`timescale 1ns / 1ps
module simple_counter(
    clk, // тактовый сигнал
    reset, // сигнал сброса
    ud, //сигнал инкремента up_down
    load, // сигнал загрузки значения счетчика
    data, 
    count, //как идея сюда можно добавить еще один регистр - запись счетчика в дату
    rst // асинхронный сброс
);
  input clk,reset,load,ud,rst;
  input [7:0] data;
  output reg [7:0] count;
  //всегда блок будет выполняться на каждом положительном фронте тактовой частоты
  always@(negedge clk or posedge rst)  ///Для Count zero установить на negedge! Для остальных на posedge
  begin
    if(rst)
        count = 0;   ///
    else if(reset)    //Установите счетчик на ноль
      count = 0;
    else if(load)    //загрузите в счетчик значение данных
      count = data;
    else if(ud)        //инкремент
      count = count + 1;
    else            //декремент убрал его 
      count = count; 
  end
endmodule












