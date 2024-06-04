`timescale 1ns / 1ps
module simple_counter(
    clk, // �������� ������
    reset, // ������ ������
    ud, //������ ���������� up_down
    load, // ������ �������� �������� ��������
    data, 
    count, //��� ���� ���� ����� �������� ��� ���� ������� - ������ �������� � ����
    rst // ����������� �����
);
  input clk,reset,load,ud,rst;
  input [7:0] data;
  output reg [7:0] count;
  //������ ���� ����� ����������� �� ������ ������������� ������ �������� �������
  always@(negedge clk or posedge rst)  ///��� Count zero ���������� �� negedge! ��� ��������� �� posedge
  begin
    if(rst)
        count = 0;   ///
    else if(reset)    //���������� ������� �� ����
      count = 0;
    else if(load)    //��������� � ������� �������� ������
      count = data;
    else if(ud)        //���������
      count = count + 1;
    else            //��������� ����� ��� 
      count = count; 
  end
endmodule












