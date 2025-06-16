# Directories
ROOT_DIR   := $(CURDIR)
SRC_DIR    := $(ROOT_DIR)/src
APP_DIR    := $(SRC_DIR)/app
DRIVERS_DIR:= $(SRC_DIR)/drivers
COMMON_DIR := $(SRC_DIR)/common
BUILD_DIR  := $(ROOT_DIR)/build
OBJ_DIR    := $(BUILD_DIR)/obj
BIN_DIR    := $(BUILD_DIR)/bin

# MSP430 Toolchain Paths
TOOLS_DIR = ${TOOLS_PATH}
MSP_ROOT_DIRECTORY    := $(TOOLS_DIR)
MSP_BIN_DIRECTORY     := $(MSP_ROOT_DIRECTORY)/bin
MSP_INCLUDE_DIRECTORY := $(MSP_ROOT_DIRECTORY)/include
MSP_LINK_DIRECTORY    := $(MSP_INCLUDE_DIRECTORY)

# Toolchain
CC       := $(MSP_BIN_DIRECTORY)/msp430-elf-gcc
RM       := rm -rf
CPPCHECK := cppcheck

# MCU and Flags
MCU    := msp430g2553
WFLAGS := -Wall -Wextra -Werror -Wshadow
INCLUDE_DIRS := $(MSP_INCLUDE_DIRECTORY) $(COMMON_DIR) $(APP_DIR) $(DRIVERS_DIR)
CFLAGS := -mmcu=$(MCU) $(WFLAGS) -Og -g $(addprefix -I,$(INCLUDE_DIRS))
LFLAGS := -mmcu=$(MCU) $(addprefix -L,$(MSP_LINK_DIRECTORY))

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) \
             $(wildcard $(APP_DIR)/*.c) \
             $(wildcard $(DRIVERS_DIR)/*.c)

# Object files (mirroring src folder structure inside build/obj)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Target binary
TARGET := $(BIN_DIR)/project.elf

# Build target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(LFLAGS) $^ -o $@

# Compile rules for src root files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rules for app subfolder files
$(OBJ_DIR)/app/%.o: $(APP_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rules for drivers subfolder files
$(OBJ_DIR)/drivers/%.o: $(DRIVERS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	$(RM) $(BUILD_DIR)

# Static analysis
cppcheck:
	@$(CPPCHECK) --quiet --enable=all --inline-suppr \
	$(addprefix -I, $(INCLUDE_DIRS)) \
	$(SRC_FILES) || true


# Phony targets
.PHONY: all clean cppcheck

# Default target
all: $(TARGET)

