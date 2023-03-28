ROOT = solution
SRC_DIR = src
INCL_DIR = include
TARGET_DIR = out
SOURCES := $(shell find $(SRC_DIR) -name '*.c')
INCLUDES := $(shell find $(INCL_DIR) -name '*.h')

ASM = nasm
ASMFLAGS = -felf64
CCOMP = gcc

$(TARGET_DIR)/sepia: $(TARGET_DIR)/sepia_asm.o $(INCLUDES) $(SOURCES)
	$(CCOMP) -I $(INCL_DIR) -O2 -o $@  $(SOURCES) $<

$(TARGET_DIR)/sepia_asm.o: $(SRC_DIR)/sepia_asm.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -r out