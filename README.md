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
4. For the initialization sequence and example code, refer to `main.c`.

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
- STM32CubeIDE or any other compatible IDE for STM32 development
- ARM-CMSIS library

## License
This project is licensed under the MIT License.
