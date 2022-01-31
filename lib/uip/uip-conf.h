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

/* TODO: implement UDP application; */
// #define UIP_CONF_UDP 1
/* maximum number of UDP connections */
#define UIP_CONF_UDP_CONNS 5

/* maximum tcp connections */
#define UIP_CONF_MAX_CONNECTIONS 2

/* maximum number of listening TCP ports */
#define UIP_CONF_MAX_LISTENPORTS 5

/* maximum number of entries in the ARP table */
#define UIP_CONF_ARPTAB_SIZE 8

/* does not need to be larger than 1500 bytes */
#define UIP_CONF_BUFSIZE 2048

/* for debugging purposes; not used here */
#define UIP_CONF_STATISTICS 0

/* do not log any events */
#define UIP_CONF_LOGGING 0

/* offset in uip_buf where IP header is located (6byte dest mac, 6 byte src mac, 2 eth type) */
/* might be neccessary to be changed if vlan tags or security tags are used */
#define UIP_CONF_LLH_LEN 14

/* ethernet address is set at runtime, not at compile time */
#define UIP_FIXEDETHADDR 0


/* register a callback function that is called by the uIP stack to handle incoming IP packets */
/* this function is usually invoked when uip_input() is called in the main application */
/* uip_callback(void) has to be implemented; this is just a function prototype */
#define UIP_APPCALL uip_callback
void uip_callback(void);

/* uip_tcp_appstate_t is a global memory for the state of our custom tcp_application */
typedef u16_t uip_tcp_appstate_t;

/* uip_tcp_appstate_t is a global memory for the state of our custom udp_application */
typedef u16_t uip_udp_appstate_t;

/* tell uIP that a buffer for ethernet frames is created in main applications */
#define UIP_CONF_EXTERNAL_BUFFER 1
//extern u8_t *uip_buf;

#endif
