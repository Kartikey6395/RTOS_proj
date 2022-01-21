#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

int i = 0;
void Task_1(void *pvParameters)
{
    while(1)
    {
        printf("INC = %d\n",i++);
    }
}

void Task_2(void *pvParameters)
{
    while(1)
    {
        printf("DEC = %d\n",i--);
    }
}

void app_main()
{
    TaskHandle_t xHandle_Task_1 =NULL;
    TaskHandle_t xHandle_Task_2 =NULL;
    BaseType_t xReturned_1;
    BaseType_t xReturned_2;

   xReturned_1 = xTaskCreate(Task_1,"TaskLog_1",2048,NULL,5,&xHandle_Task_1);
   xReturned_2 = xTaskCreate(Task_2,"TaskLog_2",2048,NULL,4,&xHandle_Task_2);

   if(xReturned_1 == pdPASS)
   {
       printf("Task_1 created \n");
       vTaskDelete(xHandle_Task_1);
   }

   if(xReturned_2 == pdPASS)
   {
       printf("Task_2 created \n");
       vTaskDelete(xHandle_Task_2);
   }

}