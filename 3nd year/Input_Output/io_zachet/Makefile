SYSTEMC_HOME    = /Users/bsv/Documents/soft/lib/systemc-2.3.3
TARGET_ARCH     = macosxarm

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

FLAGS           =-g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR) -std=c++11
LDFLAGS         = -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = src/cpu.cpp src/spi_master.cpp src/display.cpp src/main.cpp
OBJS = $(SRCS:.cpp=.o)
	
main: 
	g++ -o model $(LDFLAGS) $(FLAGS) $(SRCS)

