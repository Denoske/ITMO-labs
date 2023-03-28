mkdir out
make
./out/sepia tests/input.bmp tests/output_c.bmp tests/output_asm.bmp>>../README.md
make clean