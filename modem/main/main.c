#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "modem_commands.h"
#include "mqtt.h"


void app_main()
{
    printf("Waiting for initialization.....\r\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Ready to run.\r\n");
    
    init_uart();
    modem_connect();
    //send();
}