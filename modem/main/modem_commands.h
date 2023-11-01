#include "modem_uart_com.h"

void gsm_connection()
{
    int step = 1;
    int response_check = 3;
    bool network_connect = false;

    while(!network_connect) {
        switch (step)
        {
        case 1:
            while(response_check > 0) {
                send_at_command("ATE0\r\n", 1000); /*Disable echo.*/
                response_check = at_response("ATE0", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 2:
            while(response_check > 0) {
                send_at_command("AT+CIPSHUT\r\n", 3000); /*Deactivate GPRS PDP Context.*/
                response_check = at_response("AT+CIPSHUT", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 3:
            while(response_check > 0) {
                send_at_command("AT+CGATT=1\r\n", 2000); /*Atach to the GPRS network.*/
                response_check = at_response("AT+CGATT=1", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 4:
            while(response_check > 0) {
                send_at_command("AT+CIPMUX=0\r\n", 2000); /*Single IP connection.*/
                response_check = at_response("AT+CIPMUX=0", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 5:
            while(response_check > 0) {
                send_at_command("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"\r\n", 2000); /*Start task and set APN, user name, password.*/
                response_check = at_response("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 6:
            while(response_check > 0) {
                send_at_command("AT+CIICR\r\n", 3000); /*Bring up wireless connection with GPRS or CSD.*/
                response_check = at_response("AT+CIICR", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 7:
            while(response_check > 0) {
                send_at_command("AT+CIFSR\r\n", 4000); /*Get local IP address.*/
                printf("Repeat: %d\r\n", response_check);
                response_check = at_response("AT+CIFSR", response_check);
            }
            if (response_check == 0) {
                printf("Command failed.\r\n");
                /*Set new reset method.*/
                response_check = 3;
                step = 1;
                break;
            }
            else {
                response_check = 3;
                step++;
                break;
            }
        case 8:
            while(response_check > 0) {
                send_at_command("AT+CIPSTART=\"TCP\",\"etransito.vitoria.ifes.edu.br\",\"1883\"\r\n", 4000);
                response_check = at_response("AT+CIPSTART=\"TCP\",\"etransito.vitoria.ifes.edu.br\",\"1883\"", response_check);
            }
            response_check = 3;
            step++;
            break;
        case 9:
            network_connect = true;
            break;
        
        }
    }
}