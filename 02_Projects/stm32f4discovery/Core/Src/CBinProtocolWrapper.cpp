#include "CBinProtocolWrapper.h"
#include "CBinProtocol.h"

extern "C" void BinProtocolInit()
{
  CBinProtocol::GetInstance().Init();
}

extern "C" void BinProtocolParse()
{
  CBinProtocol::GetInstance().Parse();
}

extern "C" void BinProtocolFill(const uint8_t *buf, size_t buf_len)
{
  CBinProtocol::GetInstance().Fill(buf, buf_len);
}
