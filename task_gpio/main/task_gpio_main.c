#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


#define LED_PIN 15


void Task_LED(void *pvParameters)
{
    //esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED_PIN,1);
        printf("LED ON\n");
        vTaskDelay(2000/ portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN,0);
        printf("LED OFF\n");
    }

}

void Task_ALARM(void *pvParameters)
{
    while(1)
    {
    printf("ALARM ON\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    BaseType_t xReturned_1;
    BaseType_t xReturned_2;
    TaskHandle_t xHandle_Task_1 = NULL;
    TaskHandle_t xHandle_Task_2 = NULL;

    xReturned_1 = xTaskCreate(Task_LED,"LED",1024,NULL,20,&xHandle_Task_1);
    xReturned_2 = xTaskCreate(Task_ALARM,"ALARM",1024,NULL,20,&xHandle_Task_2);

    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created\n");
       // vTaskDelete( xHandle_Task_1);
    }

    if(xReturned_2 == pdPASS)
    {
        printf("task 2 created\n");
      //  vTaskDelete( xHandle_Task_2);
    }

}
