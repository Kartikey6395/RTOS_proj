#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void Task_1_delay(void *pvParameters)
{
    while(1)
    {
        printf("task_1\n");
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2_delay(void *pvParameters)
{
    while(1)
    {
        printf("task_2\n");
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_delay,"TaskDelayLog1",1024,NULL,2,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_delay,"TaskDelayLog2",1024,NULL,2,&xHandle_Task_2);
    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created\n");
        //vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 2 created\n");
        //vTaskDelete( xHandle_Task_2);
    }
}