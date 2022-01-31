/*
 * @author: David Pernerstorfer <es20m012@technikum-wien.at>
 * @created: 2022-01-26
 * @about: driver for uDMA peripheral eth_frame. the uDMA peripheral communicates
           with the 1G ethernet mac. ethernet frames are transmitted to eth mac
           via fifos.
 */
#include <stdio.h>
#include <pulp.h>
#include <stdint.h>
#include <string.h>
#include <eth_frame.h>

void init_udma_eth_frame() {
  /* enable clock for udma peripheral */
  plp_udma_cg_set(plp_udma_cg_get() | (1<<PER_ID_ETH_FRAME));
}


uint8_t enqueue_udma_tx(void *tx_buffer, uint32_t size_bytes) {
  /* set source start address for udma tx transaction */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_TX_SADDR, (uint32_t)tx_buffer);

  /*  set number of bytes to transfer */
  /* tx_buffer_size means word size (16 bit), therefore multiply by 2 */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_TX_SIZE, size_bytes);

  /* tell udma_ethernet_frame how many bytes to transfer; used for fifo counter */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_TX_BYTES, size_bytes);

  /* TX_CFG register bits (see pulpissimo/doc/datasheet.pdf)
   * bit 0 - CONTINOUS(R/W) - not unused here
   * bit 4 - EN(R/W) - 1=enable and start transfer; 0=disabled
   * bit 5 - PENDING(R) - 1=pending transfer in the queue; 0=no pending transfer in the queue
   * bit 6 - CLR(W) - 1=stop and clear the on-going transfer; 0=disabled
   * other bits are not used
   */
  /* enable tx channel */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_TX_CFG, (1<<4));
}


uint8_t enqueue_udma_rx(void *rx_buffer, uint32_t size_bytes) {
  /* set destination start address for udma rx transaction */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_SADDR, (uint32_t)rx_buffer);

  /*  set number of bytes to transfer */
  /* size in bytes */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_SIZE, size_bytes);

  /* RX_CFG register bits (see pulpissimo/doc/datasheet.pdf)
   * bit 0 - CONTINOUS(R/W) - not unused here
   * bit 4 - EN(R/W) - 1=enable and start transfer; 0=disabled
   * bit 5 - PENDING(R) - 1=pending transfer in the queue; 0=no pending transfer in the queue
   * bit 6 - CLR(W) - 1=stop and clear the on-going transfer; 0=disabled
   * other bits are not used
   */
  /* enable rx channel */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_CFG, (1<<4));
}


void wait_udma_rx_done() {
  /* busy wait until rx transaction finished */
  uint32_t reg_rx_bytes_left;
  do {
    reg_rx_bytes_left = pulp_read32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_SIZE);
  } while (reg_rx_bytes_left != 0);
}


void wait_udma_tx_done() {
  /* busy wait until tx transaction finished */
  uint32_t reg_tx_bytes_left = 0;
  do {
    reg_tx_bytes_left = pulp_read32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_TX_BYTES_LEFT);
  } while (reg_tx_bytes_left > 0);

}


uint8_t eof_received() {
  /* check if full ethernet frame has arrived in uDMA fifo buffer */
  return (pulp_read32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_CFG)>>UDMA_REG_ETH_FRAME_RX_FIFO_CFG_EOF_BIT) & 1;
}

void eof_reset() {
  /* reset end of frame (eof) bit in eth_frame; enables fifo */
  pulp_write32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_CFG, 0);
}

uint32_t eth_frame_rx_size() {
  /* get size of ethernet frame in uDMA fifo buffer*/
  return pulp_read32(UDMA_REG_ETH_FRAME_ADDR_FIRST + UDMA_REG_ETH_FRAME_OFFS_RX_FIFO_N);
}
