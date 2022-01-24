#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandle_Task_1 = NULL;
TaskHandle_t xHandle_Task_2 = NULL;


void Task_1_Sensor(void *pvParameters)
{   int i = 0;
    while(1)
    {   vTaskDelay(1200 / portTICK_PERIOD_MS);
        vTaskSuspend(NULL);
        
        i++;
        printf("task_1_sensor_inp =%d\n",i);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        
        
    }
}

void Task_2_Process(void *pvParameters)
{int j=0;
    while(1)
    {
        
        printf("task_2_in_process | count=%d\n",j++);
        vTaskResume(xHandle_Task_1);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        //vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_Sensor,"Task_resume_1",2048,NULL,2,&xHandle_Task_1);
    
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_Process,"Task_suspend_2",2048,NULL,2,&xHandle_Task_2);
    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_1));
        //vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 2 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_2));
        //vTaskDelete( xHandle_Task_2);
    }
}