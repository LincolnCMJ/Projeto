#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "esp_system.h"
// #include "esp_log.h"

#include "modem_config.h"
#include "mqtt.h"


void app_main(void) {
    init_uart();
    modem_activate();
    send();
}