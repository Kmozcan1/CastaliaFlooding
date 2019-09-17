package node.application.floodingApplication;

simple FloodingApplication like node.application.iApplication {
	parameters:	
		//Mandatory parameters, Section 5.2 of the document
		string applicationID = default ("FloodingApplication");
		bool collectTraceInfo = default(true);
		int priority = default(1);
		int packetHeaderOverhead = default(8); //maybe change to 5?
		int constantDataPayload = default(160); //forced packet size in case it is undefined
		
		
		bool isSink = default (false);
		int packetsSent = default(0);
		int totalPacketsSent = default(0);
		int totalPacketsReceived = default(0);
		int packetSize = default(32);
		int packetsPerNode = default(10);
		string reportDestination = default ("0");
		int minTimerInterval = default(100);
		int maxTimerInterval = default(500);
		int packetSpacing = default(100);
		
	//From iApplication.ned
	gates:
		output toCommunicationModule;
		output toSensorDeviceManager;
		input fromCommunicationModule;
		input fromSensorDeviceManager;
		input fromResourceManager;
}
