#include "load_libraries.h"

#include "modem_commands.h"
#include "mqtt.h"
#include "wifi_connection.h"

#include "nmea_parser_example_main.h"

void app_main()
{
    printf("Waiting for initialization.\r\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    printf("Ready.\r\n");

    esp_WiFi();
    vTaskDelay(pdMS_TO_TICKS(2000));

    // init_uart();
    // gsm_connection();

    send_data();
}