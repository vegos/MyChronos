################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
driver/as.obj: ../driver/as.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/as.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver/bmp_as.obj: ../driver/bmp_as.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/bmp_as.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver/bmp_ps.obj: ../driver/bmp_ps.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/bmp_ps.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver/cma_as.obj: ../driver/cma_as.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/cma_as.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver/cma_ps.obj: ../driver/cma_ps.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/cma_ps.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver/ps.obj: ../driver/ps.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=eabi -O4 --opt_for_speed=0 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/include" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/driver" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/logic" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/bluerobin" --include_path="C:/Users/antonis/workspace_v5_4/ez430_chronos/simpliciti" --define=__CCE__ --define=ISM_EU --define=__MSP430F5509__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/ps.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


