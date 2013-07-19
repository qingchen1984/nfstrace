//------------------------------------------------------------------------------
// Author: Dzianis Huznou
// Description: Base structure for nfs-info.
// Copyright (c) 2013 EPAM Systems. All Rights Reserved.
//------------------------------------------------------------------------------
#ifndef NFS_OPERATION_H
#define NFS_OPERATION_H
//------------------------------------------------------------------------------
#include <cassert>
#include <memory>

#include <sys/time.h>

#include "../../auxiliary/session.h"
#include "../rpc/rpc_struct.h"
//------------------------------------------------------------------------------
using namespace NST::filter::rpc;

using NST::auxiliary::Session;
//------------------------------------------------------------------------------
namespace NST
{
namespace filter
{
namespace NFS3
{

class NFSOperation
{
public:
    typedef NST::auxiliary::Session Session;

    NFSOperation(const RPCCall* c, const RPCReply* r, const Session* s) : call(c), reply(r), session(s)
    {
    }
    ~NFSOperation()
    {
        delete call;
        delete reply;
    }

    inline const RPCCall* get_call() const
    {
        return call;
    }
    inline const RPCReply* get_reply() const
    {
        return reply;
    }
    inline const Session* get_session() const
    {
        return session;
    }
    inline timeval latency() const
    {
        timeval diff;
        timerclear(&diff);
        if(call && reply)
        {
            timersub(&reply->get_time(), &call->get_time(), &diff);
        }
        return diff;
    }

private:
    NFSOperation(const NFSOperation&);
    void operator=(const NFSOperation&);

    const RPCCall*  call;
    const RPCReply* reply;
    const Session*  session;
};

} // namespace NFS3
} // namespace filter
} // namespace NST
//------------------------------------------------------------------------------
#endif//NFS_OPERATION_H
//------------------------------------------------------------------------------