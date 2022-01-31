/*
 * @author: David Pernerstorfer <es20m012@technikum-wien.at>
 * @created: 2022-01-26
 * @about: contains register addresses of uDMA peripherals: eth_frame; ptpts_rx and ptptx_tx
 */

#ifndef __ARCHI_UDMA_UDMA_ETH_FRAME__
#define __ARCHI_UDMA_UDMA_ETH_FRAME__

#include <stdint.h>

#define PER_ID_ETH_FRAME 17
#define PER_ID_PTP_TS_RX 18
#define PER_ID_PTP_TS_TX 19

// first address of the udma config registers for the udma peripheral "eth_frame"
// ARCHI_SOC_PERIPHERALS_ADDR + \\  // base address of soc periphers (udma is contained in this address space) (see memory_map.h)
// ARCHI_UDMA_OFFSET + \ // address offset of udma within address space of soc peripherals
// UDMA_FIRST_CHANNEL_OFFSET + \ // the initial udma registers are for general udma configuration (glock gate enable, event envale, etc.)
// (PER_ID_ETH_FRAME)*0x80 \ // for each udma peripheral 32 registers (128 byte) are reserved
#define UDMA_REG_ETH_FRAME_ADDR_FIRST (ARCHI_SOC_PERIPHERALS_ADDR + ARCHI_UDMA_OFFSET + UDMA_FIRST_CHANNEL_OFFSET + (PER_ID_ETH_FRAME)*0x80)

#define UDMA_REG_ETH_FRAME_OFFS_RX_SADDR 0x00
#define UDMA_REG_ETH_FRAME_OFFS_RX_SIZE  0x04
#define UDMA_REG_ETH_FRAME_OFFS_RX_CFG   0x08

#define UDMA_REG_ETH_FRAME_OFFS_TX_SADDR 0x10
#define UDMA_REG_ETH_FRAME_OFFS_TX_SIZE  0x14
#define UDMA_REG_ETH_FRAME_OFFS_TX_CFG   0x18

#define UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_CFG       0x1C
#define UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_N         0x20
#define UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_FULL      0x24

#define UDMA_REG_ETH_FRAME_OFFS_TX_BYTES          0x28
#define UDMA_REG_ETH_FRAME_OFFS_TX_BYTES_LEFT     0x2C

#define UDMA_REG_ETH_FRAME_RX_FIFO_CFG_EOF_BIT    0x01
#define UDMA_REG_ETH_FRAME_RX_FIFO_FULL_FULL_BIT  0x00


/* PTP timestamp RX register addresses */
#define UDMA_REG_PTPTSRX_ADDR_FIRST (ARCHI_SOC_PERIPHERALS_ADDR + ARCHI_UDMA_OFFSET + UDMA_FIRST_CHANNEL_OFFSET + (PER_ID_PTP_TS_RX)*0x80)

#define UDMA_REG_PTPTSRX_OFFS_RX_SADDR 0x00
#define UDMA_REG_PTPTSRX_OFFS_RX_SIZE  0x04
#define UDMA_REG_PTPTSRX_OFFS_RX_CFG   0x08

#define UDMA_REG_PTPTSRX_OFFS_RX_FIFO_CFG       0x1C
#define UDMA_REG_PTPTSRX_OFFS_RX_FIFO_N         0x20

#define UDMA_REG_PTPTSRX_RX_FIFO_FULL_BIT  0x02

/* PTP timestamp TX register addresses */
#define UDMA_REG_PTPTSTX_ADDR_FIRST (ARCHI_SOC_PERIPHERALS_ADDR + ARCHI_UDMA_OFFSET + UDMA_FIRST_CHANNEL_OFFSET + (PER_ID_PTP_TS_TX)*0x80)

#define UDMA_REG_PTPTSTX_OFFS_RX_SADDR 0x00
#define UDMA_REG_PTPTSTX_OFFS_RX_SIZE  0x04
#define UDMA_REG_PTPTSTX_OFFS_RX_CFG   0x08

#define UDMA_REG_PTPTSTX_OFFS_RX_FIFO_CFG       0x1C
#define UDMA_REG_PTPTSTX_OFFS_RX_FIFO_N         0x20

#define UDMA_REG_PTPTSTX_RX_FIFO_FULL_BIT  0x02




/* function prototypes; see eth_frmae.c for documentation*/
void init_udma_eth_frame();
uint8_t enqueue_udma_tx(void *tx_buffer, uint32_t size_bytes);
uint8_t enqueue_udma_rx(void *rx_buffer, uint32_t size_bytes);
void wait_udma_rx_done();
void wait_udma_tx_done();
uint8_t eof_received();
void eof_reset();
uint32_t eth_frame_rx_size();


#endif
