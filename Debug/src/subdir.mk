################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AnimationMgr.cpp \
../src/Aspect.cpp \
../src/DebugDrawer.cpp \
../src/Engine.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp \
../src/GameMgr.cpp \
../src/GfxMgr.cpp \
../src/InputMgr.cpp \
../src/Mgr.cpp \
../src/Physics2D.cpp \
../src/SoundMgr.cpp \
../src/UiMgr.cpp \
../src/Utils.cpp \
../src/main.cpp 

OBJS += \
./src/AnimationMgr.o \
./src/Aspect.o \
./src/DebugDrawer.o \
./src/Engine.o \
./src/Entity381.o \
./src/EntityMgr.o \
./src/GameMgr.o \
./src/GfxMgr.o \
./src/InputMgr.o \
./src/Mgr.o \
./src/Physics2D.o \
./src/SoundMgr.o \
./src/UiMgr.o \
./src/Utils.o \
./src/main.o 

CPP_DEPS += \
./src/AnimationMgr.d \
./src/Aspect.d \
./src/DebugDrawer.d \
./src/Engine.d \
./src/Entity381.d \
./src/EntityMgr.d \
./src/GameMgr.d \
./src/GfxMgr.d \
./src/InputMgr.d \
./src/Mgr.d \
./src/Physics2D.d \
./src/SoundMgr.d \
./src/UiMgr.d \
./src/Utils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/zachcooper/eclipse-workspace/Blast-Commander_v3/inc" -I/usr/include/AL -I/usr/include/audio -I/usr/include/ois -I/usr/local/include/OGRE -I/usr/include/OIS -I/usr/local/include/OGRE/Overlay -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


