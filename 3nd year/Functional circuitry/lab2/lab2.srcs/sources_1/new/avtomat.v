`timescale 1ns / 1ps

module avtomat(
    input [9:0] value1,
    input [9:0] value2,
    output [10:0] result
    );
    wire [10:0] skobki,proizved;

summator summa1(
    .a(value1),
    .b(value2),
    .c(skobki)
);

umnozhitel umnozh(
    .AB(skobki),
    .out(proizved)
);

summator summa2(
    .a(proizved),
    .b(value2),
    .c(result)
);

endmodule
