#ifndef _FLOODINGAPPLICATION_H_
#define _FLOODINGAPPLICATION_H_

#include "VirtualApplication.h"
#include "FloodingPacket_m.h"
#include <unordered_set>

using namespace std;

enum FloodingApplicationTimers {
	SEND_PACKET = 1,
};

class FloodingApplication:public VirtualApplication {
	private:
		int packetsSent;
		int totalPacketsSent;
		int totalPacketsReceived;
		int numberOfNodes;
		double minTimerInterval;
		double maxTimerInterval;
		double randomTimerInterval;
		double interval;
		int packetSize;
		int packetsPerNode;
		double packetSpacing;
		string reportDestination;
		std::unordered_set<string> receivedPacketSet;
	protected:
		virtual void startup();
		void fromNetworkLayer(ApplicationPacket *, const char *, double, double);		
		void timerFiredCallback(int);
		double fRand(double, double);
};

#endif