/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *  
 ****************************************************************************/

#ifndef MAC_802154_A_H_
#define MAC_802154_A_H_

#include <map>
#include <vector>

#include "VirtualMac.h"
#include "Mac802154aPacket_m.h"

#define ACK_PKT_SIZE 6
#define COMMAND_PKT_SIZE 8
#define GTS_SPEC_FIELD_SIZE 3
#define BASE_BEACON_PKT_SIZE 12

#define TX_TIME(x) (phyLayerOverhead + x)*1/(1000*phyDataRate/8.0)	//x are in BYTES

using namespace std;

enum MacStates {
	MAC_STATE_SETUP = 1000,
	MAC_STATE_SLEEP = 1001,
	MAC_STATE_IDLE = 1002,
	MAC_STATE_CSMA_CA = 1003,
	MAC_STATE_CCA = 1004,
	MAC_STATE_IN_TX = 1005,
	MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE = 1006,
	MAC_STATE_WAIT_FOR_DATA_ACK = 1007,
	MAC_STATE_WAIT_FOR_BEACON = 1008,
	MAC_STATE_WAIT_FOR_GTS = 1009,
	MAC_STATE_PROCESSING = 1011
};

enum Mac802154aTimers {
	PERFORM_CCA = 1,
	ATTEMPT_TX = 2,
	BEACON_TIMEOUT = 3,
	GTS_START = 4,
	START_SLEEPING = 5,
	FRAME_START = 6,
	PERFORM_SAMAN_CCA = 7,
};

class Mac802154a: public VirtualMac {
 private:
    /*--- A map from int value of state to its description (used in debug) ---*/
	map<int,string> stateDescr;

	int sentBeacons;
	int recvBeacons;
	int packetoverflow;

	double previous_x;
	double previous_y;
	double previous_z;

    /*--- A map for packet breakdown statistics ---*/
	map<string,int> packetBreak;

    /*--- The .ned file's parameters ---*/
	bool printStateTransitions;
	bool isPANCoordinator;
	bool isFFD;
	bool batteryLifeExtention;
	bool enableSlottedCSMA;
	bool enableCAP;
	simtime_t previosCCAtime;
	int numberOfInitiateCSMACA;

	int numberOfPacketBreakdownDuringOneSuperfarame;
	int numberOfChannelIsBusyDuringOneSuperfarame;
	int numberOfChannelIsNotValidDuringOneSuperfarame;
	int numberOfPacketSentDuringOneSuperfarameCAP;
	int numberOfPacketSentDuringOneSuperfarameCFP;

	int numberOfBeaconReceived; //valid (Castalia results)
	int numberOfPacketSentCFP; //valid (numberOfPacketSentCFP+numberOfPacketSentCAP-numberOfPacketFailedNoAck=numberOfPacketSentSuccesfully)
	int numberOfPacketSentCAP; //valid (numberOfPacketSentCFP+numberOfPacketSentCAP-numberOfPacketFailedNoAck=numberOfPacketSentSuccesfully)
	int numberOfPacketFailedNoAck; //valid (numberOfPacketSentCFP+numberOfPacketSentCAP-numberOfPacketFailedNoAck=numberOfPacketSentSuccesfully)
	int numberOfPacketSentSuccesfully; //valid (Castalia resutls)
	int numberOfPacketSentSuccesfullyCAP; //valid (numberOfPacketSentSuccesfullyCAP+numberOfPacketSentSuccesfullyCFP=numberOfPacketSentSuccesfully)
	int numberOfPacketSentSuccesfullyCFP; //valid (numberOfPacketSentSuccesfullyCAP+numberOfPacketSentSuccesfullyCFP=numberOfPacketSentSuccesfully)

	int numberOfPacketTryToSentInCFP; //Valid (numberOfPacketTryToSentInCFP-numberOfPacketTryToSentInCFPButoutsideGTS=numberOfPacketSentCFP)
	int numberOfPacketTryToSentInCFPButoutsideGTS; //Valid (numberOfPacketTryToSentInCFP-numberOfPacketTryToSentInCFPButoutsideGTS=numberOfPacketSentCFP)

	int numberOfPacketTryToSentInCAP; //Valid (numberOfPacketTryToSentInCAP-numberOfPacketTryToSentInCAPButOutsideCAP=numberOfPacketSentCAP)
	int numberOfPacketTryToSentInCAPButOutsideCAP;  //Valid (numberOfPacketTryToSentInCAP-numberOfPacketTryToSentInCAPButOutsideCAP=numberOfPacketSentCAP)

	int numberOfContinueCSMACA;
	simtime_t sumBackofTime;
	int numberOfChannelIsCLEAR;
	int numberOfChannelIsCLEARcwIs0;
	int numberOfChannelIsBusy;
	int numberOfChannelIsNotValid;
	int numberOfChannelIsCS_NOT_VALID;
	int numberOfPerformCCA; //Valid (numberOfPerformCCA=~(numberOfContinueCSMACA+numberOfChannelIsClearButCWisNot0)-numberOfPerformCCAButMacStateIsNotCSMACA)
	int numberOfChannelIsClearButCWisNot0;
	int numberOfPerformCCAButMacStateIsNotCSMACA;

	int numberOfContinueCSMACADuringOneSuperfarame;
	simtime_t sumBackofTimeDuringOneSuperfarame;

	bool nodeSendPacketDuringCAP;
	bool nodeSendDataPacketDuringCAP;
	bool nodeSendDataPacketDuringCFP;
	bool nodeSendDataPacket;
	int numberOfChanelClearDuringSuperfarame;
	int numberOfChanelClearAndCWis0DuringSuperfarame;


	int numberOfResults;
	int indexOfNumberOfResults;
	int s_numberOfPacketSentCAP;
	int s_numberOfChannelIsCLEARcwIs0;

	int a_arrayNumberOfChannelIsCLEARcwIs0[6];
	int a_numberOfResults[6];
	int a_array_n[6];
	int a_array_indexOfNumberOfResults[6];

	int m_numberOfPacketSentCAP;
	int m_numberOfChannelIsCLEARcwIs0;

	int MACMACa;
	int numberOfPacketSentSuccesfullyCAP_MACMACa;
	int numberOfPacketSentSuccesfullyCFP_MACMACa;

	int numberOfPacketSentCAP_MACMACa;
	int numberOfPacketSentCFP_MACMACa;


	int macMinBE;
	int macMaxBE;
	int macMaxCSMABackoffs;
	int macMaxFrameRetries;
	int maxLostBeacons;
	int minCAPLength;
	int unitBackoffPeriod;
	int baseSlotDuration;
	int numSuperframeSlots;
	int baseSuperframeDuration;
	int beaconOrder;
	int frameOrder;
	int requestGTS;

    /*--- General MAC variable ---*/
	int nextPacketTry;
	double nextPacketTime;
	bool lockedGTS;
	simtime_t phyDelayForValidCS;		// delay for valid CS
	simtime_t phyDelaySleep2Tx;
	simtime_t phyDelayRx2Tx;
	int phyLayerOverhead;
	int phyBitsPerSymbol;
	double phyDataRate;

    /*--- 802154Mac state variables  ---*/
	int associatedPAN;	// ID of current PAN (-1 if not associated)
	int macState;		// current MAC state
	int nextMacState;	// next MAC state (will be switched after CSMA-CA algorithm ends)
	int CAPlength;		// duration of CAP interval (in number of superframe slots)
	int macBSN;			// beacon sequence number (unused)
	int nextPacketRetries;	// number of retries left for next packet to be sent
	int lostBeacons;	// number of consequitive lost beacon packets
	int frameInterval;	// duration of active part of the frame (in symbols)
	int beaconInterval;	// duration of the whole frame (in symbols)

	int NB, CW, BE;		// CSMA-CA algorithm parameters (Number of Backoffs, 
						// Contention Window length and Backoff Exponent)

	simtime_t CAPend;	// Absolute time of end of CAP period for current frame
	simtime_t currentFrameStart;	// Absolute recorded start time of the current frame
	simtime_t GTSstart;
	simtime_t GTSend;
	simtime_t GTSlength;

	simtime_t nextPacketResponse;	// Duration of timeout for receiving a reply after sending a packet
	simtime_t ackWaitDuration;		// Duration of timeout for receiving an ACK
	simtime_t symbolLen;			// Duration of transmittion of a single symbol
	simtime_t guardTime;

	string nextPacketState;
	simtime_t desyncTime;
	simtime_t desyncTimeStart;

	map<int,bool> associatedDevices;	// map of assoicated devices (for PAN coordinator)

    /*--- 802154Mac packet pointers (sometimes packet is created not immediately before sending) ---*/
	Mac802154aPacket *beaconPacket;
	Mac802154aPacket *associateRequestPacket;
	Mac802154aPacket *nextPacket;

    /*--- 802154Mac GTS list --- */
	vector<GTSspecA> GTSlist;	// list of GTS specifications (for PAN coordinator)

 protected:
	virtual void startup();
	void fromNetworkLayer(cPacket *, int);
	void fromRadioLayer(cPacket *, double, double);

	double getNodeLocationX();
	double getNodeLocationY();
	double getNodeLocationZ();
	void openFile(ofstream&,string);

	virtual void finishSpecific();
	void readIniFileParameters(void);
	void setMacState(int newState);
	void handleAckPacket(Mac802154aPacket *);
	void initiateCSMACA(int, int, simtime_t);
	void initiateCSMACA();
	void continueCSMACA();
	void attemptTransmission(const char *);
	void transmitNextPacket();
	void issueGTSrequest();
	void timerFiredCallback(int);
	int collectPacketState(const char *);
};
#endif				//MAC_802154_MODULE
