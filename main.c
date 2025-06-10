#include <msp430.h>
#include "led.h"
#include "drive.h"
#include "i2c.h"

int main(void)
{   
    volatile unsigned int i;
    
    WDTCTL = WDTPW | WDTHOLD;
    led_init();
    drive_init();
    i2c_init();

    while (1)
    {
        led_toggle();
        for (i = 10000; i != 0; i--);
    }
}
