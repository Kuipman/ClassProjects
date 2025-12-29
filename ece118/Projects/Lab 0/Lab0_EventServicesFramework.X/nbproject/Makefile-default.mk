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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../src/AD.c ../../../src/BOARD.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c EventChecker.c BumperService.c ES_Main.c TemplateService.c Midterm_Part5.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/EventChecker.o ${OBJECTDIR}/BumperService.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/Midterm_Part5.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386528437/AD.o.d ${OBJECTDIR}/_ext/1386528437/BOARD.o.d ${OBJECTDIR}/_ext/1386528437/pwm.o.d ${OBJECTDIR}/_ext/1386528437/roach.o.d ${OBJECTDIR}/_ext/1386528437/serial.o.d ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d ${OBJECTDIR}/EventChecker.o.d ${OBJECTDIR}/BumperService.o.d ${OBJECTDIR}/ES_Main.o.d ${OBJECTDIR}/TemplateService.o.d ${OBJECTDIR}/Midterm_Part5.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/roach.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ${OBJECTDIR}/EventChecker.o ${OBJECTDIR}/BumperService.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/Midterm_Part5.o

# Source Files
SOURCEFILES=../../../src/AD.c ../../../src/BOARD.c ../../../src/pwm.c ../../../src/roach.c ../../../src/serial.c ../../../src/ES_CheckEvents.c ../../../src/ES_Framework.c ../../../src/ES_KeyboardInput.c ../../../src/ES_PostList.c ../../../src/ES_Queue.c ../../../src/ES_TattleTale.c ../../../src/ES_Timers.c EventChecker.c BumperService.c ES_Main.c TemplateService.c Midterm_Part5.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/545a9709d2de5a56e73c901ecdc1f26becca810c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/2d37cdaf37156be7a12382f5bc684fa602f0cb9f .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/1759ae789a3504af5eaec9d4e2f7ac030e8747e0 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/91b2a23d1eb1cdd736d45c1210441eae9f75f7bb .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/50a9404066e670e81aecf68c0fc23ff72aa9d447 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/61f34562a98546f53323783b9634d2527e60854a .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/97ab0531e9b400b943b6c553ec265ee103a03bf7 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/696fc94f741d7ae8737ab36cb81fb051ebc47bf3 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/befa1adbe1e6c28bbe9ecf6bc4c47c86fd6831c6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/f370ff34b9558057faa70dbde70f1f6904ff1ea1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/376d00dfc4d2daf7121f8441683ab9fbd38336f6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/e94cfb59c14a3921b9295d9f50aeab388ed8232d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EventChecker.o: EventChecker.c  .generated_files/flags/default/b6006981733a978c676c6d7919baecccf0573487 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/EventChecker.o.d" -o ${OBJECTDIR}/EventChecker.o EventChecker.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BumperService.o: BumperService.c  .generated_files/flags/default/bf1f18c3430975b921c33f64c7cab9a9a77b76f6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/dc548ff9448bb5fa10f2f8525d86dc427161b51 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/2250d1a8bcf86dd6367e08ee7805779a03bb20c2 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5.o: Midterm_Part5.c  .generated_files/flags/default/ca8e9f423fbd387dec5d68dab06483d29038da25 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5.o.d" -o ${OBJECTDIR}/Midterm_Part5.o Midterm_Part5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/305a348fb7596e84dbeea0efda89d6dea451dcef .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/6ffa326a1f8bfd9b9ca52a7cea1af364b8abdad5 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/11b6ffd37a2fda37aafeea55f360c7810ea29de1 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/roach.o: ../../../src/roach.c  .generated_files/flags/default/ae75fea01af1e69f3cb0bcbe2b230c51ffd5252d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/roach.o.d" -o ${OBJECTDIR}/_ext/1386528437/roach.o ../../../src/roach.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/896443fa5d5d8785f7602513fee3a7c1f837da79 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o: ../../../src/ES_CheckEvents.c  .generated_files/flags/default/1e4e7a9892871b54f5d298527303ad8b53370f36 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_CheckEvents.o ../../../src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Framework.o: ../../../src/ES_Framework.c  .generated_files/flags/default/fefed305334e4970b184b00c1feb7102cb10ac56 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Framework.o ../../../src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o: ../../../src/ES_KeyboardInput.c  .generated_files/flags/default/e61fdf35968b73aed5775de3f8f883f6007ebb9 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_KeyboardInput.o ../../../src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_PostList.o: ../../../src/ES_PostList.c  .generated_files/flags/default/476b108537c5be36af563051994f96f9cebbbe68 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_PostList.o ../../../src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Queue.o: ../../../src/ES_Queue.c  .generated_files/flags/default/367bbbea83e03f70d7fd0ac7055e097373e860ce .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Queue.o ../../../src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o: ../../../src/ES_TattleTale.c  .generated_files/flags/default/eb44c57cf8ee4f0f0665cd4fae3d41ff10103fe4 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_TattleTale.o ../../../src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/ES_Timers.o: ../../../src/ES_Timers.c  .generated_files/flags/default/507234ebbc98045c9ee59228e0997e4ee6294e5d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1386528437/ES_Timers.o ../../../src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EventChecker.o: EventChecker.c  .generated_files/flags/default/4750d299d8310b63982fc00f6eb318f39343c2d .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/EventChecker.o.d" -o ${OBJECTDIR}/EventChecker.o EventChecker.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BumperService.o: BumperService.c  .generated_files/flags/default/46dbaeeaa630d540c77801e5d6e9c2e8bd98ea6f .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/a8c9b35923e1b2e6ebbdc154adb2df77645b3fa .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/9b54c4848ea06336f13c17eb018cce7bea5dc004 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5.o: Midterm_Part5.c  .generated_files/flags/default/60832aabd4b4d6ab8ce7aa904452c89868227b54 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../include" -I"../../../templates" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5.o.d" -o ${OBJECTDIR}/Midterm_Part5.o Midterm_Part5.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=500,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab0_EventServicesFramework.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
