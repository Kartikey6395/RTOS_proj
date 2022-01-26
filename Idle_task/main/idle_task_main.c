#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_freertos_hooks.h>



int i = 0;
TickType_t TickCount_1,TickCount_2,TickCount_3;
void Task_1(void *pvParameters)
{
    while(1)
    {
        printf("INC = %d\n",i++);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        TickCount_1 = xTaskGetTickCount();
        printf("countTICKS_Task_1 = %d\n",TickCount_1);
    }
}

void IdleTaskHook(void *pvParameters)
{
    while(1)
    {
        TickCount_2 = xTaskGetTickCount();
        printf("countTICKS_Task_Idle = %d\n",TickCount_2);
        
        //vTaskDelay(2000 / portTICK_PERIOD_MS);
        
    }
}
 bool vApplicationIdleHook()
 {
     printf("This is Idle_Task_Hooking_cb function\n");
     TickCount_2 = xTaskGetTickCount();
     printf("countTICKS_Idle_task = %d\n",TickCount_2);
    return true;
 }
 void vApplicationTickHook()
 {
     return;
 }


void app_main()
{
    TaskHandle_t xHandle_Task_1 =NULL;
   TaskHandle_t xHandle_Task_Idle =NULL;
    BaseType_t xReturned_1;
   BaseType_t xReturned_2;
   TickCount_3 = xTaskGetTickCount();
    printf("countTICKS_main = %d\n",TickCount_3);
   xReturned_1 = xTaskCreate(Task_1,"TaskLog_1",2048,NULL,5,&xHandle_Task_1);
   xReturned_2 = xTaskCreate(IdleTaskHook,"TaskLog_Idle",2048,NULL,tskIDLE_PRIORITY,&xHandle_Task_Idle);
    //xTaskGetIdleTaskHandle();
    esp_register_freertos_idle_hook(vApplicationIdleHook);
    esp_register_freertos_tick_hook(vApplicationTickHook);
    vTaskDelay(1000/portTICK_PERIOD_MS);
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