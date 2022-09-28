cmake_minimum_required(VERSION 3.0.0)
project(bluepill_usb_ir_mouse VERSION 0.1.0)

set(GENERATED_BINARY bluepill_usb_ir_mouse)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/stm32f103.ld") # stm32f103c8 (64k/20k)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m3 -mthumb -std=c17 -nostdlib -DSTM32F1 -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} 
    -T ${LINKER_SCRIPT} --specs=nosys.specs -mcpu=cortex-m3 -nostdlib -L ${CMAKE_SOURCE_DIR}/lib/"
)

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,-Map,${GENERATED_BINARY}.map")

#add_subdirectory(necinfrared)

set(OPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3/)

add_custom_target(libopencm3 ALL
    COMMAND make TARGETS='stm32/f1'
    WORKING_DIRECTORY ${OPENCM3_DIR}
)

add_executable(${GENERATED_BINARY}
    main.c
    hid_functions.c
    mouse_actions.c
)

target_include_directories(${GENERATED_BINARY} PUBLIC
    necinfrared/
    ${OPENCM3_DIR}/include/
    ${OPENCM3_DIR}/include/libopencmsis/
)

target_link_libraries(${GENERATED_BINARY}
    necdecoder
    opencm3_stm32f1
)
