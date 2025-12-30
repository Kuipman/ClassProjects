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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/TapeAndTrackService.c ../src/BumperService.c ../src/BeaconService.c ../src/UARTService.c ../src/ES_CheckEvents.c ../src/ES_Framework.c ../src/ES_KeyboardInput.c ../src/ES_Main.c ../src/ES_PostList.c ../src/ES_Queue.c ../src/ES_TattleTale.c ../src/ES_Timers.c ../src/AD.c ../src/BOARD.c ../src/IO_Ports.c ../src/LED.c ../src/pwm.c ../src/RC_Servo.c ../src/serial.c ../src/Stepper.c ../src/timers.c ../src/BOAT_Movement.c ../src/BOAT.c ../src/BOAT_Sensors.c ../src/Protocol2.c ../src/BOAT_HSM.c ../src/EventChecker.c ../src/BOAT_SubHSM_MoveToPosition.c ../src/BOAT_SubHSM_Returning.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o ${OBJECTDIR}/_ext/1360937237/BumperService.o ${OBJECTDIR}/_ext/1360937237/BeaconService.o ${OBJECTDIR}/_ext/1360937237/UARTService.o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1360937237/ES_Main.o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ${OBJECTDIR}/_ext/1360937237/AD.o ${OBJECTDIR}/_ext/1360937237/BOARD.o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ${OBJECTDIR}/_ext/1360937237/LED.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/RC_Servo.o ${OBJECTDIR}/_ext/1360937237/serial.o ${OBJECTDIR}/_ext/1360937237/Stepper.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o ${OBJECTDIR}/_ext/1360937237/BOAT.o ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o ${OBJECTDIR}/_ext/1360937237/Protocol2.o ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o ${OBJECTDIR}/_ext/1360937237/EventChecker.o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o.d ${OBJECTDIR}/_ext/1360937237/BumperService.o.d ${OBJECTDIR}/_ext/1360937237/BeaconService.o.d ${OBJECTDIR}/_ext/1360937237/UARTService.o.d ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1360937237/ES_Main.o.d ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d ${OBJECTDIR}/_ext/1360937237/AD.o.d ${OBJECTDIR}/_ext/1360937237/BOARD.o.d ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d ${OBJECTDIR}/_ext/1360937237/LED.o.d ${OBJECTDIR}/_ext/1360937237/pwm.o.d ${OBJECTDIR}/_ext/1360937237/RC_Servo.o.d ${OBJECTDIR}/_ext/1360937237/serial.o.d ${OBJECTDIR}/_ext/1360937237/Stepper.o.d ${OBJECTDIR}/_ext/1360937237/timers.o.d ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o.d ${OBJECTDIR}/_ext/1360937237/BOAT.o.d ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o.d ${OBJECTDIR}/_ext/1360937237/Protocol2.o.d ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o.d ${OBJECTDIR}/_ext/1360937237/EventChecker.o.d ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o.d ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o ${OBJECTDIR}/_ext/1360937237/BumperService.o ${OBJECTDIR}/_ext/1360937237/BeaconService.o ${OBJECTDIR}/_ext/1360937237/UARTService.o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1360937237/ES_Main.o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ${OBJECTDIR}/_ext/1360937237/AD.o ${OBJECTDIR}/_ext/1360937237/BOARD.o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ${OBJECTDIR}/_ext/1360937237/LED.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/RC_Servo.o ${OBJECTDIR}/_ext/1360937237/serial.o ${OBJECTDIR}/_ext/1360937237/Stepper.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o ${OBJECTDIR}/_ext/1360937237/BOAT.o ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o ${OBJECTDIR}/_ext/1360937237/Protocol2.o ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o ${OBJECTDIR}/_ext/1360937237/EventChecker.o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o

# Source Files
SOURCEFILES=../src/TapeAndTrackService.c ../src/BumperService.c ../src/BeaconService.c ../src/UARTService.c ../src/ES_CheckEvents.c ../src/ES_Framework.c ../src/ES_KeyboardInput.c ../src/ES_Main.c ../src/ES_PostList.c ../src/ES_Queue.c ../src/ES_TattleTale.c ../src/ES_Timers.c ../src/AD.c ../src/BOARD.c ../src/IO_Ports.c ../src/LED.c ../src/pwm.c ../src/RC_Servo.c ../src/serial.c ../src/Stepper.c ../src/timers.c ../src/BOAT_Movement.c ../src/BOAT.c ../src/BOAT_Sensors.c ../src/Protocol2.c ../src/BOAT_HSM.c ../src/EventChecker.c ../src/BOAT_SubHSM_MoveToPosition.c ../src/BOAT_SubHSM_Returning.c



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

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MX320F128H
ProjectDir="C:\Users\student\Documents\ECE118 - Mechatronics\Final Project\ece118_boat\ECE118_BOAT.X"
ProjectName=ECE118_BOAT
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\bootloader320.ld"
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
${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o: ../src/TapeAndTrackService.c  .generated_files/flags/default/8ef817790b08bf82dc5892aacd4af88a404ba0bc .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o.d" -o ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o ../src/TapeAndTrackService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BumperService.o: ../src/BumperService.c  .generated_files/flags/default/3a826161c8d2806371fa42928a0c8fd6ce232701 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BumperService.o.d" -o ${OBJECTDIR}/_ext/1360937237/BumperService.o ../src/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BeaconService.o: ../src/BeaconService.c  .generated_files/flags/default/7b835a258a710b428cbe0988031e99990102396d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BeaconService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BeaconService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BeaconService.o.d" -o ${OBJECTDIR}/_ext/1360937237/BeaconService.o ../src/BeaconService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/UARTService.o: ../src/UARTService.c  .generated_files/flags/default/a8557e75ba09c2e6ebbe51ac637389057cf13933 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UARTService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UARTService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/UARTService.o.d" -o ${OBJECTDIR}/_ext/1360937237/UARTService.o ../src/UARTService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o: ../src/ES_CheckEvents.c  .generated_files/flags/default/479c01c30a123680a39a481c8707ed9c01d63801 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Framework.o: ../src/ES_Framework.c  .generated_files/flags/default/2b3f3af7ed598abd0a66b960de0856a637bf7ebe .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o: ../src/ES_KeyboardInput.c  .generated_files/flags/default/8e1186eb7e415fe132167a1fedf2e4a9fe49893c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Main.o: ../src/ES_Main.c  .generated_files/flags/default/15303a3e1cf5c44dfa62478e476941ad7913d95 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Main.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Main.o ../src/ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_PostList.o: ../src/ES_PostList.c  .generated_files/flags/default/b94e4d8d5b72d7875c3900e8f39e90b6c35ce9c7 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Queue.o: ../src/ES_Queue.c  .generated_files/flags/default/4ef557b41e5b19d5e278fcff7e78b8174cc6088f .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o: ../src/ES_TattleTale.c  .generated_files/flags/default/a0484035773ad5d9a82eaba5251da567962e6582 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Timers.o: ../src/ES_Timers.c  .generated_files/flags/default/d2e7c473df364441a10983fc0b6cbf6f2c28ca79 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/AD.o: ../src/AD.c  .generated_files/flags/default/7da4102b0af9e1c2e57d378f43eb2ffddfb82bfa .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/AD.o.d" -o ${OBJECTDIR}/_ext/1360937237/AD.o ../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOARD.o: ../src/BOARD.c  .generated_files/flags/default/a3f4395f573ce03579a046b86c559e762c7bbf6b .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOARD.o ../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/IO_Ports.o: ../src/IO_Ports.c  .generated_files/flags/default/a2873dce47ae5139f18512ccd766d3fec9534172 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/LED.o: ../src/LED.c  .generated_files/flags/default/8d759bc8dae89061bb3a7d597d413c63f4b1dba9 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/LED.o.d" -o ${OBJECTDIR}/_ext/1360937237/LED.o ../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  .generated_files/flags/default/a17097c0d109167fe1f73c73b021456756d949c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/pwm.o ../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/RC_Servo.o: ../src/RC_Servo.c  .generated_files/flags/default/93560719eeb8e3cabeb734f3fb9d942cd18aa158 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1360937237/RC_Servo.o ../src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/serial.o: ../src/serial.c  .generated_files/flags/default/48a89443aefd6e77be18b60db63367d0e53dc613 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/serial.o.d" -o ${OBJECTDIR}/_ext/1360937237/serial.o ../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Stepper.o: ../src/Stepper.c  .generated_files/flags/default/6b62d71af978959287eee0c2460d0573bb237da7 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Stepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Stepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Stepper.o.d" -o ${OBJECTDIR}/_ext/1360937237/Stepper.o ../src/Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  .generated_files/flags/default/5f8400f2c1c32ac65e53078448ce08feba1277bf .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o: ../src/BOAT_Movement.c  .generated_files/flags/default/3cae6d1cf74fc25542249dbb2d448c3b80e73039 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o ../src/BOAT_Movement.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT.o: ../src/BOAT.c  .generated_files/flags/default/ebfa82e44f5dd5b4f83c9f69c7c4a9f1b11e1bdb .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT.o ../src/BOAT.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o: ../src/BOAT_Sensors.c  .generated_files/flags/default/9444b2bf4abeb8116b5cf4906c2e25c6973cf813 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o ../src/BOAT_Sensors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Protocol2.o: ../src/Protocol2.c  .generated_files/flags/default/da8ae954a02bb67564e5af323c1f010bebd3bd9b .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Protocol2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Protocol2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Protocol2.o.d" -o ${OBJECTDIR}/_ext/1360937237/Protocol2.o ../src/Protocol2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o: ../src/BOAT_HSM.c  .generated_files/flags/default/de684e76db7663411c5cb540fa5010127eed1a5a .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o ../src/BOAT_HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/EventChecker.o: ../src/EventChecker.c  .generated_files/flags/default/c44528aa207d0f82c1ae65bcb135b55c5ddd97d1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1360937237/EventChecker.o ../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o: ../src/BOAT_SubHSM_MoveToPosition.c  .generated_files/flags/default/f9037b88a27212bc7c2bc0db9d27bbdf440c5621 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o ../src/BOAT_SubHSM_MoveToPosition.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o: ../src/BOAT_SubHSM_Returning.c  .generated_files/flags/default/c43ad180ae7925d1109e2e467111f52c18aa4abb .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o ../src/BOAT_SubHSM_Returning.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o: ../src/TapeAndTrackService.c  .generated_files/flags/default/a281f9701a5474111a817c5a4f9072b62d23697c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o.d" -o ${OBJECTDIR}/_ext/1360937237/TapeAndTrackService.o ../src/TapeAndTrackService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BumperService.o: ../src/BumperService.c  .generated_files/flags/default/76febe15ab3fefa092024c8b42ba319aa41ead8b .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BumperService.o.d" -o ${OBJECTDIR}/_ext/1360937237/BumperService.o ../src/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BeaconService.o: ../src/BeaconService.c  .generated_files/flags/default/b6c6c4ecb47b6b292bf0378f7e2ff05560a98c61 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BeaconService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BeaconService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BeaconService.o.d" -o ${OBJECTDIR}/_ext/1360937237/BeaconService.o ../src/BeaconService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/UARTService.o: ../src/UARTService.c  .generated_files/flags/default/abf7e08106f9344ed7361851c100e88649f456c8 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UARTService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/UARTService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/UARTService.o.d" -o ${OBJECTDIR}/_ext/1360937237/UARTService.o ../src/UARTService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o: ../src/ES_CheckEvents.c  .generated_files/flags/default/a350081fc7ab41daf732c5f71007035c777164a1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_CheckEvents.o ../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Framework.o: ../src/ES_Framework.c  .generated_files/flags/default/432e97b707c37186eaf3b40d7f7db8c6110d25c6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Framework.o ../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o: ../src/ES_KeyboardInput.c  .generated_files/flags/default/9e4ecd21e5871491d1203cfab7dfe70f37232be5 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_KeyboardInput.o ../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Main.o: ../src/ES_Main.c  .generated_files/flags/default/2b3ffa527a56faa97206d4f1446543fbe6b491dd .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Main.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Main.o ../src/ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_PostList.o: ../src/ES_PostList.c  .generated_files/flags/default/37be19e833f6e1324399e9a2695aa703997f91f6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_PostList.o ../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Queue.o: ../src/ES_Queue.c  .generated_files/flags/default/d202fffac8f899e0ed97f5e69651d8c5f4284a9e .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Queue.o ../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o: ../src/ES_TattleTale.c  .generated_files/flags/default/487177fc0302906609df6387a940329b5c7dce44 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_TattleTale.o ../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/ES_Timers.o: ../src/ES_Timers.c  .generated_files/flags/default/1fc8be86f33fe5dec550f11e83e4041dbd419e1d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/ES_Timers.o ../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/AD.o: ../src/AD.c  .generated_files/flags/default/8e31f417bd9730c766ec0cc367d331d5a81738d5 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/AD.o.d" -o ${OBJECTDIR}/_ext/1360937237/AD.o ../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOARD.o: ../src/BOARD.c  .generated_files/flags/default/252171eca495e24b9a2c4a304b45eafd3cf28667 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOARD.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOARD.o ../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/IO_Ports.o: ../src/IO_Ports.c  .generated_files/flags/default/b3836d520d6938369af5f7095755583a3cb11f3a .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1360937237/IO_Ports.o ../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/LED.o: ../src/LED.c  .generated_files/flags/default/cf33a3cfb59081c88d1691254e0feeda620da46d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/LED.o.d" -o ${OBJECTDIR}/_ext/1360937237/LED.o ../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  .generated_files/flags/default/1eea716e0ba61afd06fced6f0d253b700e5f0101 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d" -o ${OBJECTDIR}/_ext/1360937237/pwm.o ../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/RC_Servo.o: ../src/RC_Servo.c  .generated_files/flags/default/ecbacd2d97777fca58dde220a0285d6075978244 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1360937237/RC_Servo.o ../src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/serial.o: ../src/serial.c  .generated_files/flags/default/628edf8e4c6d9550b76929a6104dcb82bec1627f .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/serial.o.d" -o ${OBJECTDIR}/_ext/1360937237/serial.o ../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Stepper.o: ../src/Stepper.c  .generated_files/flags/default/b571b97c90263e5d92e76d3af93d23314a043391 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Stepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Stepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Stepper.o.d" -o ${OBJECTDIR}/_ext/1360937237/Stepper.o ../src/Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  .generated_files/flags/default/fccd5623948794d88b6b22cd7ba7e91693763afa .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o: ../src/BOAT_Movement.c  .generated_files/flags/default/344a598725c0396e16606f33920404778499271f .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_Movement.o ../src/BOAT_Movement.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT.o: ../src/BOAT.c  .generated_files/flags/default/b12b7c8fdc89661a3e325ac0e5666c5fc5d795ab .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT.o ../src/BOAT.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o: ../src/BOAT_Sensors.c  .generated_files/flags/default/d72baf4895538676ecf536681452309f68bf0f0c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_Sensors.o ../src/BOAT_Sensors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/Protocol2.o: ../src/Protocol2.c  .generated_files/flags/default/d528656982f7f45749b0e0fc3520c3975522e6b6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Protocol2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Protocol2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/Protocol2.o.d" -o ${OBJECTDIR}/_ext/1360937237/Protocol2.o ../src/Protocol2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o: ../src/BOAT_HSM.c  .generated_files/flags/default/988a7510e2d4074bfd1aa1c993a330d903328b42 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_HSM.o ../src/BOAT_HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/EventChecker.o: ../src/EventChecker.c  .generated_files/flags/default/528cfddf7406c9fa571d123178276d913bb732fe .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/EventChecker.o.d" -o ${OBJECTDIR}/_ext/1360937237/EventChecker.o ../src/EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o: ../src/BOAT_SubHSM_MoveToPosition.c  .generated_files/flags/default/4a73c347f49d78f9f3e11450bd5a8b3d9298e54a .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_MoveToPosition.o ../src/BOAT_SubHSM_MoveToPosition.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o: ../src/BOAT_SubHSM_Returning.c  .generated_files/flags/default/1ca40fbcf5377657665ee8c72b301ba0af1835e .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o.d" -o ${OBJECTDIR}/_ext/1360937237/BOAT_SubHSM_Returning.o ../src/BOAT_SubHSM_Returning.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--defsym=_min_heap_size=5000,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=5000,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ECE118_BOAT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\Users\student\Enum_To_String.py]"
	@python C:\Users\student\Enum_To_String.py
	@echo "--------------------------------------"

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
