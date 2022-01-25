#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>


#define LED_PIN 15
#define BUZZ_PIN 16

TimerHandle_t xHandle_Timer;
int i =0;
void Task_LED(void *pvParameters)
{
    esp_rom_gpio_pad_select_gpio(LED_PIN);
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
//Timer Callback Function
void ON_BUZZER( TimerHandle_t xMyTimer )
{
    i++;
    esp_rom_gpio_pad_select_gpio(BUZZ_PIN);
    gpio_set_direction(BUZZ_PIN,GPIO_MODE_OUTPUT);
    while(1)
    {
        
        gpio_set_level(BUZZ_PIN,1);
        printf("Timer buzz ON\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        gpio_set_level(BUZZ_PIN,0);
        printf("Timer BUZZ OFF\n");
        if(i == 5)
        {
            printf("timer stopped\n");
            xTimerStop(xMyTimer ,0);
        }
    }


}


void app_main()
{
    BaseType_t xReturned_1;
    
    TaskHandle_t xHandle_Task_1 = NULL;

    xReturned_1 = xTaskCreate(Task_LED,"LED",1024,NULL,20,&xHandle_Task_1);
     
    xHandle_Timer =  xTimerCreate("timer_BUZZ",pdMS_TO_TICKS(5000),pdTRUE,NULL,ON_BUZZER);


    xTimerStart(xHandle_Timer,0);
                 

    

    if(xReturned_1 == pdPASS)
    {
        printf("task 1 created\n");
       // vTaskDelete( xHandle_Task_1);
    }

    /*if(xReturned_2 == pdPASS)
    {
        printf("task 2 created\n");
      //  vTaskDelete( xHandle_Task_2);
    }*/

}
