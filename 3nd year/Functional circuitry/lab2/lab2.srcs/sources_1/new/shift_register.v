`timescale 1ns / 1ps

module shift_register (
    input clk,                              // �������� ������
    input reset,                            // ������ ������
    input enable,                           // ������ ����������
    input rst,                              // ����������� �����
    input load,                             // ������ �������� ������ � �������
    input [7:0] data,                       // ������������ ����
    output reg out,                         //  ����� ������� ������
    output reg [7:0] register
);

always @(posedge rst) begin
    if (rst) begin
        out <= 0;
        register <= 8'b0;
    end
end
//always @(posedge load) begin              // ���� ���������� ���� load, �� ��������� ������ �� ���� � �������
//    register = data;
//end
//reg [7:0] register;                       // ���������� ��������
always @(posedge clk) begin                 //������ � ��������� � ��������
    if (load) begin                         // ���� ���������� ���� load, �� ��������� ������ �� ���� � �������
        register = data; 
    end else begin
        if (reset) begin
            register <= 8'b0;               // ����� ��������
        end else begin
        if (enable) begin
            register [7] <= 0;              // ���������� �������� ������ �������� 0
            out <= register[0];             // ���������� ������� ������
            register <= {register[7:1]};    // ����� ������
            end
        end
    end
end


endmodule

