#Directories
MSPGCC_ROOT_DIR = /home/farhan/ti/msp430-gcc
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUDE_DIRS = $(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)

#Toolchain
CC      = $(MSPGCC_BIN_DIR)/msp430-elf-gcc

#Files
TARGET  = blink

#Flags
MCU     = msp430g2553
WFLAGS  = -Wall -Wextra -Werror -Wshadow
CFLAGS  = -mmcu=$(MCU) $(WFLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -Og -g
LDFLAGS = -mmcu=$(MCU) $(addprefix -L,$(LIB_DIRS))


#Build
$(TARGET):main.o led.o
	$(CC) $(LDFLAGS) \
	$^ -o $@ 

#Compiling 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

