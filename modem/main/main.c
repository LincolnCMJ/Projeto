#include "load_libraries.h"

#include "modem_commands.h"
#include "mqtt.h"


void app_main()
{
    printf("Waiting for initialization.....\r\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    printf("Ready.\r\n");
    
    init_uart();
    gsm_connection();
    //vTaskDelay(pdMS_TO_TICKS());
    //send();
}