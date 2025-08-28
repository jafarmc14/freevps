cmake_minimum_required(VERSION 3.16)
project(freertos_posix_hello C)
set(CMAKE_C_STANDARD 11)

add_executable(app
    main.c
    FreeRTOS-Kernel/list.c
    FreeRTOS-Kernel/queue.c
    FreeRTOS-Kernel/tasks.c
    FreeRTOS-Kernel/timers.c
    FreeRTOS-Kernel/event_groups.c
    FreeRTOS-Kernel/stream_buffer.c
    FreeRTOS-Kernel/croutine.c

    # port POSIX (GCC)
    FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/port.c
    FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
    FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}
    FreeRTOS-Kernel/include
    FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix
    FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils
)

# POSIX butuh pthread & realtime
target_link_libraries(app PRIVATE pthread rt)
