#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "modem_uart_com.h"

void modem_activate() {
    const char *init_commnands[] = {
        "AT\r\n",
        "AT+CGATT=1\r\n",
        "AT+CIPMUX=0\r\n",
        "AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"\r\n",
        "AT+CSQ\r\n",
        "AT+CIICR\r\n",
        "AT+CIFSR\r\n",
        "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r\n",
        "AT+CIPSEND=48\r\n",
        "GET /update?api_key=USVTT9FAQOPBMP5G&field1=30\r\n\x1A",
        //"AT+CIPCLOSE\r\n",
        //"AT+CIPSHUT\r\n",
    };
     
    int current_command_index = 0;
    int num_commands = sizeof(init_commnands) / sizeof(init_commnands[0]);

    while (1) {
        if (current_command_index < num_commands) {
            send_at_command(init_commnands[current_command_index]);
            current_command_index++;
        }
        else {
            break;
        }
        receive();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}