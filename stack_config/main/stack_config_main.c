#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void Task_1_LED(void *pvParameters)
{
    while(1)
    {
        
        UBaseType_t uxHighWaterMark;

        
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        printf("task_1_led => %d\n",uxHighWaterMark);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2_ALARM(void *pvParameters)
{int i = 0;
    while(1)
    {
        
        UBaseType_t uxHighWaterMark;

        
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        printf("task_2_alarm => %d\n",uxHighWaterMark);
        printf("COUNT %d\n",i++);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_LED,"TaskDelayLog1",2048,NULL,10,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_ALARM,"TaskDelayLog2",2048,NULL,10,&xHandle_Task_2);
    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_1));
        vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 1 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_2));
        vTaskDelete( xHandle_Task_2);
    }
}