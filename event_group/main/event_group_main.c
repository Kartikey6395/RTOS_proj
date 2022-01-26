#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

EventGroupHandle_t sensor_eg;
const uint32_t temperature_bit = (1 << 0);
const uint32_t pressure_bit = (1 << 1);
const uint32_t all_bit = (temperature_bit | pressure_bit);

void Task_1_pressure(void *pvParameters)
{
    while(1)
    {
        printf("task_1_PRESSURE\n");
        xEventGroupSetBits( sensor_eg,pressure_bit);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2_temp(void *pvParameters)
{
    while(1)
    {
        printf("task_2_TEMP\n");
        xEventGroupSetBits( sensor_eg,temperature_bit);
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
}

void Task_3_calib(void *pvParameters)
{
    uint32_t result;
    while(1)
    {
        printf("task_caliberation\n");
        result = xEventGroupWaitBits( sensor_eg, all_bit , pdTRUE , pdTRUE, pdMS_TO_TICKS(3000));
        //const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
        printf("result = %d\n",result);
    }
    vTaskDelete(NULL);
}


void app_main()
{
     
    sensor_eg = xEventGroupCreate();

    TaskHandle_t xHandle_Task_1 = NULL;
    BaseType_t xReturned_1;
    xReturned_1 = xTaskCreate(Task_1_pressure,"TaskDelayLog1",2048,NULL,2,&xHandle_Task_1);
    TaskHandle_t xHandle_Task_2 = NULL;
    BaseType_t xReturned_2;
    xReturned_2 = xTaskCreate(Task_2_temp,"TaskDelayLog2",2048,NULL,2,&xHandle_Task_2);
    TaskHandle_t xHandle_Task_3 = NULL;
    BaseType_t xReturned_3;
    xReturned_3 = xTaskCreate(Task_3_calib,"TaskDelayLog2",2048,NULL,2,&xHandle_Task_3);
    
    if(xReturned_1 == pdPASS)
    {
        printf("task 1 pressure created\n");
        //vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 2 temperature created\n");
        //vTaskDelete( xHandle_Task_2);
    }
    
    if(xReturned_3 == pdPASS)
    {
        printf("task 3 calib created\n");
        //vTaskDelete( xHandle_Task_2);
    }
}