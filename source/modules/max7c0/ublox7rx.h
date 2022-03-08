#ifndef UBLOX7RX
#define UBLOX7RX 

#include<stdio.h>
#include<string.h>
#include<stdint.h>

#define PUBX_RATE_DEFAULT 

typedef struct 
{
	char msgID[4];
	int32_t rddc;	
	int32_t rus1;	
	int32_t rus2;	
	int32_t rusb;	
	int32_t rspi;	
} pubx_rate_t;

typedef struct
{
	float time; // seconds since midnight
	float latitude; // degrees (N positive)
	float longitude; // degrees (E positive)
	float alt; // meters ASL
	int32_t quality; // fix indicator
	int32_t satts; // number of sattelites used
} gps_packet_t;

int32_t rate_command(pubx_rate_t* fields, char* dest);
int32_t parse_gga(char* sentence, gps_packet_t* dest, size_t n);
#endif
