//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MultipathRingsRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("multipathRingsRoutingPacketDef");
    if (!e) enums.getInstance()->add(e = new cEnum("multipathRingsRoutingPacketDef"));
    e->insert(MPRINGS_DATA_PACKET, "MPRINGS_DATA_PACKET");
    e->insert(MPRINGS_TOPOLOGY_SETUP_PACKET, "MPRINGS_TOPOLOGY_SETUP_PACKET");
);

Register_Class(MultipathRingsRoutingPacket);

MultipathRingsRoutingPacket::MultipathRingsRoutingPacket(const char *name, int kind) : RoutingPacket(name,kind)
{
    this->multipathRingsRoutingPacketKind_var = 0;
    this->sinkID_var = 0;
    this->senderLevel_var = 0;
}

MultipathRingsRoutingPacket::MultipathRingsRoutingPacket(const MultipathRingsRoutingPacket& other) : RoutingPacket(other)
{
    copy(other);
}

MultipathRingsRoutingPacket::~MultipathRingsRoutingPacket()
{
}

MultipathRingsRoutingPacket& MultipathRingsRoutingPacket::operator=(const MultipathRingsRoutingPacket& other)
{
    if (this==&other) return *this;
    RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void MultipathRingsRoutingPacket::copy(const MultipathRingsRoutingPacket& other)
{
    this->multipathRingsRoutingPacketKind_var = other.multipathRingsRoutingPacketKind_var;
    this->sinkID_var = other.sinkID_var;
    this->senderLevel_var = other.senderLevel_var;
}

void MultipathRingsRoutingPacket::parsimPack(cCommBuffer *b)
{
    RoutingPacket::parsimPack(b);
    doPacking(b,this->multipathRingsRoutingPacketKind_var);
    doPacking(b,this->sinkID_var);
    doPacking(b,this->senderLevel_var);
}

void MultipathRingsRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->multipathRingsRoutingPacketKind_var);
    doUnpacking(b,this->sinkID_var);
    doUnpacking(b,this->senderLevel_var);
}

int MultipathRingsRoutingPacket::getMultipathRingsRoutingPacketKind() const
{
    return multipathRingsRoutingPacketKind_var;
}

void MultipathRingsRoutingPacket::setMultipathRingsRoutingPacketKind(int multipathRingsRoutingPacketKind)
{
    this->multipathRingsRoutingPacketKind_var = multipathRingsRoutingPacketKind;
}

int MultipathRingsRoutingPacket::getSinkID() const
{
    return sinkID_var;
}

void MultipathRingsRoutingPacket::setSinkID(int sinkID)
{
    this->sinkID_var = sinkID;
}

int MultipathRingsRoutingPacket::getSenderLevel() const
{
    return senderLevel_var;
}

void MultipathRingsRoutingPacket::setSenderLevel(int senderLevel)
{
    this->senderLevel_var = senderLevel;
}

class MultipathRingsRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    MultipathRingsRoutingPacketDescriptor();
    virtual ~MultipathRingsRoutingPacketDescriptor();

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

Register_ClassDescriptor(MultipathRingsRoutingPacketDescriptor);

MultipathRingsRoutingPacketDescriptor::MultipathRingsRoutingPacketDescriptor() : cClassDescriptor("MultipathRingsRoutingPacket", "RoutingPacket")
{
}

MultipathRingsRoutingPacketDescriptor::~MultipathRingsRoutingPacketDescriptor()
{
}

bool MultipathRingsRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MultipathRingsRoutingPacket *>(obj)!=NULL;
}

const char *MultipathRingsRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MultipathRingsRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int MultipathRingsRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *MultipathRingsRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "multipathRingsRoutingPacketKind",
        "sinkID",
        "senderLevel",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int MultipathRingsRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "multipathRingsRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkID")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderLevel")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MultipathRingsRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *MultipathRingsRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "multipathRingsRoutingPacketDef";
            return NULL;
        default: return NULL;
    }
}

int MultipathRingsRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MultipathRingsRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMultipathRingsRoutingPacketKind());
        case 1: return long2string(pp->getSinkID());
        case 2: return long2string(pp->getSenderLevel());
        default: return "";
    }
}

bool MultipathRingsRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setMultipathRingsRoutingPacketKind(string2long(value)); return true;
        case 1: pp->setSinkID(string2long(value)); return true;
        case 2: pp->setSenderLevel(string2long(value)); return true;
        default: return false;
    }
}

const char *MultipathRingsRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *MultipathRingsRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


