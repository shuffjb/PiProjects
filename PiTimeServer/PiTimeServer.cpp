/*-------------------------------------------------------------------*/
/* PiTimeServer - Send NMEA Sentences thru USB to Arduino.           */
/*                Use system time for now since it is synched to     */
/*                NTP Servers on startup when connected to internet  */
/* 2021-01-09 JBS Created                                            */
/* 2021-02-07 JBS Updated comments and library info                  */
/*                                                                   */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Notes on Libraries:                                               */
/*  Uses rs232 libraries from Teunis van Beelen                      */
/*  http://www.teuniz.net/RS-232/                                    */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Notes for finding tty ports:                                      */
/*   ls /dev/tty*  shows all tty ports.  when you plug in a usb      */
/*                 a new tty port is created.  do the ls, then       */
/*                 plug in, do the ls again                          */
/*   lsusb lsusb   shows all connected USB devices (not their tty)   */
/*                                                                   */
/*-------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "PiTimeServer.h"
#include "rs232.h"

#define BUF_SIZE 128

int main()
{
  int i=0;
  int nMessages=0;  /* count messages printed */
  int cport_nr=24;  /* /dev/ttyACM0 */
  int bdrate=4800;  /* 4800 baud for stability */
  int flwcntrl=0;   /* Flow Controll off  */

  time_t curUTC;
  struct tm * wrkTime;
  char nmea_buff[BUF_SIZE];
  char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
  char str_send[2][BUF_SIZE]; // send data buffer
  //unsigned char str_recv[BUF_SIZE]; // recv data buffer
  strcpy(str_send[0], "This is a test string.");
  strcpy(str_send[1], "This is another test string.");

  /* Get the current time. */
  time (&curUTC);
  wrkTime = gmtime(&curUTC);
  i = i + 0;  // kill warning
  
  strftime(nmea_buff, BUF_SIZE, "%H%M%S", wrkTime);
  printf("%s\n", nmea_buff);
  
  if(RS232_OpenComport(cport_nr, bdrate, mode, flwcntrl))
  {
    printf("Can not open comport\n");
    return(0);
  }

  usleep(2000000);  /* waits 2000ms for stable condition */
  while(1)
  {
    /* Get the current time. */
    time (&curUTC);
    wrkTime = gmtime(&curUTC);
    strftime(nmea_buff, BUF_SIZE, "$GPRMC,%H%M%S.000,,,*00\r\n", wrkTime);
    if (nMessages++ < 10 ) {  /* only send 10 messages */
      printf("nmea: %s", nmea_buff);
    }
    if (nMessages > 100) {  /* after 100 counts, reset */
      nMessages = 0;
    }
    RS232_cputs(cport_nr, nmea_buff); // sends string on serial
    
    //printf("Sent to Arduino: %s", nmea_buff);
    usleep(500000);  // Wait a while
  }
  return(0);
}
