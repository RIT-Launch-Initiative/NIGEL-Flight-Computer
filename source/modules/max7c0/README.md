Implements PUBX RATE command and GGA sentence parsing.

*u-blox 7 Reciever Description / Including Protocol Specification V14*
# PUBX RATE Message Fields
*Reciever Description* pp. 69

`$PUBX,40,msgID,rddc,rus1,rus2,rusb,rspi,reserved*cs\r\n`

- msgID: NMEA message identifier - `ccc`
- rddc: output rate on DDC - `0` for no output, `1` for output per epoch
- rus1: output rate on USART1
- rus2: output rate on USART2
- rusb: output rate on USB
- rspi: output rate on SPI
- reserved: always `0`
- cs: checksum `cc`

# GGA Sentence Fields
*Reciever description* pp. 54

`$xxGGA,time,lat,NS,long,EW,quality,numSV,HDOP,alt,M,sep,M,[diffAge],[diffStation]*cs\r\n`

- time: UTC - `HHmmss.ss`
- lat: Latitude - `ddmm.mmmmm`
- NS: `N` or `S`
- long: Longitude - `dddmm.mmmmm`
- EW: `E` or `W`
- quality: Position fix quality indicator - `0` for no fix, `1` for standard GPS,
  `2` for DGPS
- numSV: Number of sattelites used `dd`
- HDOP: horizontal dilution of precision (numeric)
- alt: Altitude above mean sea level (meters, numeric)
- sep: Difference between geoid and mean sea level (meters, numeric)
- diffAge: Age of differential correction in seconds (if DGPS is used)
- diffStation: Station ID providing differential corrections (if DGPS is used)
