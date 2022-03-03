#ifndef __CMT_PORT_H__
#define __CMT_PORT_H__

#include <stdint.h>

void cmt_port_init(char *dev_name, char *fifo_name, char *bus_name, int csb_pin, int fcsb_pin);

void cmt_port_write(uint8_t addr, uint8_t dat);
void cmt_port_read(uint8_t addr, uint8_t* p_dat);

void cmt_port_write_fifo(const uint8_t* p_buf, uint16_t len);
void cmt_port_read_fifo(uint8_t* p_buf, uint16_t len);

#endif
