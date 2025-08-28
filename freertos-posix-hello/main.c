#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* Dipanggil kalau terjadi stack overflow */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void)xTask;
    printf("Stack overflow in task: %s\n", pcTaskName);
    fflush(stdout);
    taskDISABLE_INTERRUPTS();
    for(;;);
}

/* Dipanggil kalau malloc gagal */
void vApplicationMallocFailedHook(void) {
    printf("Malloc failed!\n");
    fflush(stdout);
    taskDISABLE_INTERRUPTS();
    for(;;);
}


static void vTaskA(void *pv) {
    (void)pv;
    for (;;) {
        printf("[TaskA] Hello from FreeRTOS!\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void vTaskB(void *pv) {
    (void)pv;
    for (;;) {
        printf("[TaskB] Tick count = %lu\n", (unsigned long)xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;) {} // tidak akan pernah sampai sini
    return 0;
}
