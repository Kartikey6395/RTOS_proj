#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

struct Queue
{
    char Task_name[10];
    eTaskState Task_state;
    UBaseType_t Task_stacksize;
};
QueueHandle_t xMsgQueue_1;

QueueHandle_t xStructQueue_2;
void Task_1_Sensor(void *pvParameters)
{   int i = 0,count=0;
    struct Queue *Msg_Q_1 = {pcTaskGetName(NULL),eTaskGetState(NULL),uxTaskGetStackHighWaterMark( NULL )};
    xQueueSend(xStructQueue_2,(void *)&Msg_Q_1,portMAX_DELAY);

    while(1)
    {   
        
        i++;
        count++;
        xQueueSend(xMsgQueue_1,&i,portMAX_DELAY);
        printf("Sensor_task:Sending Data = %d\n",i);
        if(count > 10)
        {
            count =0;
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}

void Task_2_Process(void *pvParameters)
{
    struct Queue *Msg_Q_2 = {pcTaskGetName(NULL),eTaskGetState(NULL),uxTaskGetStackHighWaterMark( NULL )};
    xQueueSend(xStructQueue_2,(void *)&Msg_Q_2,portMAX_DELAY);

    int j = 0;
    while(1)
    {
        
        xQueueReceive(xMsgQueue_1,&j,portMAX_DELAY);
        printf("Processing_task:receive data =%d\n",j);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    
    xMsgQueue_1 = xQueueCreate( 10,sizeof(int));
    xStructQueue_2 = xQueueCreate( 2,sizeof(struct Queue*));
 
    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_Sensor,"Task_1_Sensing",2048,NULL,5,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_Process,"Task_2_Processing",2048,NULL,5,&xHandle_Task_2);

    struct Queue *xpMsg_Q = {"\0",0,0};
    if((xQueueReceive(xStructQueue_2,&xpMsg_Q,portMAX_DELAY)) == pdPASS)
    {
        printf("xQueue is full goes to blockmode\n");
        printf("Task_name => %s\n",(char *)xpMsg_Q->Task_name);
    printf("Task State => %d\n",xpMsg_Q->Task_state);
    printf("Task_stacksize => %d\n",(xpMsg_Q->Task_stacksize));
    }

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