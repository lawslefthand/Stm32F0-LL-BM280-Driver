# BMP280 Dual Mode Driver (I2C/SPI) for STM32 Nucleo F0 Boards

This is a dual-mode driver for the BMP280 sensor, supporting both I2C and SPI communication interfaces. Written using the ARM-CMSIS standard, the driver provides complete Low-Level (LL) support and control for the BMP280 on STM32 Nucleo F0 boards.

## Features
- Supports both I2C and SPI communication modes
- ARM-CMSIS standard-based driver implementation
- Complete LL support for controlling the BMP280 sensor
- Configurable I2C and SPI parameters for optimal performance
- Compatible with STM32 Nucleo F0 series boards

## Usage
1. Download or clone this repository.
2. Add the driver files to the `src` folder of your STM32CubeIDE project.
3. Initialize the driver in your main application code and configure the sensor according to your desired mode (I2C or SPI).
4. **Important**: To ensure proper initialization settings take effect, follow these steps:
   - First, initialize the BMP280 in **I2C mode** by uploading the i2c driver. This configures the initialization settings of the sensor.
   - Once I2C mode is initialized and the configuration is complete, switch to **SPI mode** and upload the spi driver for normal operation  (will be fixed later).
5. For the initialization sequence and example code, refer to initialization.

## Connection Table

### I2C Connection (Nucleo F0 board)
| BMP280 Pin | STM32 Pin      | Function  |
|------------|----------------|-----------|
| VDD        | 3.3V           | Power     |
| GND        | GND            | Ground    |
| SCL        | PB6 (I2C1 SCL) | Clock     |
| SDA        | PB7 (I2C1 SDA) | Data      |

### SPI Connection (Nucleo F0 board)
| BMP280 Pin | STM32 Pin      | Function  |
|------------|----------------|-----------|
| VDD        | 3.3V           | Power     |
| GND        | GND            | Ground    |
| SCK        | PA5 (SPI1 SCK) | Clock     |
| SDI        | PA6 (SPI1 MISO)| MISO      |
| SDO        | PA7 (SPI1 MOSI)| MOSI      |
| CS         | PA4 (SPI1 NSS) | Chip Select |

## Known Bugs
- **I2C Communication Issue**: For certain defective HW-611 BMP280 boards, the sensor may not update temperature and pressure under certain I2C configurations due to hardware limitations. To overcome this, you need to use Adafruit's I2C driver first in the Arduino IDE and then apply this driver in STM32CubeIDE. This workaround resolves issues with the defective boards and ensures proper operation.

## Dependencies
- STM32CubeIDE
- ARM-CMSIS Headers

## License
This project is licensed under the MIT License.

## Initialization 

```c
//Example sequence for i2c init
/*

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "stm32f030x8.h"
#include "bmp280_i2c.h"
#include "usart.h"

int main() {

	usart_gpio_init();
	usart_init();
	bmp_rcc_config();
	bmp_gpio_config();
	bmp_i2c_config();

	while (1) {

//init config settings
	bmp_i2c_write(0xF5, CONFIG_SETTING);
	bmp_i2c_write(0xF4, CTRL_MEAS_SETTING);


		double temp = 0;
		double press = 0;

		temp = temperature(0);
		press = pressure();

		printf("temp %f\n", temp);
		printf("press %f\n", press);

		delay_1s_spi();

	}

}
*/



//Example sequence for spi init
/*
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

		//bmp_spi_write(0b01110101,0x00);
		//bmp_spi_write(0b01110100,0xFF);


		double temp = 0;
		double press = 0;

		temp = spi_temperature(0);
		press = spi_pressure();

		printf("temp %f\n", temp);
		printf("press %f\n", press);

		delay_1s_spi();

	}

}
*/

```
