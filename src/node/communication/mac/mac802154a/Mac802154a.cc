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
#include <iostream>
#include <fstream>
#include <string>
#include "Mac802154a.h"
#include "fuzzyIS/FuzzyLite.h"
#include <limits>
#include "fuzzyIS/FunctionTerm.h"


Define_Module(Mac802154a);

void Mac802154a::startup()
{
	previous_x = 0;
	previous_y = 0;
	previous_z = 0;
	MACMACa = 0;

	numberOfPacketSentCAP_MACMACa = 0;
	numberOfPacketSentCFP_MACMACa = 0;

	readIniFileParameters();
	numberOfChanelClearDuringSuperfarame = 0;
	numberOfChanelClearAndCWis0DuringSuperfarame = 0;
	numberOfBeaconReceived = 0;
	numberOfInitiateCSMACA = 0;
	numberOfPacketFailedNoAck = 0;
	numberOfPacketSentSuccesfully = 0;
	numberOfPacketSentCFP = 0;
	numberOfPacketSentCAP = 0;
	numberOfContinueCSMACA = 0;
	sumBackofTime = 0;
	nodeSendDataPacket = false;
	nodeSendDataPacketDuringCAP = false;
	nodeSendDataPacketDuringCFP = false;
	numberOfPacketSentSuccesfullyCFP = 0;
	numberOfPacketSentSuccesfullyCAP = 0;

	numberOfPacketSentSuccesfullyCAP_MACMACa = 0;
	numberOfPacketSentSuccesfullyCFP_MACMACa = 0;

	numberOfPacketTryToSentInCFP = 0;
	numberOfPacketTryToSentInCFPButoutsideGTS = 0;

	numberOfPacketTryToSentInCAP = 0;
	numberOfPacketTryToSentInCAPButOutsideCAP = 0;

	numberOfPerformCCA = 0;
	numberOfChannelIsCLEAR = 0;
	numberOfChannelIsBusy = 0;
	numberOfChannelIsNotValid = 0;
	numberOfChannelIsCLEARcwIs0 = 0;
	numberOfChannelIsCS_NOT_VALID = 0;
	nodeSendPacketDuringCAP = false;
	numberOfChannelIsClearButCWisNot0 = 0;
	numberOfPerformCCAButMacStateIsNotCSMACA = 0;


	numberOfResults = 0;
	indexOfNumberOfResults = 0;
	s_numberOfPacketSentCAP = 0;
	s_numberOfChannelIsCLEARcwIs0 = 0;
	a_arrayNumberOfChannelIsCLEARcwIs0[0] = 0; //n=1
	a_arrayNumberOfChannelIsCLEARcwIs0[1] = 0; //n=10
	a_arrayNumberOfChannelIsCLEARcwIs0[2] = 0; //n=20
	a_arrayNumberOfChannelIsCLEARcwIs0[3] = 0; //n=40
	a_arrayNumberOfChannelIsCLEARcwIs0[4] = 0; //n=80
	a_arrayNumberOfChannelIsCLEARcwIs0[5] = 0; //n=100

	a_array_n[0]=1;
	a_array_n[1]=10;
	a_array_n[2]=20;
	a_array_n[3]=40;
	a_array_n[4]=80;
	a_array_n[5]=100;

	a_numberOfResults[0] = 0;
	a_numberOfResults[1] = 0;
	a_numberOfResults[2] = 0;
	a_numberOfResults[3] = 0;
	a_numberOfResults[4] = 0;
	a_numberOfResults[5] = 0;

	a_array_indexOfNumberOfResults[0] = 0;
	a_array_indexOfNumberOfResults[1] = 0;
	a_array_indexOfNumberOfResults[2] = 0;
	a_array_indexOfNumberOfResults[3] = 0;
	a_array_indexOfNumberOfResults[4] = 0;
	a_array_indexOfNumberOfResults[5] = 0;

	m_numberOfPacketSentCAP = 0;
	m_numberOfChannelIsCLEARcwIs0 = 0;


	//Initialise state descriptions used in debug output
	if (printStateTransitions) {
		stateDescr[1000] = "MAC_STATE_SETUP";
		stateDescr[1001] = "MAC_STATE_SLEEP";
		stateDescr[1002] = "MAC_STATE_IDLE";
		stateDescr[1003] = "MAC_STATE_CSMA_CA";
		stateDescr[1004] = "MAC_STATE_CCA";
		stateDescr[1005] = "MAC_STATE_IN_TX";
		stateDescr[1006] = "MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE";
		stateDescr[1007] = "MAC_STATE_WAIT_FOR_DATA_ACK";
		stateDescr[1008] = "MAC_STATE_WAIT_FOR_BEACON";
		stateDescr[1009] = "MAC_STATE_WAIT_FOR_GTS";
		stateDescr[1011] = "MAC_STATE_PROCESSING";
	}

	phyDataRate = par("phyDataRate");
	phyDelaySleep2Tx = (double)par("phyDelaySleep2Tx") / 1000.0;
	phyDelayRx2Tx = (double)par("phyDelayRx2Tx") / 1000.0;
	phyDelayForValidCS = (double)par("phyDelayForValidCS") / 1000.0;
	phyLayerOverhead = par("phyFrameOverhead");
	phyBitsPerSymbol = par("phyBitsPerSymbol");

	guardTime = (double)par("guardTime") / 1000.0;

	ofstream myfile;
	openFile(myfile,"startup");
	myfile <<  getClock() << "," <<  previosCCAtime << endl;
	myfile.close();

	/**************************************************************************************************
	 *			802.15.4 specific intialize
	 **************************************************************************************************/

	symbolLen = 1 / (phyDataRate * 1000 / phyBitsPerSymbol);
	ackWaitDuration = symbolLen * unitBackoffPeriod + 
		phyDelayRx2Tx * 2 + TX_TIME(ACK_PKT_SIZE);

	beaconPacket = NULL;
	associateRequestPacket = NULL;
	nextPacket = NULL;
	nextPacketResponse = 0;
	nextPacketRetries = 0;
	nextPacketState = "";
	nextMacState = 0;

	macState = MAC_STATE_SETUP;
	macBSN = rand() % 255;
	lockedGTS = false;
	associatedPAN = -1;
	currentFrameStart = 0;
	GTSstart = 0;
	GTSend = 0;
	CAPend = 0;
	lostBeacons = 0;
	sentBeacons = 0;
	recvBeacons = 0;
	packetoverflow = 0;

	desyncTime = 0;
	desyncTimeStart = 0;

	packetBreak.clear();

	if (isFFD && isPANCoordinator) {
		associatedPAN = SELF_MAC_ADDRESS;
		setTimer(FRAME_START, 0);	//frame start is NOW
	}
}

void Mac802154a::timerFiredCallback(int index)
{

	    ofstream fileForAll;
		fileForAll.open ("fileForAll.txt", ios::ate | ios::out | ios::app);//ios::ate | ios::out | ios::app

		string nodeId;
		if(getFullPath().compare("SN.node[0].Communication.MAC") == 0)
			nodeId = "0";
		else if(getFullPath().compare("SN.node[1].Communication.MAC") == 0)
			nodeId = "1";
		else if(getFullPath().compare("SN.node[2].Communication.MAC") == 0)
			nodeId = "2";
		else if(getFullPath().compare("SN.node[3].Communication.MAC") == 0)
			nodeId = "3";
		else if(getFullPath().compare("SN.node[4].Communication.MAC") == 0)
			nodeId = "4";
		else if(getFullPath().compare("SN.node[5].Communication.MAC") == 0)
			nodeId = "5";

		string timerFiredCallbackStatus;
		switch (index) {
		case FRAME_START: timerFiredCallbackStatus = "FRAME_START"; break;
		case BEACON_TIMEOUT: timerFiredCallbackStatus = "BEACON_TIMEOUT"; break;
		case GTS_START: timerFiredCallbackStatus = "GTS_START"; break;
		case ATTEMPT_TX: timerFiredCallbackStatus = "ATTEMPT_TX"; break;
		case PERFORM_CCA: timerFiredCallbackStatus = "PERFORM_CCA"; break;
		case START_SLEEPING: timerFiredCallbackStatus= "START_SLEEPING"; break;
		}

		fileForAll << nodeId << "," << timerFiredCallbackStatus << "," << getClock() <<  "/";
		fileForAll.close();


	switch (index) {
		case 	PERFORM_SAMAN_CCA:{
			continueCSMACA();
			break;
		}
		case FRAME_START:{
			if (isPANCoordinator) {	// as a PAN coordinator, create and broadcast beacon packet
				beaconPacket = new Mac802154aPacket("PAN beacon packet", MAC_LAYER_PACKET);
				beaconPacket->setDstID(BROADCAST_MAC_ADDRESS);
				beaconPacket->setPANid(SELF_MAC_ADDRESS);
				beaconPacket->setMac802154aPacketType(MAC_802154_BEACON_PACKET);
				beaconPacket->setBeaconOrder(beaconOrder);
				beaconPacket->setFrameOrder(frameOrder);
				if (macBSN > 254) {
					macBSN = 0;
				} else {
					macBSN++;
				}
				beaconPacket->setBSN(macBSN);

				CAPlength = numSuperframeSlots;
				beaconPacket->setGTSlistArraySize(GTSlist.size());
				for (int i = 0; i < (int)GTSlist.size(); i++) {
					if (CAPlength > GTSlist[i].length) {
						CAPlength -= GTSlist[i].length;
						GTSlist[i].start = CAPlength + 1;
						beaconPacket->setGTSlist(i, GTSlist[i]);
					} else {
						GTSlist[i].length = 0;
						trace() << "Internal ERROR: GTS list corrupted";
					}
				}

				beaconPacket->setCAPlength(CAPlength);
				beaconPacket->setByteLength(BASE_BEACON_PKT_SIZE + GTSlist.size() * GTS_SPEC_FIELD_SIZE);
				CAPend = CAPlength * baseSlotDuration * (1 << frameOrder) * symbolLen;
				sentBeacons++;

				setMacState(MAC_STATE_IN_TX);
				toRadioLayer(beaconPacket);
				toRadioLayer(createRadioCommand(SET_STATE, TX));
				setTimer(ATTEMPT_TX, TX_TIME(beaconPacket->getByteLength()));
				beaconPacket = NULL;

				setTimer(FRAME_START, beaconInterval * symbolLen);
				currentFrameStart = getClock() + phyDelayRx2Tx;
			} else {	// if not a PAN coordinator, then wait for beacon
				toRadioLayer(createRadioCommand(SET_STATE, RX));
				setMacState(MAC_STATE_WAIT_FOR_BEACON);
				setTimer(BEACON_TIMEOUT, guardTime * 3);
			}
			break;
		}

		// beacon timeout fired - indicates that beacon was missed by this node
		case BEACON_TIMEOUT:{
			lostBeacons++;
			if (lostBeacons >= maxLostBeacons) {
				trace() << "Lost synchronisation with PAN " << associatedPAN;
				setMacState(MAC_STATE_SETUP);
				associatedPAN = -1;
				lockedGTS = false;
				desyncTimeStart = getClock();
			} else if (associatedPAN != -1) {
				trace() << "Missed beacon from PAN " << associatedPAN <<
				    ", will wake up to receive next beacon in " <<
				    beaconInterval * symbolLen - guardTime * 3 << " seconds";
				setMacState(MAC_STATE_SLEEP);
				toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
				setTimer(FRAME_START, beaconInterval * symbolLen - guardTime * 3);
			}
			break;
		}

		case GTS_START:{
			if (macState == MAC_STATE_WAIT_FOR_DATA_ACK ||
			    macState == MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE ||
			    macState == MAC_STATE_PROCESSING) {
				break;
			}

			toRadioLayer(createRadioCommand(SET_STATE, RX));
			// we delay transmission attempt by the time requred by radio to wake up
			// note that GTS_START timer was scheduled exactly phyDelaySleep2Tx seconds
			// earlier than the actual start time of GTS slot
			setMacState(MAC_STATE_PROCESSING);
			setTimer(ATTEMPT_TX, phyDelaySleep2Tx);
			
			// set a timer to go to sleep after our GTS slot ends
			setTimer(START_SLEEPING, phyDelaySleep2Tx + GTSlength);
			break;
		}

		// previous transmission is reset, attempt a new transmission 
		case ATTEMPT_TX:{
			if (macState != MAC_STATE_IN_TX
			    && macState != MAC_STATE_WAIT_FOR_DATA_ACK
			    && macState != MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE
			    && macState != MAC_STATE_WAIT_FOR_GTS
			    && macState != MAC_STATE_PROCESSING) {
				trace() << "WARNING ATTEMPT_TX timer was not cancelled, macState is " << macState;
				break;
			}

			if (macState == MAC_STATE_WAIT_FOR_DATA_ACK)
			{
				numberOfPacketFailedNoAck++;
				collectPacketState("NoAck");
			}

			attemptTransmission("ATTEMPT_TX timer");
			break;
		}
		// timer to preform carrier sense
		case PERFORM_CCA:{
			if (macState != MAC_STATE_CSMA_CA){
				numberOfPerformCCAButMacStateIsNotCSMACA++;
				break;
			}
			CCA_result CCAcode = radioModule->isChannelClear();

			if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET)
				numberOfPerformCCA++;

			if (CCAcode == CLEAR) {
				CW--;
				if (CW != 0) {
					if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET){
						numberOfChannelIsCLEAR++;
						numberOfChannelIsClearButCWisNot0++;
						numberOfChanelClearDuringSuperfarame++;
					}
					// since carrier is clear, no need to generate another random delay
					setTimer(PERFORM_CCA, unitBackoffPeriod * symbolLen);

					ofstream myfile;
					openFile(myfile,"PERFORM_CCA/CCAcodeCLEAR");
					myfile <<  getClock() << "," <<  previosCCAtime << endl;
					myfile.close();

				} else if (!nextPacket) {
					trace() << "ERROR: CSMA_CA algorithm executed without any data to transmit";
					attemptTransmission("ERROR in CSMA_CA");
				} else {
					// CSMA-CA successful (CW == 0), can transmit the queued packet
					if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET){
						numberOfChannelIsCLEAR++;
						nodeSendDataPacketDuringCAP = true;
						numberOfChannelIsCLEARcwIs0++;
						s_numberOfChannelIsCLEARcwIs0++;
						m_numberOfChannelIsCLEARcwIs0++;

						a_arrayNumberOfChannelIsCLEARcwIs0[0]++;
						a_arrayNumberOfChannelIsCLEARcwIs0[1]++;
						a_arrayNumberOfChannelIsCLEARcwIs0[2]++;
						a_arrayNumberOfChannelIsCLEARcwIs0[3]++;
						a_arrayNumberOfChannelIsCLEARcwIs0[4]++;
						a_arrayNumberOfChannelIsCLEARcwIs0[5]++;

						numberOfChanelClearAndCWis0DuringSuperfarame++;
						numberOfChanelClearDuringSuperfarame++;

						ofstream myfile;
						openFile(myfile,"BEACON");
						myfile << "                   CCAtime:" <<  previosCCAtime << " CCAcode == CLEAR  try to transmission BE:" << BE  << "[" << numberOfBeaconReceived << "] CSMA-CA successful= " << numberOfPacketSentDuringOneSuperfarameCAP << "       NB: " << NB <<"       Buffer: [" << TXBuffer.size() << "]"  << endl;
						myfile.close();
					}

					transmitNextPacket();
				}
			} else if (CCAcode == BUSY) {
				if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET){
					numberOfChannelIsBusyDuringOneSuperfarame ++;
					numberOfChannelIsBusy++;
				}
				ofstream myfile;
				openFile(myfile,"BEACON");
				myfile << "                   CCAtime:" <<  previosCCAtime << " CCAcode == BUSY  BE:" << BE  << "[" << numberOfBeaconReceived << "].numberOfChannelIsBusyDuringOneSuperfarame = " << numberOfChannelIsBusyDuringOneSuperfarame << endl;
				myfile.close();

				//if MAC is preforming CSMA-CA, update corresponding parameters
				CW = enableSlottedCSMA ? 2 : 1;
				NB++;
				BE++;
				if (BE > macMaxBE)
					BE = macMaxBE;
				if (NB > macMaxCSMABackoffs) {
					collectPacketState("CSfail");
					nextPacketRetries--;
					attemptTransmission("NB exeeded maxCSMAbackoffs");
				} else {
					setMacState(MAC_STATE_CSMA_CA);
					continueCSMACA();
				}
			} else if (CCAcode == CS_NOT_VALID_YET) {
				if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET){
					numberOfChannelIsNotValidDuringOneSuperfarame ++;
					numberOfChannelIsNotValid++;
				}
				ofstream myfile;
				openFile(myfile,"BEACON");
				myfile << "                                            [" << numberOfBeaconReceived << "] numberOfChannelIsNotValidDuringOneSuperfarame = " << numberOfChannelIsNotValidDuringOneSuperfarame << endl;
				myfile.close();

				setTimer(PERFORM_CCA, phyDelayForValidCS);
			} else {	//CS_NOT_VALID
				if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET)
					numberOfChannelIsCS_NOT_VALID++;
				opp_error("802.15.4 MAC internal error, isChannelClear() function called when radio is NOT READY");
			}
			break;
		}

		case START_SLEEPING:{
			setMacState(MAC_STATE_SLEEP);
			toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
			break;
		}
	}
}

/* This indicates that a packet is received from upper layer (Network)
 * First we check that the MAC buffer is capable of holding the new packet, also check
 * that length does not exceed the valid mac frame size. Then store a copy of the packet
 * is stored in transmission buffer. We dont need to encapsulate the message here - it will
 * be done separately for each transmission attempt
 */
void Mac802154a::fromNetworkLayer(cPacket * pkt, int dstMacAddress)
{
	Mac802154aPacket *macPacket = new Mac802154aPacket("802.15.4 MAC data packet", MAC_LAYER_PACKET);
	macPacket->setSrcID(SELF_MAC_ADDRESS);	//if we are connected, we would have short MAC address assigned, 
	//but we are not using short addresses in this model
	macPacket->setDstID(dstMacAddress);
	macPacket->setMac802154aPacketType(MAC_802154_DATA_PACKET);
	encapsulatePacket(macPacket, pkt);

	if (bufferPacket(macPacket)) {
		if (macState == MAC_STATE_IDLE)
			attemptTransmission("New packet from network layer");
	} else {
		packetoverflow++;
		//full buffer message
	}
}

void Mac802154a::finishSpecific()
{
	if (nextPacket)
		cancelAndDelete(nextPacket);
	if (desyncTimeStart >= 0)
		desyncTime += getClock() - desyncTimeStart;

	map <string,int>::const_iterator iter;
	declareOutput("Packet breakdown");
	if (packetoverflow > 0)
		collectOutput("Packet breakdown", "Failed, buffer overflow", packetoverflow);
	for (iter = packetBreak.begin(); iter != packetBreak.end(); ++iter) {
		if (iter->first.compare("Success") == 0) {
			collectOutput("Packet breakdown", "Success, first try", iter->second);
		} else if (iter->first.compare("Broadcast") == 0) {
			collectOutput("Packet breakdown", "Broadcast", iter->second);
		} else if (iter->first.find("Success") != string::npos) {
			collectOutput("Packet breakdown", "Success, not first try", iter->second);
		} else if (iter->first.find("NoAck") != string::npos) {
			collectOutput("Packet breakdown", "Failed, no ack", iter->second);
		} else if (iter->first.find("CSfail") != string::npos) {
			collectOutput("Packet breakdown", "Failed, busy channel", iter->second);
		} else if (iter->first.find("NoPAN") != string::npos) {
			collectOutput("Packet breakdown", "Failed, no PAN", iter->second);
		} else {
			trace() << "Unknown packet breakdonw category: " <<
				iter->first << " with " << iter->second << " packets";
		}
	}

	if (!isPANCoordinator) {
		if (desyncTime > 0) {
			declareOutput("Fraction of time without PAN connection");
			collectOutput("Fraction of time without PAN connection", "",
				SIMTIME_DBL(desyncTime) / SIMTIME_DBL(getClock()));
		}
		declareOutput("Number of beacons received");
		collectOutput("Number of beacons received", "", recvBeacons);
	} else {
		declareOutput("Number of beacons sent");
		collectOutput("Number of beacons sent", "", sentBeacons);
	}

	ofstream myfile;
	openFile(myfile,"finishSpecific");

	myfile << "numberOfPacketSentSuccesfully: " << numberOfPacketSentSuccesfully << endl;
	myfile << "numberOfPacketSentSuccesfullyCFP: " << numberOfPacketSentSuccesfullyCFP << endl;
	myfile << "numberOfPacketSentSuccesfullyCAP: " << numberOfPacketSentSuccesfullyCAP << endl << endl;
	myfile << "Percentage of numberOfPacketSentSuccesfullyCFP: " << (float)numberOfPacketSentSuccesfullyCFP/numberOfPacketSentSuccesfully << endl;
	myfile << "Percentage of numberOfPacketSentSuccesfullyCAP: " << (float)numberOfPacketSentSuccesfullyCAP/numberOfPacketSentSuccesfully << endl << "------------------------------------------" << endl << endl;


	myfile << "numberOfPacketTryToSentInCFP: " << numberOfPacketTryToSentInCFP << endl;
	myfile << "numberOfPacketTryToSentInCFPButoutsideGTS: " << numberOfPacketTryToSentInCFPButoutsideGTS << endl;
	myfile << "numberOfPacketSentCFP:" << numberOfPacketSentCFP << endl << "------------------------------------------" << endl << endl;

	myfile << "numberOfContinueCSMACA: " << numberOfContinueCSMACA << endl;
	myfile << "numberOfPerformCCA: " << numberOfPerformCCA << endl  << endl;
	myfile << "numberOfChannelIsCLEAR: " << numberOfChannelIsCLEAR << endl;
	myfile << "numberOfChannelIsCLEARcwIs0: " << numberOfChannelIsCLEARcwIs0 << endl;
	myfile << "numberOfChannelIsBusy: " << numberOfChannelIsBusy << endl;
	myfile << "numberOfChannelIsNotValid: " << numberOfChannelIsNotValid << endl;
	myfile << "numberOfChannelIsCS_NOT_VALID: " << numberOfChannelIsCS_NOT_VALID << endl;
	myfile << "numberOfChannelIsClearButCWisNot0: " << numberOfChannelIsClearButCWisNot0 << endl;
	myfile << "numberOfPerformCCAButMacStateIsNotCSMACA: " << numberOfPerformCCAButMacStateIsNotCSMACA << endl << endl;

	myfile << "numberOfPacketTryToSentInCAP: " << numberOfPacketTryToSentInCAP << endl;
	myfile << "numberOfPacketTryToSentInCAPButOutsideCAP: " << numberOfPacketTryToSentInCAPButOutsideCAP << endl;
	myfile << "numberOfPacketSentCAP:" << numberOfPacketSentCAP << endl << "------------------------------------------" << endl << endl;

	myfile << "numberOfPacketFailedNoAck:" << numberOfPacketFailedNoAck << endl << "------------------------------------------" << endl << endl;

	myfile << "Number of beacon recived: " << numberOfBeaconReceived << endl;
	myfile << "Number of continue CSMACA: " << numberOfContinueCSMACA << endl;
	myfile << "Avrage Backof Time: " << sumBackofTime/numberOfContinueCSMACA << endl  << endl;


	myfile << "Percentage of numberOfChannelIsCLEAR: " << (float)numberOfChannelIsCLEAR/numberOfPerformCCA << endl;
	myfile << "Percentage of numberOfChannelIsBusy: " << (float)numberOfChannelIsBusy/numberOfPerformCCA << endl << endl;

	myfile << "Avrage numberOfChannelIsCLEAR: " << (float)numberOfChannelIsCLEAR/numberOfPerformCCA << endl;
	myfile << "Avrage numberOfChannelIsCLEARcwIs0: " << (float)numberOfChannelIsCLEARcwIs0/numberOfPerformCCA << endl;
	myfile << "Avrage numberOfChannelIsBusy: " << (float)numberOfChannelIsBusy/numberOfPerformCCA << endl;
	myfile << "Avrage numberOfChannelIsNotValid: " << (float)numberOfChannelIsNotValid/numberOfPerformCCA << endl << endl;

	myfile << "numberOfChanelClearDuringSuperfarame: " << numberOfChanelClearDuringSuperfarame << endl;
	myfile << "numberOfChanelClearDuringSuperfarame/numberOfBeaconReceived: " <<  numberOfChanelClearDuringSuperfarame << "/" << numberOfBeaconReceived << "= "<< (float)numberOfChanelClearDuringSuperfarame/numberOfBeaconReceived << endl;

    myfile.close();
}

void Mac802154a::readIniFileParameters(void)
{
	printStateTransitions = par("printStateTransitions");

	enableSlottedCSMA = par("enableSlottedCSMA");
	enableCAP = par("enableCAP");
	requestGTS = par("requestGTS");

	isPANCoordinator = par("isPANCoordinator");
	isFFD = par("isFFD");

	unitBackoffPeriod = par("unitBackoffPeriod");
	baseSlotDuration = par("baseSlotDuration");
	numSuperframeSlots = par("numSuperframeSlots");
	maxLostBeacons = par("maxLostBeacons");
	minCAPLength = par("minCAPLength");
	macMinBE = par("macMinBE");
	macMaxBE = par("macMaxBE");
	macMaxCSMABackoffs = par("macMaxCSMABackoffs");
	macMaxFrameRetries = par("macMaxFrameRetries");
	batteryLifeExtention = par("batteryLifeExtention");
	baseSuperframeDuration = baseSlotDuration * numSuperframeSlots;

	if (isPANCoordinator) {
		if (!isFFD) {
			opp_error("Only full-function devices (isFFD=true) can be PAN coordinators");
		}

		requestGTS = 0;
		enableCAP = true;
		frameOrder = par("frameOrder");
		beaconOrder = par("beaconOrder");
		if (frameOrder < 0 || beaconOrder < 0 || beaconOrder > 14
		    || frameOrder > 14 || beaconOrder < frameOrder) {
			opp_error("Invalid combination of frameOrder and beaconOrder parameters. Must be 0 <= frameOrder <= beaconOrder <= 14");
		}

		beaconInterval = baseSuperframeDuration * (1 << beaconOrder);
		frameInterval = baseSuperframeDuration * (1 << frameOrder);
		CAPlength = numSuperframeSlots;

		if (beaconInterval <= 0 || frameInterval <= 0) {
			opp_error("Invalid parameter combination of baseSlotDuration and numSuperframeSlots");
		}
	}
}

/* Helper function to change internal MAC state and print a debug statement if neccesary */
void Mac802154a::setMacState(int newState)
{
	if (macState == newState)
		return;
	if (printStateTransitions)
		trace() << "state changed from " << stateDescr[macState] << " to " << stateDescr[newState];
	macState = newState;
}

/* This function will handle a MAC frame received from the lower layer (physical or radio)
 */
void Mac802154a::fromRadioLayer(cPacket * pkt, double rssi, double lqi)
{
	Mac802154aPacket *rcvPacket = dynamic_cast < Mac802154aPacket * >(pkt);
	if (!rcvPacket)
		return;

	switch (rcvPacket->getMac802154aPacketType()) {

		/* received a BEACON frame */
		case MAC_802154_BEACON_PACKET:{
			int PANaddr = rcvPacket->getPANid();
			recvBeacons++;
			numberOfBeaconReceived++;
			nodeSendPacketDuringCAP = false;
		    numberOfResults++;

		    a_numberOfResults[0]++;
		    a_numberOfResults[1]++;
		    a_numberOfResults[2]++;
		    a_numberOfResults[3]++;
		    a_numberOfResults[4]++;
		    a_numberOfResults[5]++;

		    if(a_numberOfResults[0] == a_array_n[0]){
		    	a_array_indexOfNumberOfResults[0] = a_array_indexOfNumberOfResults[0] + a_array_n[0];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[0];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[0] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[0] <<  "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[0]/a_array_n[0] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[0] = 0;
				a_numberOfResults[0] = 0;
		    }
		    if(a_numberOfResults[1] == a_array_n[1]){
		    	a_array_indexOfNumberOfResults[1] = a_array_indexOfNumberOfResults[1] + a_array_n[1];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[1];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[1] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[1] << "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[1]/a_array_n[1] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[1] = 0;
				a_numberOfResults[1] = 0;
		    }
		    if(a_numberOfResults[2] == a_array_n[2]){
		    	a_array_indexOfNumberOfResults[2] = a_array_indexOfNumberOfResults[2] + a_array_n[2];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[2];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[2] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[2] << "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[2] = 0;
				a_numberOfResults[2] = 0;
		    }
		    if(a_numberOfResults[3] == a_array_n[3]){
		    	a_array_indexOfNumberOfResults[3] = a_array_indexOfNumberOfResults[3] + a_array_n[3];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[3];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[3] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[3] << "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[3]/a_array_n[3] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[3] = 0;
				a_numberOfResults[3] = 0;
		    }

		    if(a_numberOfResults[4] == a_array_n[4]){
		    	a_array_indexOfNumberOfResults[4] = a_array_indexOfNumberOfResults[4] + a_array_n[4];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[4];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[4] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[4] << "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[4]/a_array_n[4] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[4] = 0;
				a_numberOfResults[4] = 0;
		    }

		    if(a_numberOfResults[5] == a_array_n[5]){
		    	a_array_indexOfNumberOfResults[5] = a_array_indexOfNumberOfResults[5] + a_array_n[5];
				ofstream myfilearray;

				std::string filename;
				std::stringstream out;
				out << a_array_n[5];
				filename = out.str();

				openFile(myfilearray,"ChannelIsCLEARcwIs0/" + filename);
				myfilearray << a_array_indexOfNumberOfResults[5] << "," << a_arrayNumberOfChannelIsCLEARcwIs0[5] << "," << (double)a_arrayNumberOfChannelIsCLEARcwIs0[5]/a_array_n[5] <<  endl;
				myfilearray.close();
				a_arrayNumberOfChannelIsCLEARcwIs0[5] = 0;
				a_numberOfResults[5] = 0;
		    }


		    if(numberOfResults == 100){
		    	indexOfNumberOfResults = indexOfNumberOfResults + 100;

		    	ofstream myfile1;
		    	openFile(myfile1,"100sample/s_numberOfPacketSentCAP");
				myfile1 << indexOfNumberOfResults << "," << s_numberOfPacketSentCAP <<  endl;
				myfile1.close();

		    	ofstream myfile2;
		    	openFile(myfile2,"100sample/s_numberOfChannelIsCLEARcwIs0");
				myfile2 << indexOfNumberOfResults << "," << s_numberOfChannelIsCLEARcwIs0 << "," << (float)s_numberOfChannelIsCLEARcwIs0/100 <<  endl;
				myfile2.close();

				numberOfResults = 0;
		    	s_numberOfPacketSentCAP = 0;
		    	s_numberOfChannelIsCLEARcwIs0 = 0;
		    }


		    MACMACa++;
		    if(MACMACa == 50){
				ofstream myfile_mac;
				openFile(myfile_mac,"MAC/MACa");
				myfile_mac << numberOfBeaconReceived  << "," << numberOfPacketSentCAP_MACMACa << "," << numberOfPacketSentCFP_MACMACa << "," << numberOfPacketSentCAP_MACMACa+numberOfPacketSentCFP_MACMACa  << endl;
				myfile_mac.close();
				MACMACa = 0;
				numberOfPacketSentSuccesfullyCAP_MACMACa = 0;
				numberOfPacketSentSuccesfullyCFP_MACMACa = 0;

				numberOfPacketSentCAP_MACMACa = 0;
				numberOfPacketSentCFP_MACMACa = 0;
			}



	    	ofstream myfile3;
	    	openFile(myfile3,"100sample/m_numberOfChannelIsCLEARcwIs0");
			myfile3 << numberOfBeaconReceived  << "," << m_numberOfChannelIsCLEARcwIs0 << "," << (float)m_numberOfChannelIsCLEARcwIs0/numberOfBeaconReceived  << endl;
			myfile3.close();


	    	ofstream myfile4;
	    	openFile(myfile4,"numberOfChanelClearDuringSuperfarame");
			myfile4 << numberOfBeaconReceived << "," << numberOfChanelClearDuringSuperfarame << "," << numberOfChanelClearAndCWis0DuringSuperfarame << endl;
			myfile4.close();

	    	ofstream myfile;
	    	openFile(myfile,"BEACON");
			myfile << "PacketSentDuringOneSuperfarame CAP: " << numberOfPacketSentDuringOneSuperfarameCAP << endl << "PacketSent CAP: " << numberOfPacketSentCAP << endl << "PacketSentGTS: " << numberOfPacketSentCFP  << endl << "PacketSentSuccesfully: " << numberOfPacketSentSuccesfully << endl << "PacketFailedNoAck:" << numberOfPacketFailedNoAck << endl << endl <<"Buffer: [" << TXBuffer.size() << "]"  << endl;
			myfile << "-----------------" << endl;
			myfile << "numberOfContinueCSMACADuringOneSuperfarame: " << numberOfContinueCSMACADuringOneSuperfarame << endl;
			myfile << "Avrage sumBackofTimeDuringOneSuperfarame: " << sumBackofTimeDuringOneSuperfarame/numberOfContinueCSMACADuringOneSuperfarame << endl;

			myfile << "numberOfPacketSentSuccesfully: " << numberOfPacketSentSuccesfully << endl;
			myfile << "numberOfPacketSentSuccesfullyCFP: " << numberOfPacketSentSuccesfullyCFP << endl;
			myfile << "numberOfPacketSentSuccesfullyCAP: " << numberOfPacketSentSuccesfullyCAP << endl << endl;

			myfile << "numberOfPacketSentCFP:" << numberOfPacketSentCFP << endl;
			myfile << "numberOfPacketSentCAP:" << numberOfPacketSentCAP << endl;
			myfile << "numberOfPacketFailedNoAck:" << numberOfPacketFailedNoAck << endl << endl;

			myfile << "Number of beacon recived: " << numberOfBeaconReceived << endl;
			myfile << "Number of continue CSMACA: " << numberOfContinueCSMACA << endl;
			myfile << "Avrage Backof Time: " << sumBackofTime/numberOfContinueCSMACA << endl  << endl;

			myfile << "--------------------------------------------------------------------------------------------------" << endl;
			myfile << "BEACON:["<< numberOfBeaconReceived <<"]     Received time:[ " << getClock() << " ]" << endl << " ------------------------------------------------------------------------------"  << endl;
			myfile << "numberOfPacketSentSuccesfullyCFP: " << numberOfPacketSentSuccesfullyCFP << endl;
			myfile << "numberOfPacketSentSuccesfullyCAP: " << numberOfPacketSentSuccesfullyCAP << endl;

			myfile.close();
			numberOfPacketBreakdownDuringOneSuperfarame = 0;
			numberOfChannelIsBusyDuringOneSuperfarame = 0;
			numberOfChannelIsNotValidDuringOneSuperfarame = 0;
			numberOfPacketSentDuringOneSuperfarameCAP = 0;
			numberOfPacketSentDuringOneSuperfarameCFP = 0;
			numberOfContinueCSMACADuringOneSuperfarame = 0;
			sumBackofTimeDuringOneSuperfarame = 0;

			numberOfChanelClearDuringSuperfarame = 0;
			numberOfChanelClearAndCWis0DuringSuperfarame = 0;

			if (associatedPAN == -1) {
				//if not associated - create an association request packet
				if (nextPacket) {
					if (collectPacketState("NoPAN"))
						packetBreak[nextPacketState]++;
					cancelAndDelete(nextPacket);
				}
				nextPacket = new Mac802154aPacket("PAN associate request", MAC_LAYER_PACKET);
				nextPacket->setDstID(PANaddr);
				nextPacket->setPANid(PANaddr);
				nextPacket->setMac802154aPacketType(MAC_802154_ASSOCIATE_PACKET);
				nextPacket->setSrcID(SELF_MAC_ADDRESS);
				nextPacket->setByteLength(COMMAND_PKT_SIZE);
				initiateCSMACA(9999, MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE,
					ackWaitDuration + TX_TIME(COMMAND_PKT_SIZE));
			} else if (associatedPAN != PANaddr) {
				// if associated to a different PAN - do nothing
				return;
			}
			//update frame parameters
			currentFrameStart = getClock() - TX_TIME(rcvPacket->getByteLength());
			lostBeacons = 0;
			frameOrder = rcvPacket->getFrameOrder();
			beaconOrder = rcvPacket->getBeaconOrder();
			beaconInterval = baseSuperframeDuration * (1 << beaconOrder);
			macBSN = rcvPacket->getBSN();
			CAPlength = rcvPacket->getCAPlength();
			CAPend = CAPlength * baseSlotDuration * (1 << frameOrder) * symbolLen;
			GTSstart = 0;
			GTSend = 0;
			GTSlength = 0;

			for (int i = 0; i < (int)rcvPacket->getGTSlistArraySize(); i++) {
				if (lockedGTS && rcvPacket->getGTSlist(i).owner == SELF_MAC_ADDRESS) {
					GTSstart = (rcvPacket->getGTSlist(i).start - 1) * 
						baseSlotDuration * (1 << frameOrder) * symbolLen;
					GTSend = GTSstart + rcvPacket->getGTSlist(i).length *
					    baseSlotDuration * (1 << frameOrder) * symbolLen;
					GTSlength = GTSend - GTSstart;
					trace() << "GTS slot from " << getClock() +
					    GTSstart << " to " << getClock() + GTSend;
				}
			}

			//cancel beacon timeout message (if present)
			cancelTimer(BEACON_TIMEOUT);

			if (requestGTS) {
				if (lockedGTS) {
					if (GTSstart == 0) {
						trace() << "invalid state, GTS descriptor not found in beacon frame";
						lockedGTS = false;
					}
				} else if (associatedPAN == PANaddr) {
					issueGTSrequest();
				}
			}

			if (associatedPAN == PANaddr) {
				if (enableCAP) {
					attemptTransmission("CAP started");
					//set timer to start sleeping
					if (GTSstart == CAPend)
						// if GTS slot starts right after CAP, then
						// we start sleeping after both CAP and GTS slots end
						setTimer(START_SLEEPING, CAPend + GTSlength);
					else
						// if GTS slot does not start after CAP (or no GTS at all)
						// then we start sleeping right after CAP ends
						setTimer(START_SLEEPING, CAPend);
				} else {
					setMacState(MAC_STATE_SLEEP);
					toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
				}
				if (GTSstart != 0 && (!enableCAP || GTSstart != CAPend))
					// if GTS slot exists and does not start after CAP (or CAP is disabled) 
					// then we set GTS timer phyDelaySleep2Tx seconds earlier as radio will be sleeping
					setTimer(GTS_START, GTSstart - phyDelaySleep2Tx);
			}

			setTimer(FRAME_START, baseSuperframeDuration * (1 << beaconOrder) *
				 symbolLen - guardTime - TX_TIME(rcvPacket->getByteLength()));
			break;
		}

		// request to associate
		case MAC_802154_ASSOCIATE_PACKET:{
			// only PAN coordinators can accept association requests
			// if multihop communication is to be allowed - then this has to be changed
			// in particular, any FFD can become a coordinator and accept requests
			if (!isPANCoordinator)
				break;

			// if PAN id is not the same as my ID - do nothing
			if (rcvPacket->getPANid() != SELF_MAC_ADDRESS)
				break;

			// update associatedDevices and reply with an ACK (i.e. association is always allowed)
			trace() << "Received association request from " << rcvPacket->getSrcID();
			associatedDevices[rcvPacket->getSrcID()] = true;
			Mac802154aPacket *ackPacket = new Mac802154aPacket("PAN associate response", MAC_LAYER_PACKET);
			ackPacket->setPANid(SELF_MAC_ADDRESS);
			ackPacket->setMac802154aPacketType(MAC_802154_ACK_PACKET);
			ackPacket->setDstID(rcvPacket->getSrcID());
			ackPacket->setByteLength(ACK_PKT_SIZE);
			toRadioLayer(ackPacket);
			toRadioLayer(createRadioCommand(SET_STATE, TX));

			setMacState(MAC_STATE_IN_TX);
			setTimer(ATTEMPT_TX, TX_TIME(ACK_PKT_SIZE));
			break;
		}

		case MAC_802154_GTS_REQUEST_PACKET:{
			if (!isPANCoordinator)
				break;
			if (rcvPacket->getPANid() != SELF_MAC_ADDRESS)
				break;
			trace() << "Received GTS request from " << rcvPacket->getSrcID();

			Mac802154aPacket *ackPacket = new Mac802154aPacket("PAN GTS response", MAC_LAYER_PACKET);
			ackPacket->setPANid(SELF_MAC_ADDRESS);
			ackPacket->setMac802154aPacketType(MAC_802154_ACK_PACKET);
			ackPacket->setDstID(rcvPacket->getSrcID());
			ackPacket->setByteLength(ACK_PKT_SIZE);
			ackPacket->setGTSlength(0);

			int index = -1;
			for (int i = 0; i < (int)GTSlist.size(); i++) {
				if (GTSlist[i].owner == rcvPacket->getSrcID()) {
					if (GTSlist[i].length == rcvPacket->getGTSlength()) {
						ackPacket->setGTSlength(GTSlist[i].length);
					} else {
						CAPlength += GTSlist[i].length;
						GTSlist[i].length = 0;
						index = i;
					}
				}
			}

			if (ackPacket->getGTSlength() == 0) {
				if ((CAPlength - rcvPacket->getGTSlength()) *
				    baseSlotDuration * (1 << frameOrder) < minCAPLength) {
					trace() << "GTS request from " << rcvPacket->getSrcID() <<
					    " cannot be acocmodated";
				} else if (index != -1) {
					GTSlist[index].length = rcvPacket->getGTSlength();
					ackPacket->setGTSlength(GTSlist[index].length);
				} else {
					GTSspecA newGTSspecA;
					newGTSspecA.length = rcvPacket->getGTSlength();
					newGTSspecA.owner = rcvPacket->getSrcID();
					GTSlist.push_back(newGTSspecA);
				}
			}

			toRadioLayer(ackPacket);
			toRadioLayer(createRadioCommand(SET_STATE, TX));
			setMacState(MAC_STATE_IN_TX);
			setTimer(ATTEMPT_TX, TX_TIME(ACK_PKT_SIZE));

			break;
		}

		// ack frames are handled by a separate function
		case MAC_802154_ACK_PACKET:{
			if (rcvPacket->getDstID() != SELF_MAC_ADDRESS)
				break;
			handleAckPacket(rcvPacket);
			break;
		}

		// data frame
		case MAC_802154_DATA_PACKET:{
			int dstAddr = rcvPacket->getDstID();
			if (dstAddr != SELF_MAC_ADDRESS && dstAddr != BROADCAST_MAC_ADDRESS)
				break;

			toNetworkLayer(decapsulatePacket(rcvPacket));

			// If the frame was sent to broadcast address, nothing else needs to be done
			if (dstAddr == BROADCAST_MAC_ADDRESS)
				break;

			Mac802154aPacket *ackPacket = new Mac802154aPacket("Ack packet", MAC_LAYER_PACKET);
			ackPacket->setPANid(SELF_MAC_ADDRESS);
			ackPacket->setMac802154aPacketType(MAC_802154_ACK_PACKET);
			ackPacket->setDstID(rcvPacket->getSrcID());
			ackPacket->setByteLength(ACK_PKT_SIZE);

			toRadioLayer(ackPacket);
			toRadioLayer(createRadioCommand(SET_STATE, TX));
			setMacState(MAC_STATE_IN_TX);
			setTimer(ATTEMPT_TX, TX_TIME(ACK_PKT_SIZE));

			break;
		}

		default:{
			trace() << "WARNING: unknown packet type received " << rcvPacket->getMac802154aPacketType() <<
					" [" << rcvPacket->getName() << "]";
		}
	}
}

void Mac802154a::handleAckPacket(Mac802154aPacket * rcvPacket)
{
	switch (macState) {

		//received an ack while waiting for a response to association request
		case MAC_STATE_WAIT_FOR_ASSOCIATE_RESPONSE:{
			associatedPAN = rcvPacket->getPANid();
			if (desyncTimeStart >= 0) {
				desyncTime += getClock() - desyncTimeStart;
				desyncTimeStart = -1;
			}
			trace() << "associated with PAN:" << associatedPAN;
			cancelAndDelete(nextPacket);
			nextPacket = NULL;
			if (requestGTS) {
				issueGTSrequest();
			} else {
				attemptTransmission("Associated with PAN");
			}
			break;
		}

		//received an ack while waiting for a response to data packet
		case MAC_STATE_WAIT_FOR_DATA_ACK:{
			if (isPANCoordinator || associatedPAN == rcvPacket->getSrcID()) {
				if(nodeSendDataPacketDuringCAP){
					numberOfPacketSentSuccesfullyCAP++;
					numberOfPacketSentSuccesfullyCAP_MACMACa++;
					ofstream myfile;
					openFile(myfile,"Location/succesfullyTransmitNextPacketforCAP");
					myfile <<  getClock() << "," << previous_x << "," << previous_y << endl;
					myfile.close();

					previous_x = 0.0;
					previous_y = 0.0;
					previous_z = 0.0;
				}
				else{
					numberOfPacketSentSuccesfullyCFP++;
					numberOfPacketSentSuccesfullyCFP_MACMACa++;
					ofstream myfile;
					openFile(myfile,"Location/succesfullyTransmitNextPacketforCFP");
					myfile <<  getClock() << "," << previous_x << "," << previous_y << endl;
					myfile.close();

					previous_x = 0.0;
					previous_y = 0.0;
					previous_z = 0.0;
				}

				collectPacketState("Success");
				trace() << "Packet successfully transmitted to " << rcvPacket->getSrcID();
				nextPacketRetries = 0;
				attemptTransmission("ACK received");
				numberOfPacketSentSuccesfully++;
			}
			break;
		}

		case MAC_STATE_WAIT_FOR_GTS:{
			lockedGTS = true;
			cancelAndDelete(nextPacket);
			nextPacket = NULL;
			if (enableCAP) {
				attemptTransmission("GTS request granted");
			} else {
				setMacState(MAC_STATE_SLEEP);
				toRadioLayer(createRadioCommand(SET_STATE, SLEEP));
			}
			break;
		}

		default:{
			trace() << "WARNING: received unexpected ACK in state " << stateDescr[macState];
			break;
		}
	}
}

// This function will initiate a transmission (or retransmission) attempt after a given delay
void Mac802154a::attemptTransmission(const char * descr)
{
	cancelTimer(ATTEMPT_TX);
	trace() << "Attempt transmission, description: " << descr;

	if (currentFrameStart + CAPend > getClock()) {	// we could use a timer here
		// still in CAP period of the frame
		if (!enableCAP) {
			setMacState(MAC_STATE_IDLE);
			return;
		}
	} else if (requestGTS == 0 || GTSstart == 0) {
		// not in CAP period and not in GTS, no transmissions possible
		setMacState(MAC_STATE_IDLE);
		return;
	} else if (currentFrameStart + GTSstart > getClock() ||	//we could use a timer here too!
		   currentFrameStart + GTSend < getClock()) {
		// outside GTS, no transmissions possible
		setMacState(MAC_STATE_IDLE);
		return;
	}
	// if a packet already queued for transmission - check avaliable retries
	if (nextPacket) {
		if (nextPacketRetries <= 0) {
			if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET) {
				if (nextPacket->getDstID() != BROADCAST_MAC_ADDRESS)
					packetBreak[nextPacketState]++;
				else
					packetBreak["Broadcast"]++;
			}
			cancelAndDelete(nextPacket);
			nextPacket = NULL;
		} else {
			trace() << "Continuing transmission of [" << nextPacket->getName() <<
				"], retries left: " << nextPacketRetries;
			initiateCSMACA();
			return;
		}
	}
	// if not associated to a PAN - cannot initiate transmissions other than association requests
	if (associatedPAN == -1)
		return;

	// extract a packet from transmission buffer
	if (TXBuffer.size() > 0) {
		nextPacket = check_and_cast <Mac802154aPacket*>(TXBuffer.front());
		TXBuffer.pop();
		int txAddr = nextPacket->getDstID();
		nextPacketState = "";
		if (txAddr == BROADCAST_MAC_ADDRESS)
			initiateCSMACA(0, MAC_STATE_IN_TX, TX_TIME(nextPacket->getByteLength()));
		else
			initiateCSMACA(macMaxFrameRetries, MAC_STATE_WAIT_FOR_DATA_ACK,
				       ackWaitDuration + TX_TIME(nextPacket->getByteLength()));
		return;
	}

	setMacState(MAC_STATE_IDLE);
}

// initiate CSMA-CA algorithm, initialising retries, next state and response values
void Mac802154a::initiateCSMACA(int retries, int nextState, simtime_t response)
{
	trace() << "Initiating new transmission of [" << nextPacket->getName() <<
		"], retries left: " << retries;
	nextPacketRetries = retries;
	nextMacState = nextState;
	nextPacketResponse = response;
	initiateCSMACA();
}

// initiate CSMA-CA algorithm
void Mac802154a::initiateCSMACA()
{
	nodeSendDataPacketDuringCAP = false;
	nodeSendDataPacketDuringCFP = false;

	if (requestGTS && lockedGTS && currentFrameStart + GTSstart < getClock()
	    && currentFrameStart + GTSend > getClock()) {
		//we are in GTS, no need to run CSMA-CA - transmit right away
		trace() << "Transmitting packet in GTS";
		nodeSendDataPacketDuringCFP = true;
		transmitNextPacket();
		return;
	}

	if (macState == MAC_STATE_CSMA_CA) {
		trace() << "WARNING: cannot initiate CSMA-CA algorithm while in MAC_STATE_CSMA_CA";
		return;
	}

 	setMacState(MAC_STATE_CSMA_CA);

 	numberOfInitiateCSMACA++;

 	NB = 0;
	CW = enableSlottedCSMA ? 2 : 1;
	BE = batteryLifeExtention ? (macMinBE < 2 ? macMinBE : 2) : macMinBE;


	    /*
	    if(getFullPath().compare("SN.node[3].Communication.MAC") == 0){
	    	simtime_t initiateCsmacADelayTime;
	        initiateCsmacADelayTime = 0.0001811250;
	        setTimer(PERFORM_SAMAN_CCA, initiateCsmacADelayTime);
	    }
	    else if(getFullPath().compare("SN.node[2].Communication.MAC") == 0){
	    	simtime_t initiateCsmacADelayTime;
	        initiateCsmacADelayTime = 0.0001011250;
	        setTimer(PERFORM_SAMAN_CCA, initiateCsmacADelayTime);
	    }
	    else{
	    	continueCSMACA();
	    }

		/*
		simtime_t initiateCsmacADelayTime;
		initiateCsmacADelayTime = 0.0000000250;
		setTimer(PERFORM_SAMAN_CCA, initiateCsmacADelayTime);
		*/
	continueCSMACA();
}

// continue CSMA-CA algorithm
void Mac802154a::continueCSMACA()
{
	if (macState != MAC_STATE_CSMA_CA) {
		trace() << "WARNING: continueCSMACA called not in MAC_STATE_CSMA_CA";
		return;
	}
	//generate a random delay, multiply it by backoff period length


    ofstream myfile_fuzzy;
    openFile(myfile_fuzzy,"fuzzyInitiateCSMACA");


    FuzzyOperator& op_a = FuzzyOperator::DefaultFuzzyOperator();
	FuzzyEngine engine_a("complex-mamdani", op_a);
    engine_a.hedgeSet().add(new HedgeNot);
    engine_a.hedgeSet().add(new HedgeSomewhat);
    engine_a.hedgeSet().add(new HedgeVery);

    InputLVar* rateChannelIsCLEARcw0_a = new InputLVar("RateChannelIsCLEARcw0");
    rateChannelIsCLEARcw0_a->addTerm(new ShoulderTerm("R1", 0.2, 0.4, true));
    rateChannelIsCLEARcw0_a->addTerm(new TriangularTerm("R2", 0.2, 0.6));
    rateChannelIsCLEARcw0_a->addTerm(new TriangularTerm("R3", 0.4, 0.8));
    rateChannelIsCLEARcw0_a->addTerm(new TriangularTerm("R4", 0.6, 1));
    rateChannelIsCLEARcw0_a->addTerm(new TriangularTerm("R5", 0.8, 1.2));
    rateChannelIsCLEARcw0_a->addTerm(new ShoulderTerm("R6", 1, 1.2, false));
    engine_a.addInputLVar(rateChannelIsCLEARcw0_a);



    InputLVar* sampleRate_a = new InputLVar("SampleRate");
    sampleRate_a->addTerm(new ShoulderTerm("S1", 20, 40, true));
    sampleRate_a->addTerm(new TriangularTerm("S2", 20, 60));
    sampleRate_a->addTerm(new TriangularTerm("S3", 40, 80));
    sampleRate_a->addTerm(new TriangularTerm("S4", 60, 100));
    sampleRate_a->addTerm(new TriangularTerm("S5", 80, 120));
    sampleRate_a->addTerm(new ShoulderTerm("S6", 100, 120, false));
    engine_a.addInputLVar(sampleRate_a);

    OutputLVar* fuzzyDelayTime_a = new OutputLVar("DelayTime");
    fuzzyDelayTime_a->addTerm(new ShoulderTerm("D1", 2, 4, true));
    fuzzyDelayTime_a->addTerm(new TriangularTerm("D2", 2, 6));
    fuzzyDelayTime_a->addTerm(new TriangularTerm("D3", 4, 8));
    fuzzyDelayTime_a->addTerm(new TriangularTerm("D4", 6, 10));
    fuzzyDelayTime_a->addTerm(new ShoulderTerm("D5", 8, 10, false));

    engine_a.addOutputLVar(fuzzyDelayTime_a);

    RuleBlock* block_a = new RuleBlock();
    block_a->addRule(new MamdaniRule("if SampleRate is S1 then DelayTime is D5", engine_a));
    block_a->addRule(new MamdaniRule("if SampleRate is S2 then DelayTime is D5", engine_a));
    block_a->addRule(new MamdaniRule("if SampleRate is S3 then DelayTime is D4", engine_a));
    block_a->addRule(new MamdaniRule("if SampleRate is S4 then DelayTime is D3", engine_a));
    block_a->addRule(new MamdaniRule("if SampleRate is S5 then DelayTime is D2", engine_a));
    block_a->addRule(new MamdaniRule("if SampleRate is S6 then DelayTime is D1", engine_a));

    engine_a.addRuleBlock(block_a);

    int sampleRateId = 0;
    switch(SELF_MAC_ADDRESS){
		case 1: sampleRateId = 10; break;
		case 2: sampleRateId = 30; break;
		case 3: sampleRateId = 60; break;
		case 4: sampleRateId = 80; break;
		case 5: sampleRateId = 120; break;
    }

    rateChannelIsCLEARcw0_a->setInput((double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2]);
    sampleRate_a->setInput(sampleRateId);
    engine_a.process();
    flScalar fuzzyDelayTimeOut_a = fuzzyDelayTime_a->output().defuzzify();

    //**************************************************************************************
    //**************************************************************************************
    //**************************************************************************************


    FuzzyOperator& op = FuzzyOperator::DefaultFuzzyOperator();
	FuzzyEngine engine("complex-mamdani", op);

	    engine.hedgeSet().add(new HedgeNot);
	    engine.hedgeSet().add(new HedgeSomewhat);
	    engine.hedgeSet().add(new HedgeVery);

	    /*InputLVar* energy = new InputLVar("Energy");
	    energy->addTerm(new TriangularTerm("LOW", 0.0, 0.50));
	    energy->addTerm(new TriangularTerm("MEDIUM", 0.25, 0.75));
	    energy->addTerm(new TriangularTerm("HIGH", 0.50, 1.00));
	    engine.addInputLVar(energy);*/

	    InputLVar* fuzzyBuffer = new InputLVar("Buffer");
	    //fuzzyBuffer->addTerm(new TriangularTerm("ABSOLUTELY_EMPTY", 0, 4));
	    fuzzyBuffer->addTerm(new ShoulderTerm("NEARLY_EMPTY", 8, 16, true));
	    fuzzyBuffer->addTerm(new TriangularTerm("NEARLY_HALF_EMPTY", 8, 24));
	    //fuzzyBuffer->addTerm(new TriangularTerm("ABSOLUTELY_MIDDLE", 12, 20));
	    fuzzyBuffer->addTerm(new TriangularTerm("NEARLY_HALF_FULL", 16, 32));
	    fuzzyBuffer->addTerm(new ShoulderTerm("NEARLY_FULL", 24, 32, false));
	    //fuzzyBuffer->addTerm(new TriangularTerm("ABSOLUTELY_FULL", 28, 32));
	    engine.addInputLVar(fuzzyBuffer);

		//myfile << "numberOfChanelClearDuringSuperfarame: " << numberOfChanelClearDuringSuperfarame << endl;
		//myfile << "numberOfChanelClearDuringSuperfarame/numberOfBeaconReceived: " <<  numberOfChanelClearDuringSuperfarame << "/" << numberOfBeaconReceived << "= "<< (float)numberOfChanelClearDuringSuperfarame/numberOfBeaconReceived << endl;

	    InputLVar* rateChannelIsCLEARcw0 = new InputLVar("RateChannelIsCLEARcw0");
	    rateChannelIsCLEARcw0->addTerm(new ShoulderTerm("R1", 0.2, 0.4, true));
	    rateChannelIsCLEARcw0->addTerm(new TriangularTerm("R2", 0.2, 0.6));
	    rateChannelIsCLEARcw0->addTerm(new TriangularTerm("R3", 0.4, 0.8));
	    rateChannelIsCLEARcw0->addTerm(new TriangularTerm("R4", 0.6, 1));
	    rateChannelIsCLEARcw0->addTerm(new TriangularTerm("R5", 0.8, 1.2));
	    rateChannelIsCLEARcw0->addTerm(new ShoulderTerm("R6", 1, 1.2, false));
	    engine.addInputLVar(rateChannelIsCLEARcw0);

	    InputLVar* sampleRate = new InputLVar("SampleRate");
	    sampleRate->addTerm(new ShoulderTerm("S1", 20, 40, true));
	    sampleRate->addTerm(new TriangularTerm("S2", 20, 60));
	    sampleRate->addTerm(new TriangularTerm("S3", 40, 80));
	    sampleRate->addTerm(new TriangularTerm("S4", 60, 100));
	    sampleRate->addTerm(new TriangularTerm("S5", 80, 120));
	    sampleRate->addTerm(new ShoulderTerm("S6", 100, 120, false));
	    engine.addInputLVar(sampleRate);

	    /*-------------------------------------------------------------------------------------------------------
		(double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2]
	    /*-------------------------------------------------------------------------------------------------------
		In parametr tedade kole halathaye ke chanel clear bode va CW ham 0 bode ra az zamane shoroe simoulation ta be hal ra neshan midahad.
		 (float)m_numberOfChannelIsCLEARcwIs0/numberOfBeaconReceived
		 max=
		 min=
	    /*-------------------------------------------------------------------------------------------------------
		In parametr tedade kole halathaye ke chanel clear bode va CW ham 0 bode ra az zamane shoroe simoulation ta be hal ra neshan midahad.
		 (float)m_numberOfChannelIsCLEARcwIs0/numberOfBeaconReceived
		 max=
		 min=
	    /*-------------------------------------------------------------------------------------------------------
		In parametr tedade kole halathaye ke chanel clear bode va CW ham 0 bode ra dar tole 100 superframe ra neshan midahad.
		 (float)s_numberOfChannelIsCLEARcwIs0/100 = The number of channel is clear and CW is 0 in 100 superframe
		 max=
		 min=
	    /*-------------------------------------------------------------------------------------------------------*/

	   /* OutputLVar* fuzzyBE = new OutputLVar("BE");
	    fuzzyBE->addTerm(new ShoulderTerm("D1", 2, 3, true));
	    fuzzyBE->addTerm(new TriangularTerm("D2", 2, 4));
	    fuzzyBE->addTerm(new TriangularTerm("D3", 3, 5));
	    fuzzyBE->addTerm(new TriangularTerm("D4", 4, 6));
	    fuzzyBE->addTerm(new TriangularTerm("D5", 5, 7));
	    fuzzyBE->addTerm(new ShoulderTerm("D6", 6, 7, false));*/

	    OutputLVar* fuzzyDelayTime = new OutputLVar("DelayTime");
	    /*fuzzyDelayTime->addTerm(new ShoulderTerm("D1", 8, 16, true));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D2", 8, 24));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D3", 16, 32));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D4", 24, 40));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D5", 32, 48));
	    fuzzyDelayTime->addTerm(new ShoulderTerm("D6", 40, 48, false));*/

	    fuzzyDelayTime->addTerm(new ShoulderTerm("D1", 20, 40, true));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D2", 20, 60));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D3", 40, 80));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D4", 60, 100));
	    fuzzyDelayTime->addTerm(new TriangularTerm("D5", 80, 120));
	    fuzzyDelayTime->addTerm(new ShoulderTerm("D6", 100, 120, false));

	    engine.addOutputLVar(fuzzyDelayTime);

	    RuleBlock* block = new RuleBlock();
	    /*block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R1 then DelayTime is D1", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R2 then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R3 then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R4 then DelayTime is D4", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R5 then DelayTime is D5", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R6 then DelayTime is D6", engine));
	    */
	    /*block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R1 then BE is D1", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R2 then BE is D2", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R3 then BE is D3", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R4 then BE is D4", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R5 then BE is D5", engine));
	    block->addRule(new MamdaniRule("if RateChannelIsCLEARcw0 is R6 then BE is D6", engine));
	    */

	    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    /*
	    block->addRule(new MamdaniRule("if SampleRate is S1 and Buffer is NEARLY_EMPTY then DelayTime is D6", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S1 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D5", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S1 and Buffer is NEARLY_HALF_FULL then DelayTime is D4", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S1 and Buffer is NEARLY_FULL then DelayTime is D3", engine));

	    block->addRule(new MamdaniRule("if SampleRate is S2 and Buffer is NEARLY_EMPTY then DelayTime is D5", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S2 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D4", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S2 and Buffer is NEARLY_HALF_FULL then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S2 and Buffer is NEARLY_FULL then DelayTime is D3", engine));

	    block->addRule(new MamdaniRule("if SampleRate is S3 and Buffer is NEARLY_EMPTY then DelayTime is D4", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S3 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S3 and Buffer is NEARLY_HALF_FULL then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S3 and Buffer is NEARLY_FULL then DelayTime is D2", engine));

	    block->addRule(new MamdaniRule("if SampleRate is S4 and Buffer is NEARLY_EMPTY then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S4 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S4 and Buffer is NEARLY_HALF_FULL then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S4 and Buffer is NEARLY_FULL then DelayTime is D2", engine));

	    block->addRule(new MamdaniRule("if SampleRate is S5 and Buffer is NEARLY_EMPTY then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S5 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S5 and Buffer is NEARLY_HALF_FULL then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S5 and Buffer is NEARLY_FULL then DelayTime is D1", engine));

	    block->addRule(new MamdaniRule("if SampleRate is S6 and Buffer is NEARLY_EMPTY then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S6 and Buffer is NEARLY_HALF_EMPTY then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S6 and Buffer is NEARLY_HALF_FULL then DelayTime is D1", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S6 and Buffer is NEARLY_FULL then DelayTime is D1", engine));
	    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	    /*
	    block->addRule(new MamdaniRule("if SampleRate is S1 then DelayTime is D6", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S2 then DelayTime is D5", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S3 then DelayTime is D4", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S4 then DelayTime is D3", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S5 then DelayTime is D2", engine));
	    block->addRule(new MamdaniRule("if SampleRate is S6 then DelayTime is D1", engine));
		*/
	    //NEARLY_EMPTY, NEARLY_HALF_EMPTY, NEARLY_HALF_FULL, NEARLY_FULL


	    engine.addRuleBlock(block);
	    rateChannelIsCLEARcw0->setInput((double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2]);
	    sampleRate->setInput(sampleRateId);
	    fuzzyBuffer->setInput(TXBuffer.size());

	    engine.process();
	    flScalar fuzzyDelayTimeOut = fuzzyDelayTime->output().defuzzify();
	    //flScalar fuzzyBEout = fuzzyBE->output().defuzzify();

	    /*
	    myfile_fuzzy << "Orginal random max: " << BE << endl;
	    myfile_fuzzy << "fuzzy random max: " << fuzzyBEout << endl;
	    myfile_fuzzy << "Delay Fuzzy Set is: " << fuzzyBE->fuzzify(fuzzyBEout) << endl;
	    myfile_fuzzy << "rateChannelIsCLEARcw0 fuzzify is: " << rateChannelIsCLEARcw0->fuzzify((double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2]) << endl;
	    myfile_fuzzy << "rateChannelIsCLEARcw0 is: " << (double)a_arrayNumberOfChannelIsCLEARcwIs0[2]/a_array_n[2] << endl;
	    myfile_fuzzy << "----------------------------------------------------------------------" << endl;
	    myfile_fuzzy.close();*/

	    myfile_fuzzy << "sampleRateId: " << sampleRateId << endl;
		myfile_fuzzy << "fuzzy random min: " << fuzzyDelayTimeOut_a << endl;
		myfile_fuzzy << "fuzzy random max: " << fuzzyDelayTimeOut << endl << endl;

		myfile_fuzzy << "fuzzyBuffer fuzzify is: " << fuzzyBuffer->fuzzify(TXBuffer.size()) << endl;
		myfile_fuzzy << "Delay Fuzzy Set is: " << fuzzyDelayTime->fuzzify(fuzzyDelayTimeOut) << endl;
		myfile_fuzzy << "sampleRateId fuzzify is: " << sampleRate->fuzzify(sampleRateId) << endl;
		myfile_fuzzy << "----------------------------------------------------------------------" << endl;
		myfile_fuzzy.close();


	//int rnd = genk_intrand(1, (1 << BE) - 1) + 1;
	//int rnd = genk_intrand(1, (1 << (int)fuzzyBEout) - 1) + 1;
	//int rnd = genk_intrand(1, fuzzyDelayTimeOut) + 1;

	if(fuzzyDelayTimeOut_a >= fuzzyDelayTimeOut)
		fuzzyDelayTimeOut_a = 1;
	//fuzzyDelayTimeOut_a
	int rnd = genk_intrand(fuzzyDelayTimeOut_a, fuzzyDelayTimeOut) + 1;
	//int rnd = genk_intrand(1, (1 << BE) - 1) + 1;

	simtime_t CCAtime = rnd * (unitBackoffPeriod * symbolLen);

	ofstream myfile2;
	openFile(myfile2,"BE");
	myfile2 << "(1 << BE): " << (1 << BE) << "   BE: " << BE << "  rnd: " << rnd << "  rnd * (unitBackoffPeriod * symbolLen): " << rnd * (unitBackoffPeriod * symbolLen) << "      (unitBackoffPeriod * symbolLen): " << unitBackoffPeriod * symbolLen << "    symbolLen: " << symbolLen << "      unitBackoffPeriod: " << unitBackoffPeriod << "      CCAtime:" << CCAtime << endl;
    myfile2.close();

	//if using slotted CSMA - need to locate backoff period boundary
	if (enableSlottedCSMA) {
		simtime_t backoffBoundary = (ceil((getClock() - currentFrameStart) / (unitBackoffPeriod * symbolLen)) -
		     (getClock() - currentFrameStart) / (unitBackoffPeriod * symbolLen)) * (unitBackoffPeriod * symbolLen);
		CCAtime += backoffBoundary;
	}

	trace() << "Random backoff value: " << rnd << ", in " << CCAtime << " seconds";

	ofstream myfile;
	openFile(myfile,"continueCSMACA");
	myfile <<"BE: " << BE << "    CCAtime:" << CCAtime  << "    numberOfIniCSMACA: " << numberOfInitiateCSMACA << "   Clock: " << getClock() << "       Buffer size: [" << TXBuffer.size() << "]" << "   SpentEnergy:["<< resMgrModule->getSpentEnergy() << "]    Loca:( "<< getNodeLocationX() << " , " << getNodeLocationY()  << " )" << endl;

	numberOfContinueCSMACA++;
	sumBackofTime+=CCAtime;

    numberOfContinueCSMACADuringOneSuperfarame++;
	sumBackofTimeDuringOneSuperfarame+=CCAtime;

	myfile <<"numberOfContinueCSMACA: " << numberOfContinueCSMACA << endl;
	myfile <<"CCAtime: " << CCAtime << endl;
	myfile <<"sumBackofTime: " << sumBackofTime << endl;
	myfile <<"sumBackofTime/numberOfContinueCSMACA: " << sumBackofTime/numberOfContinueCSMACA << endl;
	myfile <<"------------------------------------------------------------------------------------------------------" << endl;

	myfile.close();

	previosCCAtime = CCAtime;
	setTimer(PERFORM_CCA, CCAtime);
}

/* Transmit a packet by sending it to the radio */
void Mac802154a::transmitNextPacket()
{
	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCFP)
		numberOfPacketTryToSentInCFP++;
	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCAP)
		numberOfPacketTryToSentInCAP++;

	//check if transmission is allowed given current time and tx time
	double txTime = TX_TIME(nextPacket->getByteLength());
	int allowTx = 1;

	if (!(currentFrameStart + CAPend > getClock() + txTime))
		if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCAP)
			numberOfPacketTryToSentInCAPButOutsideCAP++;

	if (currentFrameStart + CAPend > getClock() + txTime) {
		// still in CAP period of the frame
		if (!enableCAP && nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET)
			allowTx = 0;
	} else if (requestGTS == 0 || GTSstart == 0) {
		// not in CAP period and not in GTS, no transmissions possible
		allowTx = 0;
	} else if (currentFrameStart + GTSstart > getClock() ||
		   currentFrameStart + GTSend < getClock() + txTime) {
		// outside GTS, no transmissions possible
		if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCFP)
			numberOfPacketTryToSentInCFPButoutsideGTS++;
		allowTx = 0;
	}

	if (!allowTx) {
		setMacState(MAC_STATE_IDLE);
		return;
	}
	//transmission is allowed, decrement retry counter and modify mac and radio states.
	nextPacketRetries--;
	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET)
		nodeSendDataPacket = true;


	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCAP){
		numberOfPacketSentCAP++;
		numberOfPacketSentCAP_MACMACa++;
		s_numberOfPacketSentCAP++;
		m_numberOfPacketSentCAP++;
		numberOfPacketSentDuringOneSuperfarameCAP++;

		ofstream myfile;
		openFile(myfile,"BEACON");
		myfile << "                   CCAtime:" <<  previosCCAtime << "  transmission is allowed    -------------------->   BE:" << BE  << "[" << numberOfBeaconReceived << "] CSMA-CA successful= " << numberOfPacketSentDuringOneSuperfarameCAP << "       NB: " << NB <<"       Buffer: [" << TXBuffer.size() << "]"  << endl;
		myfile.close();
	}

	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCFP){
		numberOfPacketSentCFP++;
		numberOfPacketSentCFP_MACMACa++;
		numberOfPacketSentDuringOneSuperfarameCFP++;

		ofstream myfile;
		openFile(myfile,"BEACON");
		myfile << "                   GTS[" << numberOfBeaconReceived << "]    Clock: " <<  getClock() << "        Buffer: [" << TXBuffer.size() << "]"  << endl;
		myfile.close();
	}

	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCFP){
		previous_x = getNodeLocationX();
		previous_y = getNodeLocationY();
		previous_z = getNodeLocationZ();

		ofstream myfile;
		openFile(myfile,"Location/transmitNextPacketforCFP");
		myfile <<  getClock() << "," << getNodeLocationX() << "," << getNodeLocationY() << endl;
		myfile.close();
	}
	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET && nodeSendDataPacketDuringCAP){
		previous_x = getNodeLocationX();
		previous_y = getNodeLocationY();
		previous_z = getNodeLocationZ();

		ofstream myfile;
		openFile(myfile,"Location/transmitNextPacketforCAP");
		myfile <<  getClock() << "," << getNodeLocationX() << "," << getNodeLocationY() << endl;
		myfile.close();
	}


	if (nextPacketResponse > 0) {
		setMacState(nextMacState);
		setTimer(ATTEMPT_TX, nextPacketResponse);
	} else {
		setMacState(MAC_STATE_IN_TX);
		setTimer(ATTEMPT_TX, txTime);
	}

	toRadioLayer(nextPacket->dup());
	toRadioLayer(createRadioCommand(SET_STATE, TX));
}

/* Create a GTS request packet and schedule it for transmission */
void Mac802154a::issueGTSrequest()
{
	if (nextPacket) {
		if (collectPacketState("NoPAN"))
			packetBreak[nextPacketState]++;
		cancelAndDelete(nextPacket);
	}

	nextPacket = new Mac802154aPacket("GTS request", MAC_LAYER_PACKET);
	nextPacket->setPANid(associatedPAN);
	nextPacket->setDstID(associatedPAN);
	nextPacket->setMac802154aPacketType(MAC_802154_GTS_REQUEST_PACKET);
	nextPacket->setSrcID(SELF_MAC_ADDRESS);
	nextPacket->setGTSlength(requestGTS);
	nextPacket->setByteLength(COMMAND_PKT_SIZE);
	initiateCSMACA(9999, MAC_STATE_WAIT_FOR_GTS, ackWaitDuration + TX_TIME(COMMAND_PKT_SIZE));
}

int Mac802154a::collectPacketState(const char *s)
{
	if (!nextPacket)
		opp_error("MAC 802.15.4 internal error: collectPacketState called while nextPacket pointer is NULL");
	if (nextPacket->getMac802154aPacketType() == MAC_802154_DATA_PACKET
	    && nextPacket->getDstID() != BROADCAST_MAC_ADDRESS) {
		if (nextPacketState.size()) {
			nextPacketState.append(",");
			nextPacketState.append(s);
		} else {
			nextPacketState = s;
		}
		//packetBreak[nextPacketState]++;
		return 1;
	}
	return 0;
}



double Mac802154a::getNodeLocationX(){
	double x = 0.0;
	cTopology *nodeTopo;
	nodeTopo = new cTopology("topo");
	nodeTopo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
	VirtualMobilityManager *nodeMobilityModule =
				check_and_cast<VirtualMobilityManager*>
				(nodeTopo->getNode(SELF_MAC_ADDRESS)->getModule()->getSubmodule("MobilityManager"));
	nodeMobilityModule->getLocation();
	x = nodeMobilityModule->getLocation().x;
	return x;
}

double Mac802154a::getNodeLocationY(){
	double y = 0.0;
	cTopology *nodeTopo;
	nodeTopo = new cTopology("topo");
	nodeTopo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
	VirtualMobilityManager *nodeMobilityModule =
				check_and_cast<VirtualMobilityManager*>
				(nodeTopo->getNode(SELF_MAC_ADDRESS)->getModule()->getSubmodule("MobilityManager"));
	nodeMobilityModule->getLocation();
	y = nodeMobilityModule->getLocation().y;
	return y;
}

double Mac802154a::getNodeLocationZ(){
	double z = 0.0;
	cTopology *nodeTopo;
	nodeTopo = new cTopology("topo");
	nodeTopo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
	VirtualMobilityManager *nodeMobilityModule =
				check_and_cast<VirtualMobilityManager*>
				(nodeTopo->getNode(SELF_MAC_ADDRESS)->getModule()->getSubmodule("MobilityManager"));
	nodeMobilityModule->getLocation();
	z = nodeMobilityModule->getLocation().z;
	return z;
}

void Mac802154a::openFile(ofstream& myfile, string folderName){
	std::string nodeId;
	std::stringstream out;
	out << SELF_MAC_ADDRESS;
	nodeId = out.str();
	string fileName = "./" + folderName + "/" + nodeId + ".txt";
	myfile.open (fileName.c_str(), ios::ate | ios::out | ios::app);
}
