
#include <stdio.h>

#include <pico/binary_info.h>
#include <pico/stdlib.h>

#ifdef RASPBERRYPI_PICO_W
#include <pico/cyw43_arch.h>
#endif

#if defined(PICO_DEFAULT_LED_PIN)
#warning using built in LED
void init_led() {
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

void set_led(bool state) {
	gpio_put(PICO_DEFAULT_LED_PIN, state);
}
#elif defined(RASPBERRYPI_PICO_W)
#warning using picow LED

void init_led() {
	cyw43_arch_init();
}

void set_led(bool state) {
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}
#else
#warning no LED available
void init_led() {
}

void set_led(bool state) {
}
#endif

int main() {
	bi_decl(bi_program_description("template raspberry pi pico c++ project"));

	stdio_init_all();

	init_led();
	uint32_t count = 1;

	while (true) {
		set_led(count & 1);
		printf("%d\n", count);
		sleep_ms(100);
		count++;
	}
}
