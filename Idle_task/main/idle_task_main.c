#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>



int i = 0;
TickType_t TickCount;
void Task_1(void *pvParameters)
{
    while(1)
    {
        printf("INC = %d\n",i++);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        TickCount = xTaskGetTickCount();
        printf("countTICKS_Task_1 = %d\n",TickCount);
    }
}

void IdleTaskHook(void *pvParameters)
{
    while(1)
    {
        TickCount = xTaskGetTickCount();
        printf("countTICKS_Task_Idle = %d\n",TickCount);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        
    }
}
 //void vApplicationIdleHook(void);
 /*{
     printf("This is Idle_Task_Hooking\n");
     TickCount = xTaskGetTickCount();
     printf("countTICKS_Idle_task = %d\n",TickCount);
 }*/


void app_main()
{
    TaskHandle_t xHandle_Task_1 =NULL;
   TaskHandle_t xHandle_Task_Idle =NULL;
    BaseType_t xReturned_1;
    BaseType_t xReturned_2;
   TickCount = xTaskGetTickCount();
    printf("countTICKS_main = %d\n",TickCount);
   xReturned_1 = xTaskCreate(Task_1,"TaskLog_1",2048,NULL,5,&xHandle_Task_1);
   xReturned_2 = xTaskCreate(IdleTaskHook,"TaskLog_Idle",2048,NULL,tskIDLE_PRIORITY,&xHandle_Task_Idle);
    xTaskGetIdleTaskHandle();

   if(xReturned_1 == pdPASS)
   {
       printf("Task_1 created \n");
       //vTaskDelete(xHandle_Task_1);
   }
   if(xReturned_2 == pdPASS)
   {
       printf("Task_Idle_Hook created \n");
       
   }


   

}