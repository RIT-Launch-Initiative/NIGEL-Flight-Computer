#include "ublox7rx.h"
#include <stdio.h>

// test definitions @{ 
#define GGA_TEST_1 "$GPGGA,115739.00,4158.8441367,N,09147.4416929,W,4,13,0.9,255.747,M,-32.00,M,01,0000*6E\r\n"
#define GGA_TEST_2 "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B\r\n"
#define GGA_TEST_BROKEN "$GPGGA,115739.00,.8441367,N,09147.4416929,W,4,13,0.9,255,M,-32.00,M,01,0000*6E\r\n"
#define PACKET_POS_FORMAT "Epoch time: %f [s]\n Latitude: %f [deg N], Longitude: %f [deg E], Altitude: %f [m ASL]\n"
#define PACKET_QUAL_FORMAT "Fix: %d, %d satellites\n"
// @}

void print_gps_packet(gps_packet_t packet)
{
	printf(
		PACKET_POS_FORMAT, 
		packet.time, packet.latitude, packet.longitude, packet.alt
	);
	printf(
		PACKET_QUAL_FORMAT,
		packet.quality, packet.satts
	);
}

int main()
{
	gps_packet_t packet;
	int32_t ret = parse_gga(GGA_TEST_2, &packet, 256);
	printf("parser return value: %d\n", ret);
	if (ret) {
		printf("Failed to convert:\n%s", GGA_TEST_2);
		return 1;
	}
	printf(GGA_TEST_2);
	print_gps_packet(packet);
	return 0;
}

