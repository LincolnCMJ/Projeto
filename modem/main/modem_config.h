#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "uart_communication.h"

void modem_activate() {
    const char *messages[] = {
        "AT\r\n",
        "AT+CGATT=1\r\n",
        "AT+CIPMUX=0\r\n",
        "AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"\r\n",
        "AT+CIICR\r\n",
        "AT+CIFSR\r\n",
        "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r\n",
        "AT+CIPSEND=48\r\n",
        "GET /update?api_key=USVTT9FAQOPBMP5G&field1=0\r\n\x1A",
        "AT+CIPCLOSE\r\n",
        "AT+CIPSHUT\r\n",
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
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}