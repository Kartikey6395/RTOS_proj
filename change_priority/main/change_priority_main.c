#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void Task_1(void *pvParameters)
{   int i = 0;
    while(1)
    {   
        printf("task_1_count =%d\n",i);
        i++;
        if(i==500)
        {//const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        printf("task 1 created: Priority=> %d\n",uxTaskPriorityGet(NULL));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
         //vTaskDelete( NULL);
        }
    }
}

void Task_2(void *pvParameters)
{
    while(1)
    {
        printf("task 2 Priority=> %d\n",uxTaskPriorityGet(NULL));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        
        if(uxTaskPriorityGet(NULL) != tskIDLE_PRIORITY){
        printf("task 2 priority changed\n");
        }
        else{
        //printf("task priority remain same\n");
        vTaskPrioritySet(NULL,configMAX_PRIORITIES-1);
        }//vTaskDelete( NULL);

        
    }
}


void app_main()
{
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1,"TaskDelayLog1",2048,NULL,4,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2,"TaskDelayLog2",2048,NULL,tskIDLE_PRIORITY,&xHandle_Task_2);
    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_1));
       
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 2 created: Priority=> %d\n",uxTaskPriorityGet(xHandle_Task_2));
        //vTaskDelete( xHandle_Task_2);
    }
}