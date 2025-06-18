#include "io.h"
#include "defines.h"
#include <stdint.h>
#include <msp430.h>
#include <stddef.h>


#define IO_PORT_OFFSET (3u)
#define IO_PORT_MASK (0x3u << IO_PORT_OFFSET)
#define IO_PIN_MASK (0x7u)

#if defined(LAUNCHPAD)
#define IO_PORT_CNT (2u)
#elif defined(NSUMO)
#define IO_PORT_CNT (3u)
#endif
#define IO_PIN_CNT_PER_PORT (8u)
// Port 3 is not interrupt capable
#define IO_INTERRUPT_PORT_CNT (2u)

 uint8_t io_port(io_e io)
{
    return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}

 inline uint8_t io_pin_idx(io_e io)
{
    return io & IO_PIN_MASK;
}

 uint8_t io_pin_bit(io_e io)
{
    return 1 << io_pin_idx(io);
}


#if defined(LAUNCHPAD)
static volatile uint8_t *const port_dir_regs[IO_PORT_CNT] = { &P1DIR, &P2DIR };
static volatile uint8_t *const port_ren_regs[IO_PORT_CNT] = { &P1REN, &P2REN };
static volatile uint8_t *const port_out_regs[IO_PORT_CNT] = { &P1OUT, &P2OUT };
static volatile uint8_t *const port_in_regs[IO_PORT_CNT] = { &P1IN, &P2IN };
static volatile uint8_t *const port_sel1_regs[IO_PORT_CNT] = { &P1SEL, &P2SEL };
static volatile uint8_t *const port_sel2_regs[IO_PORT_CNT] = { &P1SEL2, &P2SEL2 };
#elif defined(NSUMO)
static volatile uint8_t *const port_dir_regs[IO_PORT_CNT] = { &P1DIR, &P2DIR, &P3DIR };
static volatile uint8_t *const port_ren_regs[IO_PORT_CNT] = { &P1REN, &P2REN, &P3REN };
static volatile uint8_t *const port_out_regs[IO_PORT_CNT] = { &P1OUT, &P2OUT, &P3OUT };
static volatile uint8_t *const port_in_regs[IO_PORT_CNT] = { &P1IN, &P2IN, &P3IN };
static volatile uint8_t *const port_sel1_regs[IO_PORT_CNT] = { &P1SEL, &P2SEL, &P3SEL };
static volatile uint8_t *const port_sel2_regs[IO_PORT_CNT] = { &P1SEL2, &P2SEL2, &P3SEL2 };
#endif

// static volatile uint8_t *const port_interrupt_flag_regs[IO_INTERRUPT_PORT_CNT] = { &P1IFG, &P2IFG };
// static volatile uint8_t *const port_interrupt_enable_regs[IO_INTERRUPT_PORT_CNT] = { &P1IE, &P2IE };
// static volatile uint8_t *const port_interrupt_edge_select_regs[IO_INTERRUPT_PORT_CNT] = { &P1IES,
//                                                                                           &P2IES };


void io_set_select(io_e io, io_select_e select)
{
    const uint8_t port = io_port(io);
    const uint8_t pin = io_pin_bit(io);
    switch (select) {
    case IO_SELECT_GPIO:
        *port_sel1_regs[port] &= ~pin;
        *port_sel2_regs[port] &= ~pin;
        break;
    case IO_SELECT_ALT1:
        *port_sel1_regs[port] |= pin;
        *port_sel2_regs[port] &= ~pin;
        break;
    case IO_SELECT_ALT2:
        *port_sel1_regs[port] &= ~pin;
        *port_sel2_regs[port] |= pin;
        break;
    case IO_SELECT_ALT3:
        *port_sel1_regs[port] |= pin;
        *port_sel2_regs[port] |= pin;
        break;
    }
}

void io_set_direction(io_e io, io_dir_e dir)
{

   const uint8_t port = io_port(io);
   const uint8_t pin = io_pin_bit(io);
   switch (dir) {
   case IO_DIR_INPUT:
      *port_dir_regs[port] &= ~pin; // Set pin as input
      break;
   case IO_DIR_OUTPUT:     
      *port_dir_regs[port] |= pin; // Set pin as output
      break;
   }
}


void io_set_resistor(io_e io, io_resistor_e resistor)
{
   const uint8_t port = io_port(io);
   const uint8_t pin = io_pin_bit(io);
   switch (resistor) {
   case IO_RESISTOR_DISABLED:
      *port_ren_regs[port] &= ~pin; // Disable pull-up/pull-down resistor
      break;
   case IO_RESISTOR_ENABLED:
      *port_ren_regs[port] |= pin; // Enable pull-up/pull-down resistor
      break;
   }
}
void io_set_out(io_e io, io_out_e output)
{
   const uint8_t port = io_port(io);
   const uint8_t pin = io_pin_bit(io);
   switch (output) {
   case IO_OUT_LOW:
      *port_out_regs[port] &= ~pin; // Set pin low (pull-down)
      break;
   case IO_OUT_HIGH:
      *port_out_regs[port] |= pin; // Set pin high (pull-up)
      break;
   }
}

io_in_e io_get_input(io_e io)
{
  return (*port_in_regs[io_port(io)] & io_pin_bit(io)) ? IO_IN_HIGH : IO_IN_LOW;
}