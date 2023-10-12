#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "uart_communication.h"

void modem_activate() {
    const char *messages[] = {
        "AT\r\n",
        "AT+CFUN=1\r\n",
        "AT+CSQ\r\n",
        "AT+CSTT=\"zap.vivo.com.br\",\"vivo\",\"vivo\"\r\n",
        
    };
    
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    int current_message_index = 0;

    while (1) {
        if (current_message_index < num_messages) {
            send_at_command(messages[current_message_index]);
            current_message_index++;
        } else {
            break;
        }
        receive();
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}