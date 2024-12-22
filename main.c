#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "stm32f030x8.h"
#include "bmp280_spi.h"
#include "usart.h"

int main() {

	usart_gpio_init();
	usart_init();
	bmp_spi_rcc_config();
	bmp_spi_gpio_config();
	bmp_spi_config();

	while (1) {

		double temp = 0;
		double press = 0;

		//temp = spi_temperature(0);
		press = spi_pressure();

		//printf("temp %f\n", temp);
		printf("press %f\n", press);

		delay_1s_spi();

	}

}
