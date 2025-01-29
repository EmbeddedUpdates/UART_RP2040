#Component specific makefile for RESET peripheral for the RP2040 platform
# COMPILER_DEFINES += -D

#C files that should be compiled in this component
C_SOURCE_FILES += Components/UART_RP2040/Source/UART_RP2040.c

#Compiled Assembly that should be included in this component link
#S_ASSEMBLY_FILES += $(COMPONENT_DIR)/Assembly/startup_cm0plus.s

#include path for header files in this component
INCLUDE_PATH += $(ROOT_DIR)/Components/UART_RP2040/Include

# #include for the SDK - which is a dependency for this component
# ifneq ($(RP2040_SDK_USED), 1)
#     INCLUDE_PATH += $(RP2040_SDK)/
# endif

