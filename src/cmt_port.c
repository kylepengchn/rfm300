#include "cmt_port.h"
#include "rtdevice.h"

#define DBG_TAG              "cmt_port"
#define DBG_LVL              DBG_ERROR
#include <rtdbg.h>


static struct rt_spi_device dev_rfm300;
static struct rt_spi_device dev_rfm300_fifo;

void cmt_port_init(char *dev_name, char *fifo_name, char *bus_name, int csb_pin, int fcsb_pin)
{
    rt_err_t ret;
    struct rt_spi_configuration cfg;

    /* control */
    ret = rt_spi_bus_attach_device(&dev_rfm300, dev_name, bus_name, (void *)csb_pin);
    if (ret != RT_EOK)
    {
        LOG_E("cant`t attch %s device to %s bus", dev_name, bus_name);
        return;
    }

    cfg.data_width = 8;
    cfg.max_hz = 1 * 1000 * 1000;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MSB | RT_SPI_MODE_0 | RT_SPI_3WIRE;
    rt_spi_configure(&dev_rfm300, &cfg);

    rt_pin_mode(csb_pin, PIN_MODE_OUTPUT);
    rt_pin_write(csb_pin, PIN_HIGH);

    /* fifo */
#if 0
    rt_size_t len1 = rt_strlen(dev_name);
    rt_size_t len = rt_strlen("fifo") + len1 + 1;
    char *fifo_name = (char *)rt_malloc(len);
    if (!fifo_name)
    {
        LOG_E("can`t create '%sfifo' name", dev_name);
        return;
    }
    
    rt_memset(fifo_name, '\0', len);
    rt_strncpy(fifo_name, dev_name, len1);
    rt_strncpy(fifo_name + len1, "fifo", rt_strlen("fifo"));
    ret = rt_spi_bus_attach_device(dev_rfm300_fifo, fifo_name, bus_name, (void *)fcsb_pin);
    rt_free(fifo_name);
#else
    ret = rt_spi_bus_attach_device(&dev_rfm300_fifo, fifo_name, bus_name, (void *)fcsb_pin);
#endif
    if (ret != RT_EOK)
    {
        LOG_E("cant`t attch %s device to %s bus", fifo_name, bus_name);
        return;
    }

    cfg.data_width = 8;
    cfg.max_hz = 1 * 1000 * 1000;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MSB | RT_SPI_MODE_0 | RT_SPI_3WIRE;;
    rt_spi_configure(&dev_rfm300_fifo, &cfg);

    rt_pin_mode(fcsb_pin, PIN_MODE_OUTPUT);
    rt_pin_write(fcsb_pin, PIN_HIGH);
}

void cmt_port_write(uint8_t addr, uint8_t dat)
{
    addr &= 0x7F;
    rt_spi_send_then_send(&dev_rfm300, &addr, 1, &dat, 1);
}

void cmt_port_read(uint8_t addr, uint8_t* p_dat)
{
    addr |= 0x80;
    rt_spi_send_then_recv(&dev_rfm300, &addr, 1, p_dat, 1);
}

void cmt_port_write_fifo(const uint8_t* p_buf, uint16_t len)
{
    rt_spi_send(&dev_rfm300_fifo, p_buf, len);
}

void cmt_port_read_fifo(uint8_t* p_buf, uint16_t len)
{
    rt_spi_recv(&dev_rfm300_fifo, p_buf, len);
}
