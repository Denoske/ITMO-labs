`timescale 1ns / 1ps

module shift_register_v0(clock,ds,a,b,c,d,e,f,g,h);
input clock, ds;
output reg a,b,c,d,e,f,g,h;

always @(posedge clock)
    begin
        a<=ds;
        b<=a;
        c<=b;
        d<=c;
        e<=d;
        f<=e;
        g<=f;
        h<=g;
    end
endmodule
