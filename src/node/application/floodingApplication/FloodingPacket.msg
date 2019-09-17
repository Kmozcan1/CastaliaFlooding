cplusplus {{
#include "ApplicationPacket_m.h"
}}

class ApplicationPacket;

packet FloodingPacket extends ApplicationPacket {
	int sourceID;
	string packetID;
}