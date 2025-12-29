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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../src/AD.c ../../../src/BOARD.c ../../../src/IO_Ports.c ../../../src/LED.c ../../../src/RC_Servo.c ../../../src/pwm.c ../../../src/serial.c Midterm_Part5_A.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ${OBJECTDIR}/_ext/1386528437/LED.o ${OBJECTDIR}/_ext/1386528437/RC_Servo.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/Midterm_Part5_A.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386528437/AD.o.d ${OBJECTDIR}/_ext/1386528437/BOARD.o.d ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d ${OBJECTDIR}/_ext/1386528437/LED.o.d ${OBJECTDIR}/_ext/1386528437/RC_Servo.o.d ${OBJECTDIR}/_ext/1386528437/pwm.o.d ${OBJECTDIR}/_ext/1386528437/serial.o.d ${OBJECTDIR}/Midterm_Part5_A.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386528437/AD.o ${OBJECTDIR}/_ext/1386528437/BOARD.o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ${OBJECTDIR}/_ext/1386528437/LED.o ${OBJECTDIR}/_ext/1386528437/RC_Servo.o ${OBJECTDIR}/_ext/1386528437/pwm.o ${OBJECTDIR}/_ext/1386528437/serial.o ${OBJECTDIR}/Midterm_Part5_A.o

# Source Files
SOURCEFILES=../../../src/AD.c ../../../src/BOARD.c ../../../src/IO_Ports.c ../../../src/LED.c ../../../src/RC_Servo.c ../../../src/pwm.c ../../../src/serial.c Midterm_Part5_A.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/db237bf4b2b4bb89e74076296451b9d062c55881 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/f4a54f145c1dc04ca795bb1230dcb7074819a0f3 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/IO_Ports.o: ../../../src/IO_Ports.c  .generated_files/flags/default/eaceb98b87c39fe3b0f831d51154c46ae9e327a6 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ../../../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LED.o: ../../../src/LED.c  .generated_files/flags/default/a0e8d167df069a03fa2acb1f87e0d9bc10f457de .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LED.o.d" -o ${OBJECTDIR}/_ext/1386528437/LED.o ../../../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/RC_Servo.o: ../../../src/RC_Servo.c  .generated_files/flags/default/d91d27a2eb84bbc8729235c7ba1823a27bb27490 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1386528437/RC_Servo.o ../../../src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/18746aa361ef28dcce219a6baa1653bf80f998af .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/d5f27e2f435e9da74f0342f2672e7259fbd0cb5c .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_A.o: Midterm_Part5_A.c  .generated_files/flags/default/25afee5291a41b6767b9217065540c976b8ce0ce .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_A.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_A.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_A.o.d" -o ${OBJECTDIR}/Midterm_Part5_A.o Midterm_Part5_A.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386528437/AD.o: ../../../src/AD.c  .generated_files/flags/default/150528253de6c66e638997bb5ab61ad981f030bf .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/AD.o.d" -o ${OBJECTDIR}/_ext/1386528437/AD.o ../../../src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/BOARD.o: ../../../src/BOARD.c  .generated_files/flags/default/9cbe872783ba085db16a392239099832844d20a5 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/BOARD.o.d" -o ${OBJECTDIR}/_ext/1386528437/BOARD.o ../../../src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/IO_Ports.o: ../../../src/IO_Ports.c  .generated_files/flags/default/993533c5378256472a43dc65c3be4e5e4de86704 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1386528437/IO_Ports.o ../../../src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/LED.o: ../../../src/LED.c  .generated_files/flags/default/d88ac86ba8b5a949b996e472f39fc838fed55989 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/LED.o.d" -o ${OBJECTDIR}/_ext/1386528437/LED.o ../../../src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/RC_Servo.o: ../../../src/RC_Servo.c  .generated_files/flags/default/43a6cc480918c06396eefc069da0146a48417e69 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1386528437/RC_Servo.o ../../../src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/pwm.o: ../../../src/pwm.c  .generated_files/flags/default/ce7c378cbfc27a4c2d03f4e0b36730d0520cccc8 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/pwm.o.d" -o ${OBJECTDIR}/_ext/1386528437/pwm.o ../../../src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386528437/serial.o: ../../../src/serial.c  .generated_files/flags/default/9785b2a1d1b39321dfc87721a9e086f771126a01 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}/_ext/1386528437" 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386528437/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1386528437/serial.o.d" -o ${OBJECTDIR}/_ext/1386528437/serial.o ../../../src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Midterm_Part5_A.o: Midterm_Part5_A.c  .generated_files/flags/default/11323b24061308674d70481ba07494076a81b1e4 .generated_files/flags/default/fceb011ff2e2d0413f553470470866dc2cdcec6b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Midterm_Part5_A.o.d 
	@${RM} ${OBJECTDIR}/Midterm_Part5_A.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/Midterm_Part5_A.o.d" -o ${OBJECTDIR}/Midterm_Part5_A.o Midterm_Part5_A.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1000,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1000,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab3Motors.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
