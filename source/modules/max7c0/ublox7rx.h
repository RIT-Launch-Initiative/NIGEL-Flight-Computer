#ifndef UBLOX7RX_H
#define UBLOX7RX_H

#include <stdint.h>
#include <stdlib.h>

typedef struct 
{
	char msgID[4]; // NMEA string identifier (always 3 char with null)
	int rddc; // rate on DDC
	int rus1; // rate on USART 1
	int rus2; // rate on USART 2
	int rusb; // rate on USB
	int rspi; // rate on SPI
}  pubx_rate_t;

typedef struct
{  
	float time; // seconds since midnight
	float latitude; // degrees (N positive)
	float longitude; // degrees (E positive)
	float alt; // meters ASL
	int quality; // fix indicator
	int satts; // number of sattelites used
} gps_packet_t;

// TODO:
int rate_command(pubx_rate_t* fields, char* dest);

/**
  * @brief	Parse GGA sentence, populate dest
  *
  * @param	sentence	Beginning of GGA sentence
  * @param	dest		Pointer to GPS packet struct to populate
  * @param	n			Maximum number of characters to read, fails if string
  * 					not long enough
  * @retval				0 for success, 1 for sscanf fail, -1 for insufficient
  * 					length fail
  */
int parse_gga(const char* sentence, gps_packet_t* dest, size_t n);
#endif
