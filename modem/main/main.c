#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

#include "at_commands.h"
#include "mqtt.h"


void app_main(void)
{
    init_uart();
    at_messages();
    //send();
}