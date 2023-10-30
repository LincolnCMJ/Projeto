static const char *TAG0 = "UART";

static const int uart_buffer_size = (1024 * 2);

#define UART UART_NUM_2
#define RX GPIO_NUM_16
#define TX GPIO_NUM_17

void init_uart()
{
    uart_driver_install(UART, uart_buffer_size, 0, 0, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));

    /*
     * UART configurations
     */
    uart_config_t uart_config = {
        .baud_rate = 115200, // UART velocity (baud rate)
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_param_config(UART, &uart_config);    
    uart_set_pin(UART, TX, RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_set_mode(UART, UART_MODE_RS485_HALF_DUPLEX); // Disable loopback
}

void send_at_command(const char *data_to_send, int wait_time)
{
    uart_write_bytes(UART, data_to_send, strlen(data_to_send));
    printf("AT Command: %s", data_to_send);
    vTaskDelay(pdMS_TO_TICKS(wait_time));
}

int at_response(const char *command_check, int cont)
{
    char data_received[1024];
    int length = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART, (size_t*)&length));
    length = uart_read_bytes(UART, data_received, length, pdMS_TO_TICKS(500));
    if (length > 0) {
        data_received[length] = '\0';
        ESP_LOGI(TAG0, "Receive: %s\r\n Length: %d\r\n", data_received, length);

        /*
         * Check routine
         */
        if (strstr(command_check, "AT+CIFSR")) { // Check the IP connection.
            if ((length < 11) || length > 19) {
                uart_flush(UART);
                cont--;
                return cont;
            }
            cont = -1;
            return cont;
        }
    }
    uart_flush(UART);
    cont = -1;
    return cont;
}