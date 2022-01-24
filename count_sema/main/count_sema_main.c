#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>


QueueHandle_t xMsgQueue_1;
SemaphoreHandle_t sem_count;


void Task_1_Sensor_A(void *pvParameters)
{   int samples = 0,count=0;
    
    while(1)
    {   
        
        samples++;
        count++;
        xSemaphoreTake(sem_count);
        xQueueSend(xMsgQueue_1,&samples,portMAX_DELAY);
        printf("Sensor_task:Sending Data = %d\n",samples);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        if(count == 10)
        {   xSemaphoreGive(sem_count);
            count =0;
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

int arr[10];

void Task_3_Sensor_B(void *pvParameters)
{   
    int count =0;
    while(1)
    {   
        count++;
        xSemaphoreTake(sem_count);
        xQueueReceive(xMsgQueue_1,&arr,portMAX_DELAY);
        printf("Sensor B_task_3:Sending Data arr[] = %d\n",arr[count]);
        &arr++;
        
        //vTaskDelay(500 / portTICK_PERIOD_MS);
        if(count == 10)
        {   xSemaphoreGive(sem_count);
            count =0;
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}


void Task_2_Process(void *pvParameters)
{
    
    int j = 0;
    while(1)
    {
        xSemaphoreTake( sem_count, portMAX_DELAY);
        xQueueReceive(xMsgQueue_1,&j,portMAX_DELAY);
        printf("Processing_task:receive data =%d\n",j);
        xSemaphoreGive(sem_count);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    
    xMsgQueue_1 = xQueueCreate( 10,sizeof(int));
    sem_count = xSemaphoreCreateCounting(2,2);
    
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_Sensor_A,"Task_1_Sensing",2048,NULL,5,&xHandle_Task_1);
     TaskHandle_t xHandle_Task_3 = NULL;
    BaseType_t xReturned_3;
    xReturned_3 = xTaskCreate(Task_3_Sensor_B,"Task_3_Sensing",2048,NULL,5,&xHandle_Task_3);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_Process,"Task_2_Processing",2048,NULL,5,&xHandle_Task_2);


    
   /* struct Queue *xpMsg_Q = {"\0",0,0};
    if((xQueueReceive(xStructQueue_2,&xpMsg_Q,portMAX_DELAY)) == pdPASS)
    {
        printf("Task_name => %s\n",(char *)xpMsg_Q->Task_name);
    printf("Task State => %d\n",xpMsg_Q->Task_state);
    printf("Task_stacksize => %d\n",xpMsg_Q->Task_stacksize);
    }
    */
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