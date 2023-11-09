#define   OUT3  GPIO_NUM_27
#define   OUT1  GPIO_NUM_26
#define   OUT2  GPIO_NUM_25
#define   OUT0  GPIO_NUM_33

#define   BT1   GPIO_NUM_19

#define VEL 10

bool keep = 1;

void Task1() {
    static char step = 1;

    while(1) {
	    switch(step) {
        case 1:
            gpio_set_level(OUT3, 1);
            gpio_set_level(OUT2, 0);
            gpio_set_level(OUT1, 0);
            gpio_set_level(OUT0, 1);
            break;
        case 2:
            gpio_set_level(OUT3, 1);
            gpio_set_level(OUT2, 0);
            gpio_set_level(OUT1, 1);
            gpio_set_level(OUT0, 0);
            break;
        case 3:
            gpio_set_level(OUT3, 0);
            gpio_set_level(OUT2, 1);
            gpio_set_level(OUT1, 1);
            gpio_set_level(OUT0, 0);
            break;
        case 4:
            gpio_set_level(OUT3, 0);
            gpio_set_level(OUT2, 1);
            gpio_set_level(OUT1, 0);
            gpio_set_level(OUT0, 1);
        }

        step++;
        if (step > 4) {
            step = 1;
        }
        vTaskDelay(pdMS_TO_TICKS(VEL));
    }
}

// void read_bts() {
//     if (gpio_get_level(BT1)) {
// 	    printf("APERTOU");
//     }
// }

// void Task2() {
//     while(1) {
//         read_bts();
//         vTaskDelay(200/portTICK_PERIOD_MS);
//     }
// }


void lock(void) {
    esp_rom_gpio_pad_select_gpio(OUT3);
    gpio_set_direction(OUT3, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(OUT2);
    gpio_set_direction(OUT2, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(OUT1);
    gpio_set_direction(OUT1, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(OUT0);
    gpio_set_direction(OUT0, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(BT1);
    gpio_set_direction(BT1, GPIO_MODE_INPUT);

    xTaskCreate(&Task1, "t1", 4096, NULL, 5, NULL);
    // xTaskCreate(&Task2, "t2", 2048, NULL, 1, NULL);  
}