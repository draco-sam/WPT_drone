#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib_wpt_rx/lib_wpt_rx_00.c main_wpt_rx_00.c lib_wpt_rx/lib_com/serial_com_01.c lib_wpt_rx/clock.c lib_wpt_rx/interrupt_manager.c lib_wpt_rx/pin_manager.c lib_wpt_rx/system.c lib_wpt_rx/traps.c lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c lib_wpt_rx/lib_com/usb/usb_descriptors.c lib_wpt_rx/lib_com/usb/usb_device.c lib_wpt_rx/lib_com/usb/usb_device_cdc.c lib_wpt_rx/lib_com/usb/usb_device_events.c lib_wpt_rx/lib_com/usb/usb_hal_16bit.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o ${OBJECTDIR}/main_wpt_rx_00.o ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o ${OBJECTDIR}/lib_wpt_rx/clock.o ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o ${OBJECTDIR}/lib_wpt_rx/pin_manager.o ${OBJECTDIR}/lib_wpt_rx/system.o ${OBJECTDIR}/lib_wpt_rx/traps.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d ${OBJECTDIR}/main_wpt_rx_00.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d ${OBJECTDIR}/lib_wpt_rx/clock.o.d ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d ${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d ${OBJECTDIR}/lib_wpt_rx/system.o.d ${OBJECTDIR}/lib_wpt_rx/traps.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o ${OBJECTDIR}/main_wpt_rx_00.o ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o ${OBJECTDIR}/lib_wpt_rx/clock.o ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o ${OBJECTDIR}/lib_wpt_rx/pin_manager.o ${OBJECTDIR}/lib_wpt_rx/system.o ${OBJECTDIR}/lib_wpt_rx/traps.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o

# Source Files
SOURCEFILES=lib_wpt_rx/lib_wpt_rx_00.c main_wpt_rx_00.c lib_wpt_rx/lib_com/serial_com_01.c lib_wpt_rx/clock.c lib_wpt_rx/interrupt_manager.c lib_wpt_rx/pin_manager.c lib_wpt_rx/system.c lib_wpt_rx/traps.c lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c lib_wpt_rx/lib_com/usb/usb_descriptors.c lib_wpt_rx/lib_com/usb/usb_device.c lib_wpt_rx/lib_com/usb/usb_device_cdc.c lib_wpt_rx/lib_com/usb/usb_device_events.c lib_wpt_rx/lib_com/usb/usb_hal_16bit.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GC006
MP_LINKER_FILE_OPTION=,--script=p24FJ128GC006.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o: lib_wpt_rx/lib_wpt_rx_00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_wpt_rx_00.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_wpt_rx_00.o: main_wpt_rx_00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_wpt_rx_00.o.d 
	@${RM} ${OBJECTDIR}/main_wpt_rx_00.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_wpt_rx_00.c  -o ${OBJECTDIR}/main_wpt_rx_00.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_wpt_rx_00.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/main_wpt_rx_00.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o: lib_wpt_rx/lib_com/serial_com_01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/serial_com_01.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/clock.o: lib_wpt_rx/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/clock.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/clock.c  -o ${OBJECTDIR}/lib_wpt_rx/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o: lib_wpt_rx/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/interrupt_manager.c  -o ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/pin_manager.o: lib_wpt_rx/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/pin_manager.c  -o ${OBJECTDIR}/lib_wpt_rx/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/system.o: lib_wpt_rx/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/system.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/system.c  -o ${OBJECTDIR}/lib_wpt_rx/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/traps.o: lib_wpt_rx/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/traps.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/traps.c  -o ${OBJECTDIR}/lib_wpt_rx/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o: lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o: lib_wpt_rx/lib_com/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_descriptors.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o: lib_wpt_rx/lib_com/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o: lib_wpt_rx/lib_com/usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device_cdc.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o: lib_wpt_rx/lib_com/usb/usb_device_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device_events.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o: lib_wpt_rx/lib_com/usb/usb_hal_16bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o: lib_wpt_rx/lib_wpt_rx_00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_wpt_rx_00.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_wpt_rx_00.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_wpt_rx_00.o: main_wpt_rx_00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_wpt_rx_00.o.d 
	@${RM} ${OBJECTDIR}/main_wpt_rx_00.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_wpt_rx_00.c  -o ${OBJECTDIR}/main_wpt_rx_00.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_wpt_rx_00.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/main_wpt_rx_00.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o: lib_wpt_rx/lib_com/serial_com_01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/serial_com_01.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/serial_com_01.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/clock.o: lib_wpt_rx/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/clock.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/clock.c  -o ${OBJECTDIR}/lib_wpt_rx/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o: lib_wpt_rx/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/interrupt_manager.c  -o ${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/pin_manager.o: lib_wpt_rx/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/pin_manager.c  -o ${OBJECTDIR}/lib_wpt_rx/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/system.o: lib_wpt_rx/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/system.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/system.c  -o ${OBJECTDIR}/lib_wpt_rx/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/traps.o: lib_wpt_rx/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/traps.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/traps.c  -o ${OBJECTDIR}/lib_wpt_rx/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o: lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/example_mcc_usb_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o: lib_wpt_rx/lib_com/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_descriptors.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o: lib_wpt_rx/lib_com/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o: lib_wpt_rx/lib_com/usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device_cdc.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o: lib_wpt_rx/lib_com/usb/usb_device_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_device_events.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_device_events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o: lib_wpt_rx/lib_com/usb/usb_hal_16bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb" 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_wpt_rx/lib_com/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/lib_wpt_rx/lib_com/usb/usb_hal_16bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/WPT_RX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp=${DFP_DIR}/xc16 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
