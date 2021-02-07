/* stats - show wlan0 IP address on oled display
 *         Text only, no cursor control.  Uses libraries by
 *         kjhughes097
 *         git: https://github.com/kjhughes097/pi-ssd1306-oled.git
 * 2021-01-22 JBS Created from samples
 *  
 */

#include <stdio.h>
#include <time.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h> 
#include <arpa/inet.h> 

#include "stats.h"
#include "pipedemo.h"
#include "ssd1306.h"

static char cMessage[256];
static char cCmd[256];

int main()
{
  int fd;
  int i=0;
  struct ifreq ifr;
  time_t rawtime;
  struct tm * timeinfo;
  SSD1306 myDisplay;
  myDisplay.initDisplay();
  myDisplay.clearDisplay();
  
  while (1) {/*  run forever  */
    
    strcpy(cCmd, "hostname -I | cut -d\' \' -f1");
    i = runCmd(cCmd, cMessage);
    printf("%s\n", cMessage);
    myDisplay.textDisplay(cMessage);        /* line 1 */
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    sprintf (cMessage, "TM: %s", asctime (timeinfo) );
    printf("%s\n", cMessage);
    myDisplay.textDisplay(cMessage);        /* line 2 */
    usleep(1000000);
    myDisplay.clearDisplay();
  }
  return(0);
  /* end */
}

