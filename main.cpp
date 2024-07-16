#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "one_wire.h"

#define TEMP_SENSE_GPIO_PIN 10
#define GREEN_LED_GPIO_PIN 4
#define ORANGE_LED_GPIO_PIN 7
#define RED_LED_GPIO_PIN 13

int main() {
    stdio_init_all();

    //ONE WIRE
    One_wire one_wire(TEMP_SENSE_GPIO_PIN);
    one_wire.init();
    rom_address_t address{};

    //LEDS
    gpio_init(GREEN_LED_GPIO_PIN);
    gpio_init(ORANGE_LED_GPIO_PIN);
    gpio_init(RED_LED_GPIO_PIN);

    gpio_set_dir(GREEN_LED_GPIO_PIN, GPIO_OUT);
    gpio_set_dir(ORANGE_LED_GPIO_PIN, GPIO_OUT);
    gpio_set_dir(RED_LED_GPIO_PIN, GPIO_OUT);

    // gpio_put(GREEN_LED_GPIO_PIN, 1);
    // gpio_put(ORANGE_LED_GPIO_PIN, 1); 
    // gpio_put(RED_LED_GPIO_PIN, 1);

    double temp = 0;

    while (true)
    {
        one_wire.single_device_read_rom(address);
        one_wire.convert_temperature(address, true, false);
        temp = one_wire.temperature(address);

        printf("Temperature: %3.1foC\n", temp);

        if(temp>32)  gpio_put(RED_LED_GPIO_PIN, 1);
        else  gpio_put(RED_LED_GPIO_PIN, 0);

        if(temp>31)  gpio_put(ORANGE_LED_GPIO_PIN, 1);
        else gpio_put(ORANGE_LED_GPIO_PIN, 0);

        if(temp > 30) gpio_put(GREEN_LED_GPIO_PIN, 1);
        else gpio_put(GREEN_LED_GPIO_PIN, 0);
        
        sleep_ms(1000);
    }
    return 0;
}
