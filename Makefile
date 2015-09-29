PROJECT_NAME = jjj

BUILDDIR = build

CMSIS = ./lib/CMSIS
DEVICE = ./lib/StdPeriph
BOARD = ./lib/Board
FATFS = ./lib/fatfs
USB = ./lib/usb
TM = ./lib/TM
FREERTOS = ./lib/FreeRTOS
EMWIN = ./lib/emWin
SRC = ./src
CONFIG = $(SRC)/config
TASKS = $(SRC)/tasks
DRIVERS = $(SRC)/drivers
BITMAPS = $(SRC)/bitmaps

SOURCES += $(wildcard $(CMSIS)/*.c)
SOURCES += $(CMSIS)/startup_stm32f4xx.S
SOURCES += $(wildcard $(DEVICE)/src/*.c)
SOURCES += $(wildcard $(BOARD)/*.c)
SOURCES += $(filter-out $(FATFS)/ccsbcs.c, $(wildcard $(FATFS)/*.c))
SOURCES += $(wildcard $(TM)/*.c)
SOURCES += $(wildcard $(FREERTOS)/*.c)
SOURCES += $(wildcard $(USB)/*.c)
SOURCES += $(wildcard $(EMWIN)/src/*.c)
SOURCES += $(wildcard $(SRC)/*.c)
SOURCES += $(wildcard $(CONFIG)/*.c)
SOURCES += $(wildcard $(TASKS)/*.c)
SOURCES += $(wildcard $(DRIVERS)/*.c)
SOURCES += $(wildcard $(BITMAPS)/*.c)

#SOURCES += stm32f4xx_it.c
#SOURCES += system_stm32f4xx.c

#SOURCES += \
		#src/main.c

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES = $(CMSIS) $(DEVICE)/inc $(FATFS) \
		   $(SRC) $(TM) $(FREERTOS)/inc $(BOARD) \
		   $(EMWIN)/inc  $(USB) $(CONFIG) $(TASKS) $(DRIVERS)
INCLUDESPARAM = $(foreach d, $(INCLUDES), -I$d)
#INCLUDES += -IProgram -I. -ILibraries/CMSIS -ILibraries/STM32F4xx_StdPeriph_Driver/inc
#INCLUDES += 

ELF = $(BUILDDIR)/$(PROJECT_NAME).elf
HEX = $(BUILDDIR)/$(PROJECT_NAME).hex
BIN = $(BUILDDIR)/$(PROJECT_NAME).bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb

LDLIBS = ./lib/emWin/src/STemWin522_CM4_OS_GCC.a
#LDLIBS = ./lib/emWin/src/STemWin522_CM4_GCC.a

DEFINES = USE_STDPERIPH_DRIVER STM32F40XX STM32F40_41xxx ARM_MATH_CM4 USE_FULL_ASSERT
DEFINESPARAM = $(foreach d, $(DEFINES), -D$d)

CFLAGS  = -O0 -g -Wall -I. \
   -mcpu=cortex-m4 -mthumb \
   -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
   $(INCLUDESPARAM) $(DEFINESPARAM)

LDSCRIPT = stm32_flash.ld
#LDSCRIPT = ./STM32_FLASH.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard #-nostdlib

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

debug: $(ELF)
	$(GDB) -tui $(ELF)

up: all flash

all: $(HEX) $(BIN)

.PHONY: clean
clean:
	rm -rf build
