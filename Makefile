#Directories
MSP_ROOT_DIRECTORY    =  /home/farhan/ti/msp430-gcc
MSP_INCLUDE_DIRECTORY =  $(MSP_ROOT_DIRECTORY)/include
MSP_LINK_DIRECTORY    =  $(MSP_INCLUDE_DIRECTORY)
MSP_BIN_DIRECTORY     =  $(MSP_ROOT_DIRECTORY)/bin
BUILD_DIR             =  build
OBJ_DIR               = $(BUILD_DIR)/obj
BIN_DIR               = $(BUILD_DIR)/bin

#Toolchain
CC   =  $(MSP_BIN_DIRECTORY)/msp430-elf-gcc

#Files
TARGET = $(BIN_DIR)/blink
SOURCE = main.c led.c
OBJECT = $(OBJ_DIR)/main.o \
         $(OBJ_DIR)/led.o

#Flags
MCU     =  msp430g2553
WFLAGS  = -Wall -Wextra -Werror -Wshadow
CFLAGS  = -mmcu=$(MCU) $(WFLAGS) $(addprefix -I,$(MSP_INCLUDE_DIRECTORY)) -Og -g
LFLAGS  = -mmcu=$(MCU) $(addprefix -L, $(MSP_LINK_DIRECTORY))


#Build
$(TARGET):$(OBJECT)
	@mkdir -p $(dir $@)
	$(CC) $(LFLAGS) $^ -o $@


#Compile
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) \
	$(CFLAGS) \
	-c $^ -o $@ 
	
#Phonies
.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) -r $(BUILD_DIR)

