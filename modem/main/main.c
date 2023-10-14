#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "modem_config.h"
#include "mqtt.h"


void app_main(void) {
    printf("Waiting for initialization.....\r\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    printf("Ready to run.\r\n");
    
    init_uart();
    modem_activate();
}