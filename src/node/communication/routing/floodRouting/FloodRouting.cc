/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                           *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *
 *******************************************************************************/

#include "FloodRouting.h"

Define_Module(FloodRouting);

void FloodRouting::startup()
{
	cModule *appModule = getParentModule()->getParentModule()->getSubmodule("Application");

	if (appModule->hasPar("isSink"))
		isSink = appModule->par("isSink");
	else
		opp_error("\nDefine a sink please.");
}


void FloodRouting::fromApplicationLayer(cPacket * pkt, const char *destination)
{
	RoutingPacket *netPacket = new RoutingPacket("FloodRouting packet", NETWORK_LAYER_PACKET);
	netPacket->setSource(SELF_NETWORK_ADDRESS);
	netPacket->setDestination(destination);
	encapsulatePacket(netPacket, pkt);
	
	//Broadcast the packet
	toMacLayer(netPacket, BROADCAST_MAC_ADDRESS);
}


void FloodRouting::fromMacLayer(cPacket * pkt, int srcMacAddress, double rssi, double lqi)
{
	RoutingPacket *netPacket = dynamic_cast <RoutingPacket*>(pkt);
	string src(netPacket->getSource());
	trace() << "Incoming packet to " << SELF_NETWORK_ADDRESS << " from " << srcMacAddress;
	if (netPacket) {
		if (isNotDuplicatePacket(pkt) && src.compare(SELF_NETWORK_ADDRESS) != 0) {
			if(isSink) {
				toApplicationLayer(decapsulatePacket(pkt));
			} else {
				RoutingPacket *dupPacket = netPacket->dup();
				toApplicationLayer(decapsulatePacket(pkt));
				toMacLayer(dupPacket, BROADCAST_MAC_ADDRESS);
			} 
		} else {
			trace() << "Discarding the duplicate packet in node " << SELF_NETWORK_ADDRESS;	
		}
	}
}

