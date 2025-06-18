#include "io.h"
#include "defines.h"
#include <stdint.h>


#define IO_PORT_OFFSET (3u)
#define IO_PORT_MASK (0x3u << IO_PORT_OFFSET)
#define IO_PIN_MASK (0x7u)

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


void io_set_select(io_e io, io_select_e select)
{
   unused (io);
   unused (select);
}

void io_set_direction(io_e io, io_dir_e dir)
{
   unused (io);
   unused (dir);
}
void io_set_resistor(io_e io, io_resistor_e resistor)
{
   unused (io);
   unused (resistor);
}
void io_set_out(io_e io, io_out_e output)
{
   unused (io);
   unused (output);
}

io_in_e io_get_input(io_e io)
{
   unused (io);
   return IO_IN_LOW; // Default return value, adjust as needed
}