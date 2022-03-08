#include "ublox7rx.h"

int32_t parse_gga(char* sentence, gps_packet_t* dest, size_t n)
{
	// initalizing buffers
	char north, east;
	int hours, minutes, lat_deg, lon_deg;
	float lat_min, lon_min;

	int ret = sscanf(
		sentence, 
		"$%*2cGGA,%2d%2d%f,%2d%f,%c,%3d%f,%c,%1d,%2d,%*f,%f,%*f,%*f,%*f,%*2c\r\n",
		&hours, &minutes, &(dest->time), // parts of time
		&lat_deg, &lat_min, &north, &lon_deg, &lon_min, &east, // parts of lat/lon
		&(dest->quality), &(dest->satts), &(dest->alt)
	);
	
	if (ret != 12) {
		return -1;
	}

	dest->latitude = (lat_deg + lat_min/60) * ((north == 'N') ? 1 : -1);
	dest->longitude = (lon_deg + lon_min/60) * ((east == 'E') ? 1 : -1);
	dest->time += 3600 * hours + 60 * minutes;

	return 0;
}
