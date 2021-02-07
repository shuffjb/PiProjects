/* statsg - show wlan0 IP address on oled display
 *          Uses ArduiPi libraries by Charles-Henri Hallard
 *          http://halard.me 
 *          git: https://github.com/hallard/ArduiPi_OLED.git
 *          Note: needs to run as super user (sudo)
 * 2021-02-04 JBS Cloned from stats.cpp (text only drivers)
 *  
 */

#include <stdio.h>
#include <time.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include "statsg.h"

// Instantiate the display
ArduiPi_OLED display;
//OLED type are:
//  0 Adafruit SPI 128x32
//  1 Adafruit SPI 128x64
//  2 Adafruit I2C 128x32
//  3 Adafruit I2C 128x64
//  4 Seeed I2C 128x64
//  5 Seeed I2C 96x96
//  6 SH1106 I2C 128x64

static char cMessage[256];
static char cCmd[256];

#define BUFSIZE 128

/* Function Prototypes  */

int runCmd(char * qcmd, char * qreturn);

int runCmd(char * qcmd, char * qreturn)  {
    /*char cmd[BUFSIZE];
     * sprintf(cmd, qcmd);  
     */  

    char buf[BUFSIZE];
    FILE *fp;

    if ((fp = popen(qcmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
        // Do whatever you want here...
        // printf("OUTPUT: %s", buf);
        strcpy(qreturn, buf);        /* put output of cmd in return */
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}


int main()
{
  int i=0;
  time_t rawtime;
  struct tm * timeinfo;

  // I2C change parameters to fit to your LCD
	if ( !display.init(OLED_I2C_RESET, OLED_TYPE) ) { // exit display fail
    exit(EXIT_FAILURE);
  }
  display.begin();
  display.clearDisplay();
  
  while (1) {/*  run forever  */
    
    strcpy(cCmd, "hostname -I | cut -d\' \' -f1");
    i = runCmd(cCmd, cMessage);
    i = i + 0;
    printf("%s\n", cMessage);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.printf("%s\n", cMessage);      /* line 1 */

/*
 *    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
        
        puts("The localtime() function failed");
        return 1;
    }
    
    printf("The time is: %02d:%02d:%02d\n", ptm->tm_hour, 
           ptm->tm_min, ptm->tm_sec);
 * 
 * 
 */

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    /*sprintf (cMessage, "%s", asctime (timeinfo) ); */
    sprintf(cMessage, 
            "%02d:%02d:%02d\n", 
            timeinfo->tm_hour, 
            timeinfo->tm_min, 
            timeinfo->tm_sec); 
            
    printf("%s\n", cMessage);
    display.printf("%s\n", cMessage);      /* line 2 */
    display.display();
    usleep(1000000);
  }
  return(0);
  /* end */
}

