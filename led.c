#include <msp430.h>
#include "led.h"

void led_init(void)
{
    P1DIR |= 0x01;
}
void led_toggle(void)
{
    P1OUT ^= 0x01;
}
