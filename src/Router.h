#pragma once
#include "util/tc_clientsocket.h"
#include "util/tc_epoll_server.h"

typedef char u8_t;
typedef uint32_t u32_t;

struct APIProtoHeader
{
    u8_t szHeaderFlag[2];
    u32_t nProtoID;
    u8_t nProtoFmtType;
    u8_t nProtoVer;
    u32_t nSerialNo;
    u32_t nBodyLen;
    u8_t arrBodySHA1[20];
    u8_t arrReserved[8];
} __attribute__((packed));

enum
{
    PACKET_LESS = 0,
    PACKET_FULL = 1,
    PACKET_ERR = -1,
};

class Router
{
public:
    Router();

    int DoRequest(uint32_t nProtoID, const string& sPbReq, string& sPbRsp);

private:
    // 加包头
    string AddHeader(uint32_t nProtoID, const string& sPbReq);

    // 判断包体是否完整
    static int parseStream(string& in, string& out);

private:
    tars::TC_TCPClient m_tcpClient;

    string m_InputStream;
    uint32_t m_SerialNo;
};