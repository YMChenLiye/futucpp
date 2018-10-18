#include "Common.pb.h"
#include <iostream>
#include "Router.h"
#include "InitConnect.pb.h"

using namespace std;

int main()
{
    Common::PacketID st;
    cout << sizeof(APIProtoHeader) << endl;
    Router stRouter;

    InitConnect::Request stReq;
    ::InitConnect::C2S* pC2S = stReq.mutable_c2s();
    pC2S->set_clientver(103);
    pC2S->set_clientid("12");
    pC2S->set_recvnotify(false);
    cout << "stReq = " << stReq.DebugString() << endl;

    string sReq;
    stReq.SerializeToString(&sReq);
    string sOut;
    stRouter.DoRequest(1001, sReq, sOut);
    cout << "hello,world" << endl;
}