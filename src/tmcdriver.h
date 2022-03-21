/*
    Name: tmcdriver.h
    Description: Minimalistic generic driver library for Trinamic stepper drivers.

    Copyright: Copyright (c) João Martins
    Author: João Martins
    Date: 21-03-2022

    µCNC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version. Please see <http://www.gnu.org/licenses/>

    µCNC is distributed WITHOUT ANY WARRANTY;
    Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the	GNU General Public License for more details.
*/

#ifndef TMCDRIVER_H
#define TMCDRIVER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define GCONF 0x00
#define IHOLD_IRUN 0x10
#define CHOPCONF 0x6C
#define TPWMTHRS 0X13
#define DRV_STATUS 0x6F

    typedef uint8_t (*tmc_getc)(void);
    typedef uint8_t (*tmc_putc)(uint8_t);
    typedef void (*tmc_initdriver)(void);

    typedef struct
    {
        // identifies the type of driver (2208, 2209, 2225, etc...)
        uint8_t type;
        // if the driver has a slave ID this should be set here
        uint8_t slave;
        // Callback for the UART/SPI interface initialization
        tmc_initdriver init;
        // Callback for UART getc. If the driver uses SPI, this callback should disable the CS pin
        tmc_getc read;
        // Callback for UART putc. If the driver uses SPI, this callback should enable the CS pin and transmit a spi byte
        tmc_putc write;
    } tmc_driver_t;

    void tmc_init(tmc_driver_t *driver);
    float tmc_get_current(tmc_driver_t *driver, float rsense);
    void tmc_set_current(tmc_driver_t *driver, float current, float rsense, float ihold_mul);
    uint8_t tmc_get_microstep(tmc_driver_t *driver);
    void tmc_set_microstep(tmc_driver_t *driver, uint8_t ms);
    uint32_t tmc_get_stealthshop(tmc_driver_t *driver);
    void tmc_set_stealthshop(tmc_driver_t *driver, uint32_t value);
    uint32_t tmc_get_status(tmc_driver_t *driver);
    uint32_t tmc_read_register(tmc_driver_t *driver, uint8_t address);
    uint32_t tmc_write_register(tmc_driver_t *driver, uint8_t address, uint32_t val);

#ifdef __cplusplus
}
#endif

#endif
