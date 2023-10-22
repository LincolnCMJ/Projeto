#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define IN1 GPIO_NUM_21
#define IN2 GPIO_NUM_4
#define IN3 GPIO_NUM_19
#define IN4 GPIO_NUM_18

void stepMotor(int step) {
    switch (step)
    {
    case 0:
        gpio_set_level(IN1, 1);
        gpio_set_level(IN2, 0);
        gpio_set_level(IN3, 1);
        gpio_set_level(IN4, 0);
        break;
    case 1:
        gpio_set_level(IN1, 0);
        gpio_set_level(IN2, 1);
        gpio_set_level(IN3, 1);
        gpio_set_level(IN4, 0);
        break;
    case 2:
        gpio_set_level(IN1, 0);
        gpio_set_level(IN2, 1);
        gpio_set_level(IN3, 0);
        gpio_set_level(IN4, 1);
        break;
    case 3:
        gpio_set_level(IN1, 1);
        gpio_set_level(IN2, 0);
        gpio_set_level(IN3, 0);
        gpio_set_level(IN4, 1);
        break;
    }
}

void app_main() {
    int step_number = 0;
    int direction = 0;
    int number_of_steps = 32;
    int speed = 500;

    esp_rom_gpio_pad_select_gpio(IN1);
    gpio_set_direction(IN1, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(IN2);
    gpio_set_direction(IN2, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(IN3);
    gpio_set_direction(IN3, GPIO_MODE_OUTPUT);
    
    esp_rom_gpio_pad_select_gpio(IN4);
    gpio_set_direction(IN4, GPIO_MODE_OUTPUT);

    int step_delay = 60L * 1000L * 1000L / number_of_steps/ speed;

    int steps_to_move = -500;

    int steps_left = abs(steps_to_move);

    if (steps_to_move > 0) {direction = 1;}
    else {direction = 0;}

    while (1) {
        //printf("Teste: %d\r\n", step_delay);
        if (direction == 1) {
            step_number++;
            if (step_number == number_of_steps) {
                step_number = 0;
            }
        }
        else {
            if (step_number == 0) {
                step_number = number_of_steps;
            }
            step_number--;
        }
        steps_left--;
        int sequence = step_number % 4;
        printf("Teste: %d\r\n", sequence);
        stepMotor(sequence);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}