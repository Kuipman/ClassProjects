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
FINAL_IMAGE=${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../src/AD.c ../../../src/BOARD.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c ../../../src/Service.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/timers.c ES_Main.c ../../../src/BumperService.c ../../../src/EventChecker.c ../../../src/LightService.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/_ext/1386528437/Service.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/timers.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/_ext/1386528437/BumperService.o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ${OBJECTDIR}/_ext/1386528437/LightService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386528437/AD.o.d ${OBJECTDIR}/_ext/1386528437/BOARD.o.d ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d ${OBJECTDIR}/_ext/1386528437/Service.o.d ${OBJECTDIR}/_ext/1386528437/pwm.o.d ${OBJECTDIR}/_ext/1386528437/roach.o.d ${OBJECTDIR}/_ext/1386528437/serial.o.d ${OBJECTDIR}/_ext/1386528437/timers.o.d ${OBJECTDIR}/ES_Main.o.d ${OBJECTDIR}/_ext/1386528437/BumperService.o.d ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d ${OBJECTDIR}/_ext/1386528437/LightService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/_ext/1386528437/Service.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/timers.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/_ext/1386528437/BumperService.o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ${OBJECTDIR}/_ext/1386528437/LightService.o

# Source Files
SOURCEFILES=../../../src/AD.c ../../../src/BOARD.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c ../../../src/Service.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/timers.c ES_Main.c ../../../src/BumperService.c ../../../src/EventChecker.c ../../../src/LightService.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\..\..\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/b0e30e922d83412e39d5237fe964f9041076dc9 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/fabbef9b1b3dec3f7bcd7f15a30d927bdeeab374 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/c70bd3e748808f9360cb1bbd63dd94bc54b62059 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/5ef24fce50f660cdec201c87177b659bcdfca116 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/c62373b14cbc081ec99ee56d8214bb6b7d0cf3c1 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/f06a1ff7d55fe71bb72186a81dc3c10fe614c014 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/710a87a6b50f506382ff1b7ee6f94196d5d026be .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/94499a46f695ad31fb467221ff987e1f98132c5c .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/4fc8e239f695f0fa954ae67e430b314cc7d472d .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/Service.o: ../../../src/Service.c  .generated_files/flags/default/315f15f2a602707eaaea3b8bf1a925bc6d383f54 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/Service.o.d" -o ${OBJECTDIR}/_ext/1386528437/Service.o ../../../src/Service.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/aec15489fbb3e6f093b31cb75e3ef8d5f83b7bb7 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/5642234658e03d825832de0f9e2a3eb30262ebe0 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/7338d3dcc7a89cd4678e4f150299838f26448cba .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/timers.o: ../../../src/timers.c  .generated_files/flags/default/f66eaef43a4d8b03ccad73b8051c2bbbb83fa504 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/timers.o ../../../src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/2e0a78232da02e3ab07baf3b5747ffd4b10112a4 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BumperService.o: ../../../src/BumperService.c  .generated_files/flags/default/a33e95ed4d46160fedeffbabec79e3a60a19a3ff .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BumperService.o.d" -o ${OBJECTDIR}/_ext/1386528437/BumperService.o ../../../src/BumperService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/EventChecker.o: ../../../src/EventChecker.c  .generated_files/flags/default/75e2d089f57b6d6469a223a345135b0df44ecc6b .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ../../../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LightService.o: ../../../src/LightService.c  .generated_files/flags/default/9f6054a42d94fd9a6d32054cf99e488593f025af .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LightService.o.d" -o ${OBJECTDIR}/_ext/1386528437/LightService.o ../../../src/LightService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/c75a6cd1c1744b535cd71f9da7307e833adc67a2 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/f2d40b1034d05457dbcbf653893c980a62daae2c .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/21ec24abd7b7e39730a42f343db2a97747dbd1b3 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/414d5f1f9e0aeb5b3740bd3914d47b1c38c34ccb .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/699bf81e154aa454b38ca1c5ba04504f350d5dbc .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/d49e03497f08e3b8c57dabcf57146603f3322be7 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/d6804d2ec2ac251a41ae42319edc2c1d2f74e9a0 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/aaed6260bbb96b0f54630ee88b149a749f7bc1d8 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/8d1e5ac7aa174f392007fc6aff350faea8b86a6e .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/Service.o: ../../../src/Service.c  .generated_files/flags/default/7d9d79f9d8d71506798a42320fbb1f12e9b38362 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/Service.o.d" -o ${OBJECTDIR}/_ext/1386528437/Service.o ../../../src/Service.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/5dc2ff6ab68eddfe870fd11c066a9daf5cdebc0f .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/2ebb4c2d46ff8bd446a31ae67504bf7dd9c2f95f .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/820f400ee9bc7403ea5ce6d0a6967e4414588ab6 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/timers.o: ../../../src/timers.c  .generated_files/flags/default/73da8c5326434c697a5a25703e1bf5a305b9453e .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/timers.o ../../../src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/88d54a25bf12d56d865851bfc7d80291700cfaf3 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BumperService.o: ../../../src/BumperService.c  .generated_files/flags/default/24c81acc357712b21d0853e102506945e432322e .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BumperService.o.d" -o ${OBJECTDIR}/_ext/1386528437/BumperService.o ../../../src/BumperService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/EventChecker.o: ../../../src/EventChecker.c  .generated_files/flags/default/8495f70c1d3941cf68e22f81f3b2328327409de6 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ../../../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LightService.o: ../../../src/LightService.c  .generated_files/flags/default/e4e0e4110580bdae474cfa3dcef1b2444eaa63a8 .generated_files/flags/default/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LightService.o.d" -o ${OBJECTDIR}/_ext/1386528437/LightService.o ../../../src/LightService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Lab0_Part5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
