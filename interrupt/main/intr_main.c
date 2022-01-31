#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>
static portMUX_TYPE mux;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;
uint32_t resource=0;
void Alarmtask_1(void *pvparameters)
{
    while(1)
    {
        printf("ALARM TASK  RUNNING\n");
        taskENTER_CRITICAL(&mux);
    
        resource++;
        taskEXIT_CRITICAL(&mux);
        printf("RESOURCE %d\n",resource);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void Delaytask_1(void *pv)
{
    uint32_t count=0;
    while(1)
    {
        count++;
        printf("DALEY TASK RUNNING :%d\n",count);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void app_main()
{
    vPortCPUInitializeMutex(&mux);
    BaseType_t result;
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_1);
    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    result=xTaskCreate(Delaytask_1,"Delaytask_1",2048,NULL,5,&xHandle_2);
    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}
