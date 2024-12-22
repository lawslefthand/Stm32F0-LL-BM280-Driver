/*
 *
 * bmp280_spi.h
 *
 *  Created on: Dec 15, 2024
 *      Author: danba
 */

#ifndef SRC_BMP280_SPI_H_
#define SRC_BMP280_SPI_H_

void bmp_spi_rcc_config(void);
void bmp_spi_gpio_config(void);
void bmp_spi_config(void);
uint8_t bmp_spi_read(uint8_t reg_addr);
double spi_temperature(int x);
double spi_pressure(void);
double spi_altitude(void);
void delay_1s_spi(void);
void nss_pu(void);

#endif /* SRC_BMP280_SPI_H_ */
