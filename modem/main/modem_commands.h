#include "modem_uart_com.h"

void modem_connect()
{
    int response_check = 1;
    bool network_connect = false;

    while(!network_connect) {
        switch (response_check)
        {
        case 1:
            send_at_command("ATE0\r\n", 1000); /*Disable echo.*/
            response_check = at_response("ATE0", response_check);
            break;
        case 2:
            send_at_command("AT+CIPSHUT\r\n", 3000); /*Deactivate GPRS PDP Context.*/
            response_check = at_response("AT+CIPSHUT", response_check);
            break;
        case 3:
            send_at_command("AT+CGATT=1\r\n", 2000); /*Atach to the GPRS network.*/
            response_check = at_response("AT+CGATT=1", response_check);
            break;
        case 4:
            send_at_command("AT+CIPMUX=0\r\n", 2000); /*Single IP connection.*/
            response_check = at_response("AT+CIPMUX=0", response_check);
            break;
        case 5:
            send_at_command("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"\r\n", 2000); /*Start task and set APN, user name, password.*/
            response_check = at_response("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"", response_check);
            break;
        case 6:
            send_at_command("AT+CIICR\r\n", 3000); /*Bring up wireless connection with GPRS or CSD.*/
            response_check = at_response("AT+CIICR", response_check);
            break;
        case 7:
            send_at_command("AT+CIFSR\r\n", 4000); /*Get local IP address.*/
            response_check = at_response("AT+CIFSR", response_check);
            break;
        case 8:
            send_at_command("AT+CIPSTART=\"TCP\",\"mqtt.eclipseprojects.io\",\"1883\"\r\n", 4000);
            response_check = at_response("AT+CIPSTART=\"TCP\",\"mqtt://mqtt.eclipseprojects.io\",\"1883\"", response_check);
            network_connect = true;
            break;
        
        }
    }
}

// send_at_command("AT+CSQ\r\n", 1000);