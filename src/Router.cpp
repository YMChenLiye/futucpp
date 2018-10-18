#include "Router.h"
#include "sha1.h"

Router::Router()
{
    m_SerialNo = 0;
    m_tcpClient.init("10.104.203.88", 11111, 3000);
}

int Router::DoRequest(uint32_t nProtoID, const string& sPbReq, string& sPbRsp)
{
    string sBuf = AddHeader(nProtoID, sPbReq);
    m_tcpClient.send(sBuf.c_str(), sBuf.length());
    cout << "send already, sBuf = " << sBuf << endl;

    // 接下来接收回包
    char* sBuff = new char[10000];
    while (true)
    {
        size_t iRecv = 0;
        int iRet = m_tcpClient.recv(sBuff, iRecv);
        if (iRet < 0)
        {
            cerr << "iRet = " << iRet << "iRecv = " << iRecv << endl;
            break;
        }
        else
        {
            string sRecv(sBuff, iRecv);
            m_InputStream += sRecv;
            string sOut;
            int ok = parseStream(m_InputStream, sOut);
            if (ok == PACKET_FULL)
            {
                cout << sOut << endl;
                break;
            }
        }
    }
}

string Router::AddHeader(uint32_t nProtoID, const string& sPbReq)
{
    // 构造发送数据
    APIProtoHeader stHeader;
    ::memset(&stHeader, 0, sizeof(APIProtoHeader));
    stHeader.szHeaderFlag[0] = 'F';
    stHeader.szHeaderFlag[1] = 'T';
    stHeader.nProtoID = nProtoID;
    stHeader.nProtoFmtType = 0;  // pb
    stHeader.nProtoVer = 0;
    stHeader.nSerialNo = ++m_SerialNo;
    stHeader.nBodyLen = sPbReq.length();
    string sha11 = sha1(sPbReq);
    cout << sha11 << endl;
    ::memcpy(stHeader.arrBodySHA1, sha11.c_str(), 20);

    size_t totalSize = sizeof(APIProtoHeader) + stHeader.nBodyLen;

    char* sBuff = new char[2 * totalSize];
    ::memcpy(sBuff, &stHeader, sizeof(APIProtoHeader));
    char* sNext = sBuff + sizeof(APIProtoHeader);
    ::memcpy(sNext, sPbReq.c_str(), sPbReq.length());
    return string(sBuff, totalSize);
}

int Router::parseStream(string& in, string& out)
{
    if (in.length() < sizeof(APIProtoHeader))
    {
        return PACKET_LESS;
    }

    APIProtoHeader stHeader;

    ::memcpy(&stHeader, in.c_str(), sizeof(APIProtoHeader));

    size_t totalPackSize = stHeader.nBodyLen + sizeof(APIProtoHeader);

    if (in.length() < totalPackSize)
    {
        return PACKET_LESS;
    }

    out = in.substr(0, totalPackSize);

    in = in.substr(totalPackSize);

    return PACKET_FULL;
}
