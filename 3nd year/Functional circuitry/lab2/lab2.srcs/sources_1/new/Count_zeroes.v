`timescale 1ns / 1ps

module Count_zeroes(
    input clk,            ///Сигнал такотовой частоты
    input rst,              ///Асинхронный сигнал сброса
    input measure_req_i, 
    input ready_i,              
    output wire o_clk,      ///необязательный выход (для наглядности) 
    output wire [7:0] result_data_o,
    output reg result_rsp_o,
    output reg busy_o
    );
    reg lets_count;
    
    Frequency_Divider delitel(
        .clk(clk),     
        .rst_n(rst), 
        .o_clk(o_clk)  //переводит изначальную тактовую частоту в тактовую частоту делителя
    );  
    simple_counter count(
        .clk(o_clk),
        .rst(rst),
        .ud(lets_count),
        .count(result_data_o)
    
    );   
    always@(*)begin
        if (result_rsp_o == ready_i) begin
            #1
            result_rsp_o <=0;
        end
        
    end
    always@(posedge measure_req_i) begin
        if(measure_req_i && lets_count == 1) begin
            lets_count <=0;
            busy_o <= 0;
            result_rsp_o <= 1;
            
        end
        else begin
            lets_count <=1;
            busy_o <=1;
            result_rsp_o <= 0;
        end
    end
endmodule
