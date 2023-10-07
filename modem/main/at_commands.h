#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "string.h"

#include "at_executor.h"

void at_messages()
{
//const char *messages[] = {"AT\n", "AT+CSQ\n", "AT+CCID\n", "AT+CREG?\n", "ATI\n", "AT+COPS?\n", "AT+CBC\n"};
    const char *messages[] = {
        "AT\r\n",
        "AT+CMEE=2\r\n",
        "AT+CPIN?\r\n",
        "AT+CREG?\r\n",
        "AT+CGATT?\r\n",
        "AT+CSQ\r\n",
        "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n",
        "AT+SAPBR=3,1,\"APN\",\"claro.com.br\"\r\n",
        "AT+SAPBR=1,1\r\n",
        "AT+SAPBR=2,1\r\n",
        "AT+HTTPINIT\r\n",
        "AT+HTTPPARA=\"CID\",1\r\n",
        "AT+HTTPPARA=\"URL\",\"https://www.m2msupport.net/m2msupport/http_get_test.php\"\r\n",
        "AT+HTTPDATA=16,10000\r\n",
        "AT+HTTPACTION=1\r\n"
    };
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    int current_message_index = 0;

    while (1) {
        if (current_message_index < num_messages) {
            send_at_command(messages[current_message_index]);
            current_message_index++;
        } else {
            //current_message_index = 0; // Restart messages
            break;
        }
        receive();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}