`timescale 1ns / 1ps

module shift_register (
    input clk,                              // тактовый сигнал
    input reset,                            // сигнал сброса
    input enable,                           // сигнал разрешения
    input rst,                              // асинхронный сброс
    input load,                             // сигнал загрузки данных в регистр
    input [7:0] data,                       // параллельный вход
    output reg out,                         //  выход крайней правой
    output reg [7:0] register
);

always @(posedge rst) begin
    if (rst) begin
        out <= 0;
        register <= 8'b0;
    end
end
//always @(posedge load) begin              // Если установлен флаг load, то загружаем данные из даты в регистр
//    register = data;
//end
//reg [7:0] register;                       // объявление регистра
always @(posedge clk) begin                 //работа с регистром и сдвигами
    if (load) begin                         // Если установлен флаг load, то загружаем данные из даты в регистр
        register = data; 
    end else begin
        if (reset) begin
            register <= 8'b0;               // сброс регистра
        end else begin
        if (enable) begin
            register [7] <= 0;              // Присвоение крайнему левому значение 0
            out <= register[0];             // Запоминаем крайний правый
            register <= {register[7:1]};    // сдвиг вправо
            end
        end
    end
end


endmodule

