#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void Task_1_LED(void *pvParameters)
{
    while(1)
    {
        printf("task_1_led_\n");
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2_ALARM(void *pvParameters)
{
    while(1)
    {
        printf("task_2_alarm\n");
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_LED,"TaskDelayLog1",1024,NULL,20,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_ALARM,"TaskDelayLog2",1024,NULL,10,&xHandle_Task_2);
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