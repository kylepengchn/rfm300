#include "radio.h"
#include <rtconfig.h>

#define DBG_TAG              "cmt_demo"
#define DBG_LVL              DBG_ERROR
#include <rtdbg.h>

#if (PKG_RFM300_CSB_PIN < 0) || (PKG_RFM300_FCSB_PIN < 0)
#error Please specify a valid pin
#endif

#define RF_PACKET_SIZE 32               /* Define the payload size here */

static uint8_t rf_rx_buffer[RF_PACKET_SIZE];   /* RF Rx buffer */
static uint8_t rf_tx_buffer[RF_PACKET_SIZE];   /* RF Tx buffer */

static uint8_t enable_master_flg = RT_TRUE;     /* Master/Slave selection */

static uint16_t rf_recv_count = 0;
static uint16_t rf_send_count = 0;
static uint16_t rf_err_count  = 0;

/* Manages the master operation */
void OnMaster(void)
{
    char str[32];

    switch (RF_Process())
    {
    case RF_IDLE:
    {
        rf_send_count++;
        rf_tx_buffer[0] = (uint8_t)rf_send_count;
        rf_tx_buffer[1] = rf_send_count >> 8;

        RF_StartTx(rf_tx_buffer, RF_PACKET_SIZE, 1000);
        break;
    }
    case RF_TX_DONE:
    {
        LOG_D("send: %d", rf_send_count);
        RF_StartRx(rf_rx_buffer, RF_PACKET_SIZE, 1000);
        break;
    }
    case RF_RX_DONE:
    {
        rf_recv_count++;
        LOG_D("recv: %d", rf_recv_count);
        break;
    }
    case RF_RX_TIMEOUT:
    {
        LOG_D("recv: timeout");
        break;
    }
    case RF_ERROR:
    {
        LOG_D("error: %d", ++rf_err_count);
        break;
    }
    default:
        break;
    }
}

/* Manages the slave operation */
void OnSlave(void)
{
    char str[32];

    switch (RF_Process())
    {
    case RF_IDLE:
    {
        RF_StartRx(rf_rx_buffer, RF_PACKET_SIZE, 0xFFFFFFFF);
        break;
    }
    case RF_RX_DONE:
    {
        rf_recv_count++;
        LOG_D("recv: %d", rf_recv_count);

        CMT2300A_DelayMs(10);

        rf_send_count++;
        rf_tx_buffer[0] = (uint8_t)rf_send_count;
        rf_tx_buffer[1] = rf_send_count >> 8;

        RF_StartTx(rf_tx_buffer, RF_PACKET_SIZE, 1000);

        break;
    }
    case RF_TX_DONE:
    {
        LOG_D("send: %d", rf_send_count);
        break;
    }
    case RF_ERROR:
    {
        LOG_D("error: %d", ++rf_err_count);
        break;
    }
    default:
        break;
    }
}

static void rfm300_thread_entry(void *param)
{
    while (1)
    {
        if (enable_master_flg == RT_TRUE)
        {
            OnMaster();
        }
        else
        {
            OnSlave();
        }
    }
}

static int rfm300_sample_init(void)
{
    rt_thread_t tid;

    RF_Init();
    if (CMT2300A_IsExist() == RT_FALSE)
    {
        LOG_E("CMT2300A not found!");
        return RT_EEMPTY;
    }
    else
    {
        LOG_I("CMT2300A ready");
    }

    tid = rt_thread_create("rfm300_demo", rfm300_thread_entry, RT_NULL,
                           1024, RT_THREAD_PRIORITY_MAX/2, 20);
    if (tid)
    {
        rt_thread_startup(tid);
    }
    
    return 0;
}
INIT_APP_EXPORT(rfm300_sample_init);
