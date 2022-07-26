/*
 * @author: David Pernerstorfer <es20m012@technikum-wien.at>
 * @created: 2022-01-26
 * @about: contains compile-time configurations for uIP stack
 * @see: uIP Docu: https://raw.githubusercontent.com/adamdunkels/uip/master/doc/uip-refman.pdf
 * @see: available config params: uipopt.h
 */
#ifndef __UIP_CONF_H__
#define __UIP_CONF_H__

#include <stdint.h>
/* uip uses special types; pulpissimo knows standard integer types */
typedef uint16_t u16_t;
typedef uint8_t u8_t;
typedef uint16_t uip_stats_t;

/*IMPORTANT NOTICE: the following configuration _#define_s were chainged in udpopt.h
 * all other defines are unmodified compared to the original version (version 1.0)
 * #define UIP_FIXEDETHADDR 1
 * #define UIP_FIXEDADDR    1
 */


/* do not use ping for host ip address assignment */
#define UIP_CONF_PINGADDRCONF 0

/* enable udp */
#define UIP_CONF_UDP 1

/* maximum number of UDP connections */
#define UIP_CONF_UDP_CONNS 10

/* udp checksums are not supported by default in uIP */
#define UIP_CONF_UDP_CHECKSUMS 0

/* maximum tcp connections */
#define UIP_CONF_MAX_CONNECTIONS 2

/* maximum number of listening TCP ports */
#define UIP_CONF_MAX_LISTENPORTS 20

/* maximum number of entries in the ARP table */
#define UIP_CONF_ARPTAB_SIZE 8

/* does not need to be larger than 2048 bytes */
#define UIP_CONF_BUFSIZE 8192

/* for debugging purposes; not used here */
#define UIP_CONF_STATISTICS 0

/* do not log any events */
#define UIP_CONF_LOGGING 1

/* offset in uip_buf where IP header is located (6byte dest mac, 6 byte src mac, 2 eth type) */
/* might be neccessary to be changed if vlan tags or security tags are used */
#define UIP_CONF_LLH_LEN 14

/* register a callback function that is called by the uIP stack to handle incoming IP packets */
/* this function is usually invoked when uip_input() is called in the main application */
/* uip_callback(void) has to be implemented; this is just a function prototype */
void uip_callback(void);
#define UIP_APPCALL uip_callback

void uip_udp_callback(void);
#define UIP_UDP_APPCALL uip_udp_callback

/* uip_tcp_appstate_t is a global memory for the state of our custom tcp_application */
typedef u16_t uip_tcp_appstate_t;

/* uip_tcp_appstate_t is a global memory for the state of our custom udp_application */
typedef u16_t uip_udp_appstate_t;

/* tell uIP that a buffer for ethernet frames is created in main applications */
#define UIP_CONF_EXTERNAL_BUFFER 1
//extern u8_t *uip_buf;

/* host ip configuration */
#define UIP_IPADDR0 192
#define UIP_IPADDR1 168
#define UIP_IPADDR2 0
#define UIP_IPADDR3 2

#define UIP_DRIPADDR0 192
#define UIP_DRIPADDR1 168
#define UIP_DRIPADDR2 0
#define UIP_DRIPADDR3 3

#define UIP_NETMASK0 255
#define UIP_NETMASK1 255
#define UIP_NETMASK2 255
#define UIP_NETMASK3 0

/* host mac address confguration */
#define UIP_ETHADDR0 0x20
#define UIP_ETHADDR1 0x00
#define UIP_ETHADDR2 0x00
#define UIP_ETHADDR3 0x00
#define UIP_ETHADDR4 0x00
#define UIP_ETHADDR5 0x00

#endif
