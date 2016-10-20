//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/communication/mac/Mac802154a/Mac802154aPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Mac802154aPacket_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("Mac802154aPacket_type");
    if (!e) enums.getInstance()->add(e = new cEnum("Mac802154aPacket_type"));
    e->insert(MAC_802154_BEACON_PACKET, "MAC_802154_BEACON_PACKET");
    e->insert(MAC_802154_ASSOCIATE_PACKET, "MAC_802154_ASSOCIATE_PACKET");
    e->insert(MAC_802154_DATA_PACKET, "MAC_802154_DATA_PACKET");
    e->insert(MAC_802154_ACK_PACKET, "MAC_802154_ACK_PACKET");
    e->insert(MAC_802154_GTS_REQUEST_PACKET, "MAC_802154_GTS_REQUEST_PACKET");
);

GTSspecA::GTSspecA()
{
    owner = 0;
    start = 0;
    length = 0;
}

void doPacking(cCommBuffer *b, GTSspecA& a)
{
    doPacking(b,a.owner);
    doPacking(b,a.start);
    doPacking(b,a.length);
}

void doUnpacking(cCommBuffer *b, GTSspecA& a)
{
    doUnpacking(b,a.owner);
    doUnpacking(b,a.start);
    doUnpacking(b,a.length);
}

class GTSspecDescriptorA : public cClassDescriptor
{
  public:
    GTSspecDescriptorA();
    virtual ~GTSspecDescriptorA();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(GTSspecDescriptorA);

GTSspecDescriptorA::GTSspecDescriptorA() : cClassDescriptor("GTSspecA", "")
{
}

GTSspecDescriptorA::~GTSspecDescriptorA()
{
}

bool GTSspecDescriptorA::doesSupport(cObject *obj) const
{
    return dynamic_cast<GTSspecA *>(obj)!=NULL;
}

const char *GTSspecDescriptorA::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GTSspecDescriptorA::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int GTSspecDescriptorA::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *GTSspecDescriptorA::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "owner",
        "start",
        "length",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int GTSspecDescriptorA::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "owner")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "start")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GTSspecDescriptorA::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *GTSspecDescriptorA::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int GTSspecDescriptorA::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GTSspecA *pp = (GTSspecA *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GTSspecDescriptorA::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GTSspecA *pp = (GTSspecA *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->owner);
        case 1: return long2string(pp->start);
        case 2: return long2string(pp->length);
        default: return "";
    }
}

bool GTSspecDescriptorA::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GTSspecA *pp = (GTSspecA *)object; (void)pp;
    switch (field) {
        case 0: pp->owner = string2long(value); return true;
        case 1: pp->start = string2long(value); return true;
        case 2: pp->length = string2long(value); return true;
        default: return false;
    }
}

const char *GTSspecDescriptorA::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *GTSspecDescriptorA::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GTSspecA *pp = (GTSspecA *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Mac802154aPacket);

Mac802154aPacket::Mac802154aPacket(const char *name, int kind) : MacPacket(name,kind)
{
    this->Mac802154aPacketType_var = 0;
    this->PANid_var = 0;
    this->srcID_var = 0;
    this->dstID_var = 0;
    this->beaconOrder_var = 0;
    this->frameOrder_var = 0;
    this->BSN_var = 0;
    this->CAPlength_var = 0;
    this->GTSlength_var = 0;
    GTSlist_arraysize = 0;
    this->GTSlist_var = 0;
}

Mac802154aPacket::Mac802154aPacket(const Mac802154aPacket& other) : MacPacket(other)
{
    GTSlist_arraysize = 0;
    this->GTSlist_var = 0;
    copy(other);
}

Mac802154aPacket::~Mac802154aPacket()
{
    delete [] GTSlist_var;
}

Mac802154aPacket& Mac802154aPacket::operator=(const Mac802154aPacket& other)
{
    if (this==&other) return *this;
    MacPacket::operator=(other);
    copy(other);
    return *this;
}

void Mac802154aPacket::copy(const Mac802154aPacket& other)
{
    this->Mac802154aPacketType_var = other.Mac802154aPacketType_var;
    this->PANid_var = other.PANid_var;
    this->srcID_var = other.srcID_var;
    this->dstID_var = other.dstID_var;
    this->beaconOrder_var = other.beaconOrder_var;
    this->frameOrder_var = other.frameOrder_var;
    this->BSN_var = other.BSN_var;
    this->CAPlength_var = other.CAPlength_var;
    this->GTSlength_var = other.GTSlength_var;
    delete [] this->GTSlist_var;
    this->GTSlist_var = (other.GTSlist_arraysize==0) ? NULL : new GTSspecA[other.GTSlist_arraysize];
    GTSlist_arraysize = other.GTSlist_arraysize;
    for (unsigned int i=0; i<GTSlist_arraysize; i++)
        this->GTSlist_var[i] = other.GTSlist_var[i];
}

void Mac802154aPacket::parsimPack(cCommBuffer *b)
{
    MacPacket::parsimPack(b);
    doPacking(b,this->Mac802154aPacketType_var);
    doPacking(b,this->PANid_var);
    doPacking(b,this->srcID_var);
    doPacking(b,this->dstID_var);
    doPacking(b,this->beaconOrder_var);
    doPacking(b,this->frameOrder_var);
    doPacking(b,this->BSN_var);
    doPacking(b,this->CAPlength_var);
    doPacking(b,this->GTSlength_var);
    b->pack(GTSlist_arraysize);
    doPacking(b,this->GTSlist_var,GTSlist_arraysize);
}

void Mac802154aPacket::parsimUnpack(cCommBuffer *b)
{
    MacPacket::parsimUnpack(b);
    doUnpacking(b,this->Mac802154aPacketType_var);
    doUnpacking(b,this->PANid_var);
    doUnpacking(b,this->srcID_var);
    doUnpacking(b,this->dstID_var);
    doUnpacking(b,this->beaconOrder_var);
    doUnpacking(b,this->frameOrder_var);
    doUnpacking(b,this->BSN_var);
    doUnpacking(b,this->CAPlength_var);
    doUnpacking(b,this->GTSlength_var);
    delete [] this->GTSlist_var;
    b->unpack(GTSlist_arraysize);
    if (GTSlist_arraysize==0) {
        this->GTSlist_var = 0;
    } else {
        this->GTSlist_var = new GTSspecA[GTSlist_arraysize];
        doUnpacking(b,this->GTSlist_var,GTSlist_arraysize);
    }
}

int Mac802154aPacket::getMac802154aPacketType() const
{
    return Mac802154aPacketType_var;
}

void Mac802154aPacket::setMac802154aPacketType(int Mac802154aPacketType)
{
    this->Mac802154aPacketType_var = Mac802154aPacketType;
}

int Mac802154aPacket::getPANid() const
{
    return PANid_var;
}

void Mac802154aPacket::setPANid(int PANid)
{
    this->PANid_var = PANid;
}

int Mac802154aPacket::getSrcID() const
{
    return srcID_var;
}

void Mac802154aPacket::setSrcID(int srcID)
{
    this->srcID_var = srcID;
}

int Mac802154aPacket::getDstID() const
{
    return dstID_var;
}

void Mac802154aPacket::setDstID(int dstID)
{
    this->dstID_var = dstID;
}

int Mac802154aPacket::getBeaconOrder() const
{
    return beaconOrder_var;
}

void Mac802154aPacket::setBeaconOrder(int beaconOrder)
{
    this->beaconOrder_var = beaconOrder;
}

int Mac802154aPacket::getFrameOrder() const
{
    return frameOrder_var;
}

void Mac802154aPacket::setFrameOrder(int frameOrder)
{
    this->frameOrder_var = frameOrder;
}

int Mac802154aPacket::getBSN() const
{
    return BSN_var;
}

void Mac802154aPacket::setBSN(int BSN)
{
    this->BSN_var = BSN;
}

int Mac802154aPacket::getCAPlength() const
{
    return CAPlength_var;
}

void Mac802154aPacket::setCAPlength(int CAPlength)
{
    this->CAPlength_var = CAPlength;
}

int Mac802154aPacket::getGTSlength() const
{
    return GTSlength_var;
}

void Mac802154aPacket::setGTSlength(int GTSlength)
{
    this->GTSlength_var = GTSlength;
}

void Mac802154aPacket::setGTSlistArraySize(unsigned int size)
{
    GTSspecA *GTSlist_var2 = (size==0) ? NULL : new GTSspecA[size];
    unsigned int sz = GTSlist_arraysize < size ? GTSlist_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        GTSlist_var2[i] = this->GTSlist_var[i];
    GTSlist_arraysize = size;
    delete [] this->GTSlist_var;
    this->GTSlist_var = GTSlist_var2;
}

unsigned int Mac802154aPacket::getGTSlistArraySize() const
{
    return GTSlist_arraysize;
}

GTSspecA& Mac802154aPacket::getGTSlist(unsigned int k)
{
    if (k>=GTSlist_arraysize) throw cRuntimeError("Array of size %d indexed by %d", GTSlist_arraysize, k);
    return GTSlist_var[k];
}

void Mac802154aPacket::setGTSlist(unsigned int k, const GTSspecA& GTSlist)
{
    if (k>=GTSlist_arraysize) throw cRuntimeError("Array of size %d indexed by %d", GTSlist_arraysize, k);
    this->GTSlist_var[k] = GTSlist;
}

class Mac802154aPacketDescriptor : public cClassDescriptor
{
  public:
    Mac802154aPacketDescriptor();
    virtual ~Mac802154aPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Mac802154aPacketDescriptor);

Mac802154aPacketDescriptor::Mac802154aPacketDescriptor() : cClassDescriptor("Mac802154aPacket", "MacPacket")
{
}

Mac802154aPacketDescriptor::~Mac802154aPacketDescriptor()
{
}

bool Mac802154aPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Mac802154aPacket *>(obj)!=NULL;
}

const char *Mac802154aPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Mac802154aPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int Mac802154aPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *Mac802154aPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "Mac802154aPacketType",
        "PANid",
        "srcID",
        "dstID",
        "beaconOrder",
        "frameOrder",
        "BSN",
        "CAPlength",
        "GTSlength",
        "GTSlist",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int Mac802154aPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='M' && strcmp(fieldName, "Mac802154aPacketType")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANid")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcID")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstID")==0) return base+3;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconOrder")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameOrder")==0) return base+5;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSN")==0) return base+6;
    if (fieldName[0]=='C' && strcmp(fieldName, "CAPlength")==0) return base+7;
    if (fieldName[0]=='G' && strcmp(fieldName, "GTSlength")==0) return base+8;
    if (fieldName[0]=='G' && strcmp(fieldName, "GTSlist")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Mac802154aPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "GTSspecA",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *Mac802154aPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Mac802154aPacket_type";
            return NULL;
        default: return NULL;
    }
}

int Mac802154aPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Mac802154aPacket *pp = (Mac802154aPacket *)object; (void)pp;
    switch (field) {
        case 9: return pp->getGTSlistArraySize();
        default: return 0;
    }
}

std::string Mac802154aPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Mac802154aPacket *pp = (Mac802154aPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMac802154aPacketType());
        case 1: return long2string(pp->getPANid());
        case 2: return long2string(pp->getSrcID());
        case 3: return long2string(pp->getDstID());
        case 4: return long2string(pp->getBeaconOrder());
        case 5: return long2string(pp->getFrameOrder());
        case 6: return long2string(pp->getBSN());
        case 7: return long2string(pp->getCAPlength());
        case 8: return long2string(pp->getGTSlength());
        case 9: {std::stringstream out; out << pp->getGTSlist(i); return out.str();}
        default: return "";
    }
}

bool Mac802154aPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Mac802154aPacket *pp = (Mac802154aPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setMac802154aPacketType(string2long(value)); return true;
        case 1: pp->setPANid(string2long(value)); return true;
        case 2: pp->setSrcID(string2long(value)); return true;
        case 3: pp->setDstID(string2long(value)); return true;
        case 4: pp->setBeaconOrder(string2long(value)); return true;
        case 5: pp->setFrameOrder(string2long(value)); return true;
        case 6: pp->setBSN(string2long(value)); return true;
        case 7: pp->setCAPlength(string2long(value)); return true;
        case 8: pp->setGTSlength(string2long(value)); return true;
        default: return false;
    }
}

const char *Mac802154aPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "GTSspecA",
    };
    return (field>=0 && field<10) ? fieldStructNames[field] : NULL;
}

void *Mac802154aPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Mac802154aPacket *pp = (Mac802154aPacket *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getGTSlist(i)); break;
        default: return NULL;
    }
}


