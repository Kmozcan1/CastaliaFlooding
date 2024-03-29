//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/floodingApplication/FloodingPacket.msg.
//

#ifndef _FLOODINGPACKET_M_H_
#define _FLOODINGPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "ApplicationPacket_m.h"
// }}

/**
 * Class generated from <tt>src/node/application/floodingApplication/FloodingPacket.msg:7</tt> by nedtool.
 * <pre>
 * packet FloodingPacket extends ApplicationPacket
 * {
 *     int sourceID;
 *     string packetID;
 * }
 * </pre>
 */
class FloodingPacket : public ::ApplicationPacket
{
  protected:
    int sourceID_var;
    opp_string packetID_var;

  private:
    void copy(const FloodingPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FloodingPacket&);

  public:
    FloodingPacket(const char *name=NULL, int kind=0);
    FloodingPacket(const FloodingPacket& other);
    virtual ~FloodingPacket();
    FloodingPacket& operator=(const FloodingPacket& other);
    virtual FloodingPacket *dup() const {return new FloodingPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getSourceID() const;
    virtual void setSourceID(int sourceID);
    virtual const char * getPacketID() const;
    virtual void setPacketID(const char * packetID);
};

inline void doPacking(cCommBuffer *b, FloodingPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, FloodingPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _FLOODINGPACKET_M_H_

