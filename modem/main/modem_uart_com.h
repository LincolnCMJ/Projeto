#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "string.h"
#include "driver/uart.h"
#include "driver/gpio.h"

static const char *TAG0 = "UART";

static const int uart_buffer_size = (1024 * 2);

#define UART UART_NUM_2
#define RX GPIO_NUM_16
#define TX GPIO_NUM_17

void init_uart() {
    uart_driver_install(UART, uart_buffer_size, 0, 0, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));

    // UART configurations
    uart_config_t uart_config = {
        .baud_rate = 115200, // UART velocity (baud rate)
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART, &uart_config);
    
    uart_set_pin(UART, TX, RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uart_set_mode(UART, UART_MODE_RS485_HALF_DUPLEX); // Disable loopback
}

void send_at_command(const char *data_to_send) {
    uart_write_bytes(UART, data_to_send, strlen(data_to_send));
}

void receive() {
    char data_received[1024];
    int length = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART, (size_t*)&length));
    length = uart_read_bytes(UART, data_received, length, pdMS_TO_TICKS(500));
    if (length > 0) {
        data_received[length] = 0; // Add a string terminator
        ESP_LOGI(TAG0, "Receive: %s", data_received);
        uart_flush(UART);
    }
}