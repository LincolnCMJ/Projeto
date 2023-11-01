#include "load_libraries.h"

#include "modem_commands.h"
#include "mqtt.h"
#include "wifi_connection.h"


void app_main()
{
    printf("Waiting for initialization.....\r\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    printf("Ready.\r\n");

    esp_connect();
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("WIFI was initiated ...........\n");

    while (1)
    {
        send();
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
    
    
    // init_uart();
    // //gsm_connection();
}