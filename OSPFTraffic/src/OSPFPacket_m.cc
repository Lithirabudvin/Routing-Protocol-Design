//
// Generated file, do not edit! Created by opp_msgtool 6.1 from OSPFPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "OSPFPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace ospftraffic {

Register_Class(OSPFPacket)

OSPFPacket::OSPFPacket(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

OSPFPacket::OSPFPacket(const OSPFPacket& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

OSPFPacket::~OSPFPacket()
{
    delete [] this->hopTrace;
}

OSPFPacket& OSPFPacket::operator=(const OSPFPacket& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void OSPFPacket::copy(const OSPFPacket& other)
{
    this->srcId = other.srcId;
    this->destId = other.destId;
    this->payload = other.payload;
    delete [] this->hopTrace;
    this->hopTrace = (other.hopTrace_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.hopTrace_arraysize];
    hopTrace_arraysize = other.hopTrace_arraysize;
    for (size_t i = 0; i < hopTrace_arraysize; i++) {
        this->hopTrace[i] = other.hopTrace[i];
    }
}

void OSPFPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->srcId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->payload);
    b->pack(hopTrace_arraysize);
    doParsimArrayPacking(b,this->hopTrace,hopTrace_arraysize);
}

void OSPFPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->srcId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->payload);
    delete [] this->hopTrace;
    b->unpack(hopTrace_arraysize);
    if (hopTrace_arraysize == 0) {
        this->hopTrace = nullptr;
    } else {
        this->hopTrace = new ::omnetpp::opp_string[hopTrace_arraysize];
        doParsimArrayUnpacking(b,this->hopTrace,hopTrace_arraysize);
    }
}

int OSPFPacket::getSrcId() const
{
    return this->srcId;
}

void OSPFPacket::setSrcId(int srcId)
{
    this->srcId = srcId;
}

int OSPFPacket::getDestId() const
{
    return this->destId;
}

void OSPFPacket::setDestId(int destId)
{
    this->destId = destId;
}

const char * OSPFPacket::getPayload() const
{
    return this->payload.c_str();
}

void OSPFPacket::setPayload(const char * payload)
{
    this->payload = payload;
}

size_t OSPFPacket::getHopTraceArraySize() const
{
    return hopTrace_arraysize;
}

const char * OSPFPacket::getHopTrace(size_t k) const
{
    if (k >= hopTrace_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hopTrace_arraysize, (unsigned long)k);
    return this->hopTrace[k].c_str();
}

void OSPFPacket::setHopTraceArraySize(size_t newSize)
{
    ::omnetpp::opp_string *hopTrace2 = (newSize==0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t minSize = hopTrace_arraysize < newSize ? hopTrace_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        hopTrace2[i] = this->hopTrace[i];
    delete [] this->hopTrace;
    this->hopTrace = hopTrace2;
    hopTrace_arraysize = newSize;
}

void OSPFPacket::setHopTrace(size_t k, const char * hopTrace)
{
    if (k >= hopTrace_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hopTrace_arraysize, (unsigned long)k);
    this->hopTrace[k] = hopTrace;
}

void OSPFPacket::insertHopTrace(size_t k, const char * hopTrace)
{
    if (k > hopTrace_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hopTrace_arraysize, (unsigned long)k);
    size_t newSize = hopTrace_arraysize + 1;
    ::omnetpp::opp_string *hopTrace2 = new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hopTrace2[i] = this->hopTrace[i];
    hopTrace2[k] = hopTrace;
    for (i = k + 1; i < newSize; i++)
        hopTrace2[i] = this->hopTrace[i-1];
    delete [] this->hopTrace;
    this->hopTrace = hopTrace2;
    hopTrace_arraysize = newSize;
}

void OSPFPacket::appendHopTrace(const char * hopTrace)
{
    insertHopTrace(hopTrace_arraysize, hopTrace);
}

void OSPFPacket::eraseHopTrace(size_t k)
{
    if (k >= hopTrace_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hopTrace_arraysize, (unsigned long)k);
    size_t newSize = hopTrace_arraysize - 1;
    ::omnetpp::opp_string *hopTrace2 = (newSize == 0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hopTrace2[i] = this->hopTrace[i];
    for (i = k; i < newSize; i++)
        hopTrace2[i] = this->hopTrace[i+1];
    delete [] this->hopTrace;
    this->hopTrace = hopTrace2;
    hopTrace_arraysize = newSize;
}

class OSPFPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcId,
        FIELD_destId,
        FIELD_payload,
        FIELD_hopTrace,
    };
  public:
    OSPFPacketDescriptor();
    virtual ~OSPFPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(OSPFPacketDescriptor)

OSPFPacketDescriptor::OSPFPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ospftraffic::OSPFPacket)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

OSPFPacketDescriptor::~OSPFPacketDescriptor()
{
    delete[] propertyNames;
}

bool OSPFPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OSPFPacket *>(obj)!=nullptr;
}

const char **OSPFPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *OSPFPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int OSPFPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int OSPFPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_payload
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_hopTrace
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *OSPFPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcId",
        "destId",
        "payload",
        "hopTrace",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int OSPFPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopTrace") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *OSPFPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_srcId
        "int",    // FIELD_destId
        "string",    // FIELD_payload
        "string",    // FIELD_hopTrace
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **OSPFPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *OSPFPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int OSPFPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopTrace: return pp->getHopTraceArraySize();
        default: return 0;
    }
}

void OSPFPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopTrace: pp->setHopTraceArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'OSPFPacket'", field);
    }
}

const char *OSPFPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OSPFPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: return long2string(pp->getSrcId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        case FIELD_hopTrace: return oppstring2string(pp->getHopTrace(i));
        default: return "";
    }
}

void OSPFPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: pp->setSrcId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        case FIELD_hopTrace: pp->setHopTrace(i,(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OSPFPacket'", field);
    }
}

omnetpp::cValue OSPFPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: return pp->getSrcId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_payload: return pp->getPayload();
        case FIELD_hopTrace: return pp->getHopTrace(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'OSPFPacket' as cValue -- field index out of range?", field);
    }
}

void OSPFPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: pp->setSrcId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        case FIELD_hopTrace: pp->setHopTrace(i,value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OSPFPacket'", field);
    }
}

const char *OSPFPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr OSPFPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void OSPFPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    OSPFPacket *pp = omnetpp::fromAnyPtr<OSPFPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OSPFPacket'", field);
    }
}

}  // namespace ospftraffic

namespace omnetpp {

}  // namespace omnetpp

