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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../src/AD.c ../../../src/BOARD.c ../../../src/BumperService.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_Main.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c ../../../src/EventChecker.c ../../../src/LightService.c ../../../src/Service.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/timers.c ../../../src/ES_HSM.c ../../../src/ES_SubHSM.c ../../../src/IO_Ports.c Midterm_Part5_PingService.c Midterm_Part5_EventChecker.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/BumperService.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_Main.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ${OBJECTDIR}/_ext/1386528437/LightService.o ${OBJECTDIR}/_ext/1386528437/Service.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/timers.o ${OBJECTDIR}/_ext/1386528437/ES_HSM.o ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ${OBJECTDIR}/Midterm_Part5_PingService.o ${OBJECTDIR}/Midterm_Part5_EventChecker.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386528437/AD.o.d ${OBJECTDIR}/_ext/1386528437/BOARD.o.d ${OBJECTDIR}/_ext/1386528437/BumperService.o.d ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1386528437/ES_Main.o.d ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d ${OBJECTDIR}/_ext/1386528437/LightService.o.d ${OBJECTDIR}/_ext/1386528437/Service.o.d ${OBJECTDIR}/_ext/1386528437/pwm.o.d ${OBJECTDIR}/_ext/1386528437/roach.o.d ${OBJECTDIR}/_ext/1386528437/serial.o.d ${OBJECTDIR}/_ext/1386528437/timers.o.d ${OBJECTDIR}/_ext/1386528437/ES_HSM.o.d ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o.d ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d ${OBJECTDIR}/Midterm_Part5_PingService.o.d ${OBJECTDIR}/Midterm_Part5_EventChecker.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/BumperService.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_Main.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ${OBJECTDIR}/_ext/1386528437/LightService.o ${OBJECTDIR}/_ext/1386528437/Service.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/timers.o ${OBJECTDIR}/_ext/1386528437/ES_HSM.o ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ${OBJECTDIR}/Midterm_Part5_PingService.o ${OBJECTDIR}/Midterm_Part5_EventChecker.o

# Source Files
SOURCEFILES=../../../src/AD.c ../../../src/BOARD.c ../../../src/BumperService.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_Main.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c ../../../src/EventChecker.c ../../../src/LightService.c ../../../src/Service.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/timers.c ../../../src/ES_HSM.c ../../../src/ES_SubHSM.c ../../../src/IO_Ports.c Midterm_Part5_PingService.c Midterm_Part5_EventChecker.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/f91910763203b9385a5295de7aa55959d05b108 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/22ffb6aa7f5fc743802fc90eb0bc434e87d367be .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BumperService.o: ../../../src/BumperService.c  .generated_files/flags/default/40cfcab44f5e88d2f1ae64b1f08193b2f8665706 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BumperService.o.d" -o ${OBJECTDIR}/_ext/1386528437/BumperService.o ../../../src/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/143c4ecc55250bbdceeb86c060d6235c2f1d75e9 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/7e8a45ed375c141dab20c1eb71a86e3527465542 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/7e2d6ec4c60a3e5157d5a636cf9e05d8ba545b19 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Main.o: ../../../src/ES_Main.c  .generated_files/flags/default/d48b70b0e5dd69b987bd01a083353c227e951f26 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Main.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Main.o ../../../src/ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/9bfbaba9792246c8f2998fdb9b523ac95a57b898 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/182274412aecf315ad43fbf16a3039ee306058e1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/484b2718181df158725012cd65785f9aa3f87f3c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/e0110b1d96d66954f0b13744523f7915435f262b .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/EventChecker.o: ../../../src/EventChecker.c  .generated_files/flags/default/e6eeda23368c6d5c338cd1896216ee80e6570a7d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ../../../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LightService.o: ../../../src/LightService.c  .generated_files/flags/default/272134a943a09f79655d43e15e7a9f75bde4cf2 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LightService.o.d" -o ${OBJECTDIR}/_ext/1386528437/LightService.o ../../../src/LightService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/Service.o: ../../../src/Service.c  .generated_files/flags/default/d35d7b031416c9fc4ce4f4355a35fb56be855ba4 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/Service.o.d" -o ${OBJECTDIR}/_ext/1386528437/Service.o ../../../src/Service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/e6455a47ca5e26e89b0a4584bc4e727fb780dcc5 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/e3235837e0c272a0b69380ac6a44384df01ab9bc .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/3c0096c664d1aad02f5cd467541965c582668401 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/timers.o: ../../../src/timers.c  .generated_files/flags/default/7b1d5f7dccb18dbf600927e3a0c57586e9f2bfd4 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/timers.o ../../../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_HSM.o: ../../../src/ES_HSM.c  .generated_files/flags/default/3eeaf9cac01cf9fe9837e6bf353a0409d2f43671 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_HSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_HSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_HSM.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_HSM.o ../../../src/ES_HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o: ../../../src/ES_SubHSM.c  .generated_files/flags/default/77c966ba6cf7788433adf4f1c016be29ce61ef53 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o ../../../src/ES_SubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/IO_Ports.o: ../../../src/IO_Ports.c  .generated_files/flags/default/48f11639e724557b5ece3f7233640cca7977c6dd .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ../../../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_PingService.o: Midterm_Part5_PingService.c  .generated_files/flags/default/28f60985282c7ee1bf798cf3190a0a71f653e021 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_PingService.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_PingService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_PingService.o.d" -o ${OBJECTDIR}/Midterm_Part5_PingService.o Midterm_Part5_PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_EventChecker.o: Midterm_Part5_EventChecker.c  .generated_files/flags/default/56cdd424e7cedddcfe8c860f4d7216726554d79 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_EventChecker.o.d" -o ${OBJECTDIR}/Midterm_Part5_EventChecker.o Midterm_Part5_EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/ccb50e2e9b4a475fee11704adf82272905e2bf5c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/58193bca10272f056760c2e8f5b220588b1de9e2 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BumperService.o: ../../../src/BumperService.c  .generated_files/flags/default/3e15366dc1857cb52cbd4c7d7eefba27cbe11444 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BumperService.o.d" -o ${OBJECTDIR}/_ext/1386528437/BumperService.o ../../../src/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/39100fabe985d7e3064d05b78232f20411bd79af .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/31d1846add81bd46d411d67fbe5a0d38786034ad .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/fede5f7cc41218b6b2c12ef96aa47e947a561765 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Main.o: ../../../src/ES_Main.c  .generated_files/flags/default/871ced7241b119f303a4248bed4ba80785bc4c65 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Main.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Main.o ../../../src/ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/15e6f444519d1d34dd28a6f459f809a698cd5ef8 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/2b63a9dab237d6b4ab5a8ab91dbb52266325d48b .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/af36e03e8e176ee8d175ecfbb68751e4b060ec54 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/9219b5451866f6f86fc0a2402db0467544507872 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/EventChecker.o: ../../../src/EventChecker.c  .generated_files/flags/default/81beb66947bb585a96ed820a4674eda28c7344be .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1386528437/EventChecker.o ../../../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LightService.o: ../../../src/LightService.c  .generated_files/flags/default/fb3bbab7fb99a9e40ed60f52aa27a43131a0c6c8 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LightService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LightService.o.d" -o ${OBJECTDIR}/_ext/1386528437/LightService.o ../../../src/LightService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/Service.o: ../../../src/Service.c  .generated_files/flags/default/6543dd7e72fb6a9116a1cde3e2c607f5c7d610c1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/Service.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/Service.o.d" -o ${OBJECTDIR}/_ext/1386528437/Service.o ../../../src/Service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/c9d763aea101d3b69bdad1cf55ce35f2726d3819 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/81eea02f4100852b3aad7eeb145932ca6d2bfc97 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/4b4bcc75fe7e15d0a6dd783b3ae264f8ad4d119c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/timers.o: ../../../src/timers.c  .generated_files/flags/default/3c9dd649154b84aee8fa04ec36fa4bd18e0ba1e1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/timers.o ../../../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_HSM.o: ../../../src/ES_HSM.c  .generated_files/flags/default/8a71649b48e502b77b35e426d5669f404617ac65 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_HSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_HSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_HSM.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_HSM.o ../../../src/ES_HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o: ../../../src/ES_SubHSM.c  .generated_files/flags/default/81ab2a92c68546f608cc2b2253c1ff474e296b7c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_SubHSM.o ../../../src/ES_SubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/IO_Ports.o: ../../../src/IO_Ports.c  .generated_files/flags/default/15849afbd8198141f7b0a2161dde33b21846f27 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ../../../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_PingService.o: Midterm_Part5_PingService.c  .generated_files/flags/default/9dd1e08593cfb76f4f718ba89281ce636e21e68 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_PingService.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_PingService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_PingService.o.d" -o ${OBJECTDIR}/Midterm_Part5_PingService.o Midterm_Part5_PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_EventChecker.o: Midterm_Part5_EventChecker.c  .generated_files/flags/default/ec3c7fa5846d632dc493a9f238bf78fe930997b0 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_EventChecker.o.d" -o ${OBJECTDIR}/Midterm_Part5_EventChecker.o Midterm_Part5_EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_HierarchicalSM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
