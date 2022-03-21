# tmc-minimal-driver

Minimalistic driver library for Trinamic stepper drivers

## Capabilities

This library contains a minimal set of generic functions to configure Trinamic stepper drivers. These functions are:

- get/set rms and hold current
- get/set microstepping
- get/set stealthchop threshold
- get the driver raw status
- get/set driver registers

Further functionalities can be developed around this library by adding custom funtions

## Using tmc-minimal-driver

tmc-minimal-driver exposes a basic struct that allows to read and write registers inside the TMC.

```
    typedef uint8_t (*tmc_getc)(void);
    typedef uint8_t (*tmc_putc)(uint8_t);
    typedef void (*tmc_initdriver)(void);

    typedef struct
    {
        //identifies the type of driver (2208, 2209, 2225, etc...)
        uint8_t type;
        //if the driver has a slave ID this should be set here
        uint8_t slave;
        // Callback for the UART/SPI interface initialization
        tmc_initdriver init;
        // Callback for UART getc. If the driver uses SPI, this callback should disable the CS pin
        tmc_getc read;
        // Callback for UART putc. If the driver uses SPI, this callback should enable the CS pin and transmit a spi byte
        tmc_putc write;
    } tmc_driver_t;
```

To use this on a driver (let's say a TMC2208) you can do it like this:

```
    uint8_t mydriver_putc(uint8_t c){
        //custom code to send byte c via UART (either hardware UART or software UART)
    }

    uint8_t mydriver_getc(void){
        //custom code to get a byte via UART (either hardware UART or software UART)
    }

    void main (void) {
        tmc_driver_t mydriver = {
            .type = 2208;
            .init = NULL; //if no initializtion needed just set to NULL
            .read = &mydriver_getc;
            .write = &mydriver_putc;
        };

        tmc_init(&mydriver);
        tmc_set_current(&mydriver, 800);
        tmc_set_microstep(&mydriver, 16);
    }
```
