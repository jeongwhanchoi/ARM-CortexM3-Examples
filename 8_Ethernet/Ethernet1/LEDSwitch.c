//Ethernet Example

#include <RTL.h>
#include "LPC17xx.H"
#include "LED.h"

U8 socket_tcp;
U8 socket_udp;

#define PORT_NUM 1001
#define BLINKLED 0x01  

static void init () {
   LED_init (); //LED initialization                         
   init_TcpNet ();	//Ethernet initialization
}

void procrec (U8 *buf) {
   switch (buf[0]) {
      case BLINKLED:
	  		LED_out(~buf[1]);
	  		LED_out(buf[1]);
         break;
   }
}

U16 udp_callback (U8 soc, U8 *rip, U16 rport, U8 *buf, U16 len) {
   rip  = rip;
   rport= rport;
   len  = len;

   if (soc != socket_udp) {
      return (0);
   }

   procrec(buf);
   return (0);
}

U16 tcp_callback (U8 soc, U8 evt, U8 *ptr, U16 par) {

   par = par;

   if (soc != socket_tcp) {
      return (0);
   }

   switch (evt) {
      case TCP_EVT_DATA:
         procrec(ptr);
         break;

      case TCP_EVT_CONREQ:
         return (1);

      case TCP_EVT_CONNECT:
         return (1);
   }
   return (0);
}

int main (void) {
   
   SystemInit(); 

   init ();

   socket_udp = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
   if (socket_udp != 0) {
      udp_open (socket_udp, PORT_NUM);
   }

   socket_tcp = tcp_get_socket (TCP_TYPE_SERVER, 0, 10, tcp_callback);
   if (socket_tcp != 0) {
      tcp_listen (socket_tcp, PORT_NUM);
   }

   while (1) {
      main_TcpNet ();
   }
}
