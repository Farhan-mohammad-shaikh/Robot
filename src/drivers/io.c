#include "io.h"
#include "defines.h"


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