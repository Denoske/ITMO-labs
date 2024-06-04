`timescale 1ns / 1ps

module lru_buffer_one_tact(clk, rst, valid_data, data, sw, out);
    input clk, rst, valid_data;
    input [15:0] data;
    input [3:0] sw;
    output [15:0] out;
    
    
    reg [15:0] buff_mem [7:0];
    reg [3:0] ages [7:0];
    reg [3:0] hitIndex;
    reg [3:0] index;
    
    integer i;
    assign out = buff_mem[sw];
    
    reg valid_data_latched;
    always @(posedge clk) valid_data_latched <= valid_data;
    
    // ages update
    always @(posedge clk) begin
        if (rst) begin  
            for(i = 0; i < 8; i = i + 1) ages[i] <= i;
        end else if (!valid_data_latched && valid_data) begin
            for (i = 0; i < 8; i = i + 1) begin
                if (i == hitIndex) begin
                    ages[i] <= 0;
                end
                else if (ages[i] < ages[hitIndex]) begin
                    ages[i] <= ages[i] + 1;
                end
            end
        end
    end
    
    
    // buff mem update
    always @(posedge clk) begin
        if (rst) begin
            for(i = 0; i < 8; i = i + 1) begin
                buff_mem[i]  <= 16'd0;
            end
        end else if (!valid_data_latched && valid_data) begin
            buff_mem[hitIndex] <= data;
        end
    end
    
    // hitIndex update
    reg hit;
    always @(*) begin
        hit = 0;
        hitIndex = 0;
        for(i = 0; i < 8; i = i + 1) begin
            if(buff_mem[i] == data) begin
                hitIndex = i;
                hit = 1;
            end
        end
        if(!hit) begin
            for(i = 0; i < 8; i = i + 1) begin
                if(ages[i] == 7) hitIndex = i;
            end
        end 
    end

endmodule