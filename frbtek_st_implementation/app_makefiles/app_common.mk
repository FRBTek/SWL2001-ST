##############################################################################
# Common rules and definitions
##############################################################################
-include app_makefiles/app_options.mk

#-----------------------------------------------------------------------------
# Build system binaries
#-----------------------------------------------------------------------------
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
AR  = $(GCC_PATH)/$(PREFIX)ar
CC  = $(GCC_PATH)/$(PREFIX)gcc
CPP = $(GCC_PATH)/$(PREFIX)g++
AS  = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP  = $(GCC_PATH)/$(PREFIX)objcopy
SZ  = $(GCC_PATH)/$(PREFIX)size
else
AR = $(PREFIX)ar
CC = $(PREFIX)gcc
CPP = $(PREFIX)g++
AS = $(PREFIX)g++ -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#-----------------------------------------------------------------------------
# Board selection
#-----------------------------------------------------------------------------

ifeq ($(BOARD),NUCLEO_U073)
-include app_makefiles/board_U073.mk
BOARD_TARGET=u0
endif

#-----------------------------------------------------------------------------
# Define target build directory
#-----------------------------------------------------------------------------
BUILD_TARGET = $(APPTARGET_ROOT)_$(TARGET)
BUILD_DIR = $(APPBUILD_ROOT)_$(TARGET)_$(BOARD_TARGET)

#-----------------------------------------------------------------------------
# Multithread is disabled if verbose build, for readable logs
#-----------------------------------------------------------------------------
ifeq ($(VERBOSE),yes)
MULTITHREAD = no
endif
ifeq ($(SIZE),yes)
MULTITHREAD = no
endif

ifeq ($(MULTITHREAD),no)
MTHREAD_FLAG =
else
MTHREAD_FLAG = -j
endif

include $(LORA_BASICS_MODEM)/makefiles/regions.mk

#-----------------------------------------------------------------------------
# Debug
#-----------------------------------------------------------------------------

# Application build optimization
ifeq ($(APP_DEBUG),yes)
OPT = $(DEBUG_APP_OPT) -g
MODEM_OPT = $(DEBUG_LBM_OPT) -g
else
OPT = $(APP_OPT)
MODEM_OPT = $(LBM_OPT)
endif

#-----------------------------------------------------------------------------
# Dump memory usage to a log file
#-----------------------------------------------------------------------------
ifeq ($(LOG_MEM), yes)
MEMLOG_FILE := $(BUILD_DIR)/mem_usage.log
MEMLOG = | tee $(MEMLOG_FILE)
else
MEMLOG =
endif


#-----------------------------------------------------------------------------
# Compilation flags
#-----------------------------------------------------------------------------

# Basic compilation flags
WFLAG += \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wpedantic \
	-fomit-frame-pointer \
	-fno-unroll-loops \
	-ffast-math \
	-ftree-vectorize

# Allow linker to not link unused functions
WFLAG += \
	-ffunction-sections \
	-fdata-sections

# Generate .su files for stack use analysis
WFLAG += -fstack-usage

#Link-time optimization
#WFLAG += --lto

# AS defines
AS_DEFS =

# Assembly flags
ASFLAGS += -fno-builtin $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) $(WFLAG)

# Common C definitions
COMMON_C_DEFS +=

ifeq ($(APP_TRACE),yes)
COMMON_C_DEFS += \
	-DHAL_DBG_TRACE=1
endif
ifeq ($(APP_TRACE),no)
COMMON_C_DEFS += \
	-DHAL_DBG_TRACE=0
endif

ifeq ($(PERF_TEST),yes)
COMMON_C_DEFS += \
	-DPERF_TEST_ENABLED
endif

ifeq ($(APP_DEBUG),yes)
COMMON_C_DEFS += \
	-DHW_DEBUG_PROBE=1
endif
CFLAGS += -fno-builtin $(MCU_FLAGS) $(BOARD_C_DEFS) $(COMMON_C_DEFS) $(MODEM_C_DEFS) $(OPT) $(WFLAG) -MMD -MP -MF"$(@:%.o=%.d)"
CFLAGS += -falign-functions=4
CFLAGS += -std=c17

#-----------------------------------------------------------------------------
# Common sources
#-----------------------------------------------------------------------------

RADIO_HAL_C_SOURCES += \
	radio_hal/radio_utilities.c

COMMON_C_INCLUDES +=  \
	-I.\
	-Iradio_hal\
	-Ismtc_modem_hal\
	-I$(LORA_BASICS_MODEM)/smtc_modem_api\
	-I$(LORA_BASICS_MODEM)/smtc_modem_hal

#-----------------------------------------------------------------------------
# Gather everything
#-----------------------------------------------------------------------------

C_INCLUDES += $(BOARD_C_INCLUDES) $(COMMON_C_INCLUDES) $(MODEM_C_INCLUDES)

C_SOURCES = \
	$(APP_C_SOURCES) \
	$(BOARD_C_SOURCES) \
	$(RADIO_DRIVER_C_SOURCES) \
	$(RADIO_HAL_C_SOURCES)

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

#-----------------------------------------------------------------------------

app_build: $(BUILD_DIR)/$(BUILD_TARGET).a
	$(call success,$@)

#-----------------------------------------------------------------------------
# list of C objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(call build,'CC',$<)
	$(SILENT)$(CC) -c $(CFLAGS) $(C_INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
ifeq ($(SIZE),yes)
	$(SZ) $@
endif

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(call build,'AS',$<)
	$(SILENT)$(AS) -c $(ASFLAGS) $< -o $@
ifeq ($(SIZE),yes)
	$(SZ) $@
endif


$(BUILD_DIR)/$(BUILD_TARGET).a: $(OBJECTS) Makefile $(BASIC_MODEM_LIB)
	$(call build,'LIB',$@)
	$(SILENT)$(AR) rcs $@ $(OBJECTS)
	$(SZ) -t $@

$(BUILD_DIR):
	$(SILENT)mkdir $@

#-----------------------------------------------------------------------------
# Clean
#-----------------------------------------------------------------------------
clean_target:
	-rm -fR $(BUILD_DIR)*
