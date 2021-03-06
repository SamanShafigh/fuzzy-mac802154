//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/communication/mac/Mac802154a/Mac802154aPacket.msg.
//

#ifndef _Mac802154aPACKET_M_H_
#define _Mac802154aPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "MacPacket_m.h"
// }}



/**
 * Enum generated from <tt>src/node/communication/mac/Mac802154a/Mac802154aPacket.msg</tt> by opp_msgc.
 * <pre>
 * enum Mac802154aPacket_type {
 * 	MAC_802154_BEACON_PACKET = 1001;
 * 	MAC_802154_ASSOCIATE_PACKET = 1002;
 * 	MAC_802154_DATA_PACKET = 1003;
 * 	MAC_802154_ACK_PACKET = 1004;
 * 	MAC_802154_GTS_REQUEST_PACKET = 1005;
 * }
 * </pre>
 */
enum Mac802154aPacket_type {
    MAC_802154_BEACON_PACKET = 1001,
    MAC_802154_ASSOCIATE_PACKET = 1002,
    MAC_802154_DATA_PACKET = 1003,
    MAC_802154_ACK_PACKET = 1004,
    MAC_802154_GTS_REQUEST_PACKET = 1005
};

/**
 * Struct generated from src/node/communication/mac/Mac802154a/Mac802154aPacket.msg by opp_msgc.
 */
struct GTSspecA
{
    GTSspecA();
    int owner;
    int start;
    int length;
};

void doPacking(cCommBuffer *b, GTSspecA& a);
void doUnpacking(cCommBuffer *b, GTSspecA& a);

/**
 * Class generated from <tt>src/node/communication/mac/Mac802154a/Mac802154aPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet Mac802154aPacket extends MacPacket {
 * 	int Mac802154aPacketType enum (Mac802154aPacket_type);
 * 	int PANid;
 * 	int srcID;
 * 	int dstID;
 * 
 * 	
 * 	int beaconOrder;
 * 	int frameOrder;
 * 	int BSN;
 * 	int CAPlength;
 * 	int GTSlength;
 * 	GTSspecA GTSlist[];
 * }
 * </pre>
 */
class Mac802154aPacket : public ::MacPacket
{
  protected:
    int Mac802154aPacketType_var;
    int PANid_var;
    int srcID_var;
    int dstID_var;
    int beaconOrder_var;
    int frameOrder_var;
    int BSN_var;
    int CAPlength_var;
    int GTSlength_var;
    GTSspecA *GTSlist_var; // array ptr
    unsigned int GTSlist_arraysize;

  private:
    void copy(const Mac802154aPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Mac802154aPacket&);

  public:
    Mac802154aPacket(const char *name=NULL, int kind=0);
    Mac802154aPacket(const Mac802154aPacket& other);
    virtual ~Mac802154aPacket();
    Mac802154aPacket& operator=(const Mac802154aPacket& other);
    virtual Mac802154aPacket *dup() const {return new Mac802154aPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getMac802154aPacketType() const;
    virtual void setMac802154aPacketType(int Mac802154aPacketType);
    virtual int getPANid() const;
    virtual void setPANid(int PANid);
    virtual int getSrcID() const;
    virtual void setSrcID(int srcID);
    virtual int getDstID() const;
    virtual void setDstID(int dstID);
    virtual int getBeaconOrder() const;
    virtual void setBeaconOrder(int beaconOrder);
    virtual int getFrameOrder() const;
    virtual void setFrameOrder(int frameOrder);
    virtual int getBSN() const;
    virtual void setBSN(int BSN);
    virtual int getCAPlength() const;
    virtual void setCAPlength(int CAPlength);
    virtual int getGTSlength() const;
    virtual void setGTSlength(int GTSlength);
    virtual void setGTSlistArraySize(unsigned int size);
    virtual unsigned int getGTSlistArraySize() const;
    virtual GTSspecA& getGTSlist(unsigned int k);
    virtual const GTSspecA& getGTSlist(unsigned int k) const {return const_cast<Mac802154aPacket*>(this)->getGTSlist(k);}
    virtual void setGTSlist(unsigned int k, const GTSspecA& GTSlist);
};

inline void doPacking(cCommBuffer *b, Mac802154aPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Mac802154aPacket& obj) {obj.parsimUnpack(b);}


#endif // _Mac802154aPACKET_M_H_
