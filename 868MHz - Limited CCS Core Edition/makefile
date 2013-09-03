################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.1.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./driver/ps.obj" \
"./driver/cma_ps.obj" \
"./driver/cma_as.obj" \
"./driver/bmp_ps.obj" \
"./driver/bmp_as.obj" \
"./driver/as.obj" \
"./logic/user.obj" \
"./logic/test.obj" \
"./logic/temperature.obj" \
"./logic/stopwatch.obj" \
"./logic/rfsimpliciti.obj" \
"./logic/rfbsl.obj" \
"./logic/menu.obj" \
"./logic/date.obj" \
"./logic/clock.obj" \
"./logic/bluerobin.obj" \
"./logic/battery.obj" \
"./logic/altitude.obj" \
"./logic/alarm.obj" \
"./logic/acceleration.obj" \
"./main.obj" \
-l"rts430x.lib" \
"../simpliciti/CC430_End_Device_868MHz.lib" \
"../bluerobin/BlueRobin_RX_868MHz.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include simpliciti/subdir_vars.mk
-include logic/subdir_vars.mk
-include driver/subdir_vars.mk
-include bluerobin/subdir_vars.mk
-include subdir_rules.mk
-include simpliciti/subdir_rules.mk
-include logic/subdir_rules.mk
-include driver/subdir_rules.mk
-include bluerobin/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ez430_chronos_868MHz.out

# Tool invocations
ez430_chronos_868MHz.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal -z --stack_size=160 -m"ez430_chronos_868MHz.map" --heap_size=160 --use_hw_mpy=F5 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" -i"C:/ti/ccsv5/msp430/include" --reread_libs --warn_sections --rom_model -o "ez430_chronos_868MHz.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "ez430_chronos_868MHz.out"
	-$(RM) "main.pp" "logic\acceleration.pp" "logic\alarm.pp" "logic\altitude.pp" "logic\battery.pp" "logic\bluerobin.pp" "logic\clock.pp" "logic\date.pp" "logic\menu.pp" "logic\rfbsl.pp" "logic\rfsimpliciti.pp" "logic\stopwatch.pp" "logic\temperature.pp" "logic\test.pp" "logic\user.pp" "driver\as.pp" "driver\bmp_as.pp" "driver\bmp_ps.pp" "driver\cma_as.pp" "driver\cma_ps.pp" "driver\ps.pp" 
	-$(RM) "main.obj" "logic\acceleration.obj" "logic\alarm.obj" "logic\altitude.obj" "logic\battery.obj" "logic\bluerobin.obj" "logic\clock.obj" "logic\date.obj" "logic\menu.obj" "logic\rfbsl.obj" "logic\rfsimpliciti.obj" "logic\stopwatch.obj" "logic\temperature.obj" "logic\test.obj" "logic\user.obj" "driver\as.obj" "driver\bmp_as.obj" "driver\bmp_ps.obj" "driver\cma_as.obj" "driver\cma_ps.obj" "driver\ps.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/hex430.exe" --ti_txt "ez430_chronos_868MHz.out" -o "ez430_chronos_868MHz.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
