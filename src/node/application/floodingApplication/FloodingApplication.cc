#include "FloodingApplication.h"
#include <random>
#include <sstream>


Define_Module(FloodingApplication);

void FloodingApplication::startup() {
	trace() << "startup";
	
	// Load Parameters
	reportDestination = par("reportDestination").stringValue();
	packetsPerNode = par("packetsPerNode");
	//minTimerInterval = (double)par("minTimerInterval") / 1000;
	//maxTimerInterval = (double)par("packetsPerNode") / 1000;
	packetSpacing = (double)par("packetSpacing") / 1000.0;
	numberOfNodes = getParentModule()->getParentModule()->par("numNodes");
	totalPacketsReceived = par("totalPacketsReceived");
	packetsSent = par("totalPacketsReceived");
	packetSize = par("packetSize");
	
	// Creates a random float between two values
	// randomTimerInterval = fRand(minTimerInterval, maxTimerInterval);
	
	interval = packetsPerNode * packetSpacing;
	//totalInterval = (interval * numberOfNodes);
	trace() << "Packet Spacing: " << packetSpacing;
	trace() << "Packets per node: " << packetsPerNode;
	trace() << "Interval: " << interval * self;
	// Send the packet if the not is not the sink
	if (!isSink) {
		setTimer(SEND_PACKET, interval * self);
	}
}

void FloodingApplication::fromNetworkLayer(ApplicationPacket * rcvPacket, const char *source, double rssi, double lqi) {
	FloodingPacket *packet = static_cast<FloodingPacket *>(rcvPacket);
	if (!isSink) {
		//trace() << atoi(SELF_NETWORK_ADDRESS) << " is forwarding packet " << packet->getPacketID() << " from node " << source;
	} else {
		totalPacketsReceived++;
		trace() << "Packet " << packet->getPacketID() << " has been delivered to the sink";
		trace() << "Total packets collected by the sink: " << totalPacketsReceived << "\n";
	}
}

void FloodingApplication::timerFiredCallback(int timerIndex) {
	switch (timerIndex) {
		case SEND_PACKET: {
			if (isSink || packetsSent >= packetsPerNode) {
				break;
			}
			FloodingPacket *packet = new FloodingPacket("packet", APPLICATION_PACKET);
			stringstream packetID;
			packetID << atoi(SELF_NETWORK_ADDRESS) << "-" << packetsSent;
			packet->setPacketID(packetID.str().c_str());
			packet->setSourceID(atoi(SELF_NETWORK_ADDRESS));
			trace(); //empty trace looks better than \n at the start
			trace() << "Sending packet " << packet->getPacketID() << " Total packets sent: " << packetsSent;
			toNetworkLayer(packet, BROADCAST_NETWORK_ADDRESS);
			packetsSent++;
			randomTimerInterval = fRand(minTimerInterval, maxTimerInterval);
			setTimer(SEND_PACKET, packetSpacing);
			break;
		}
	}
}

double FloodingApplication::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
