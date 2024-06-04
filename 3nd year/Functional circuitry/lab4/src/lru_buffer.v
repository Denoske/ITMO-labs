`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09.06.2023 21:16:13
// Design Name: 
// Module Name: lru_buffer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module lru_buffer(
    input clk,
    input rst,
    input valid_data,
    input [11:0] data,
    input [1:0] sw,
    output reg [11:0] out);
    
    
    reg [11:0] out0, out1, out2, out3;    
    reg[2:0] state;
    
    reg [2:0] ages[0:3];
    reg [2:0] hitIndex;
    reg [2:0] index;
    
    integer j;
    
    parameter IDLE = 0, CHECKING_HIT = 1, HIT_UPDATING = 2, nHIT_UPDATING = 3;
    

    
    always @ (posedge clk, negedge rst) begin
        if (!rst) begin
            out0 <= 12'd0;
            out1 <= 12'd0;
            out2 <= 12'd0;
            out3 <= 12'd0;
            hitIndex <= 4'd0;
            for(j = 0; j < 4; j = j + 1) ages[j] <= j;
            state <= IDLE;
        end else begin
            case(state)
                IDLE: begin
                    if(valid_data) begin 
                        state <= CHECKING_HIT;
                        hitIndex <= 0;
                        index <= 0;
                    end
                end
                CHECKING_HIT: begin
                    if(hitIndex > 3) state <= nHIT_UPDATING;
                    else begin
                        case(hitIndex)
                                0:  begin
                                    if(out0 == data) state <= HIT_UPDATING;
                                    else hitIndex <= hitIndex + 1;  
                                end
                                1:  begin  
                                    if(out1 == data) state <= HIT_UPDATING;
                                    else hitIndex <= hitIndex + 1;  
                                end
                                2:  begin
                                    if(out2 == data) state <= HIT_UPDATING;
                                    else hitIndex <= hitIndex + 1;  
                                end                            
                                3:  begin
                                    if(out3 == data) state <= HIT_UPDATING;
                                    else hitIndex <= hitIndex + 1;  
                                end
                        endcase           
                    end
                end
                HIT_UPDATING: begin
                    if(index > 3) begin
                        state <= IDLE;
                        ages[hitIndex] = 0;
                    end else begin
                        if(ages[index] < ages[hitIndex]) ages[index] <= ages[index] + 1;
                        index <= index + 1;                
                    end
                end
                nHIT_UPDATING: begin
                    if(index > 3) state <= IDLE;
                    else begin
                        if(ages[index] == 3) begin
                            ages[index] <= 0;
                            case(index)
                                0:  out0 <= data;
                                1:  out1 <= data;
                                2:  out2 <= data;
                                3:  out3 <= data;
                            endcase
                        end else ages[index] <= ages[index] + 1;
                        index <= index + 1;
                    end
                end
            endcase
               
            case(sw)
                0: out <= out0;
                1: out <= out1;
                2: out <= out2;
                3: out <= out3;
            endcase
        end
    end
endmodule