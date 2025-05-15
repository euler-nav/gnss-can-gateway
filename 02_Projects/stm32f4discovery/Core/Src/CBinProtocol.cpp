/**
 * @file CBinProtocol.cpp
 * @brief Implementation of the binary protocol parser class.
 *
 * THIS FILE WAS AUTOMATICALLY GENERATED FROM
 * A TEMPLATE AND A JSON CONFIGURATION FILE
 *
 * @date 20.03.2025 at 10:07:55
 */

#include "CBinProtocol.h"

CBinProtocol& CBinProtocol::GetInstance()
{
  static CBinProtocol soRteInstance;
  return soRteInstance;
}

CBinProtocol::CBinProtocol()
{
}

void CBinProtocol::Init()
{
	buffer_.allocate(RB_BUFFER_SZ);
}

void CBinProtocol::Fill(const uint8_t *buf, size_t buf_len)
{
  buffer_.push_back(buf, buf_len);
}

void CBinProtocol::Parse()
{
  uint8_t bytes[RB_BUFFER_SZ];
  SMessageDataHeader *pHdr = reinterpret_cast<SMessageDataHeader*>(bytes);

  if (findNextMessageHeader(bytes))
	{
    size_t tot_len = static_cast<size_t>(pHdr->uMsgLen + CKSUM_SZ);
    while (buffer_.space_used() >= tot_len)
    {
      if (tot_len == buffer_.pop_front(&bytes[sizeof(SMessageDataHeader)], tot_len))
      {
        uint8_t ck_a, ck_b, exp_a, exp_b;
        calculateChecksum(bytes, sizeof(SMessageDataHeader) + pHdr->uMsgLen, &ck_a, &ck_b);
        exp_a = bytes[sizeof(SMessageDataHeader) + pHdr->uMsgLen];
        exp_b = bytes[sizeof(SMessageDataHeader) + pHdr->uMsgLen + 1];

        /* Checksum verification */
        if ((ck_a == exp_a) && (ck_b == exp_b))
        {
          CBinProtocol::EMessageIds id = static_cast<CBinProtocol::EMessageIds>(pHdr->uMsgId);
          decodeMessage(bytes, id);
        }
        else
        {
          //++_statistics._cksum_failures;
        }
      }
    }
	}
}

/*******************************************************************************/
/*******************************************************************************/
bool CBinProtocol::findNextMessageHeader(uint8_t* data)
{
	bool result{false};

	while (buffer_.space_used() >= sizeof(CBinProtocol::SMessageHeader))
	{
		uint8_t sync_byte{0U};

		if (1 == buffer_.pop_front(&sync_byte, 1))
		{
			if (SMessageHeader::uMarker1_ == sync_byte)
			{
				sync_byte = 0U;

				if (1 == buffer_.pop_front(&sync_byte, 1))
				{
					if (SMessageHeader::uMarker2_ == sync_byte)
					{
				    /* Retrieve header data */
					  buffer_.pop_front(&data[0], sizeof(((SMessageDataHeader*)0)->uMsgClass));
            buffer_.pop_front(&data[1], sizeof(((SMessageDataHeader*)0)->uMsgId));
            buffer_.pop_front(&data[2], sizeof(((SMessageDataHeader*)0)->uMsgLen));

					  result = true;
						break;
					}
				}
			}
		}
	}

	return result;
}

void CBinProtocol::decodeMessage(const uint8_t* data, CBinProtocol::EMessageIds messsage_id)
{
  switch (messsage_id)
  {
    case CBinProtocol::EMessageIds::eNAV_PVT:
      /* Handle UBX-NAV-PVT message */
      break;
    case CBinProtocol::EMessageIds::eNAV_EOE:
      /* Handle UBX-NAV-EOE message */
      break;
    default:
      break;
  }
}

void CBinProtocol::calculateChecksum(uint8_t *data, uint16_t length, uint8_t *ck_a, uint8_t *ck_b)
{
  *ck_a = 0;
  *ck_b = 0;

  for (uint16_t i = 0; i < length; i++)
  {
      *ck_a += data[i];
      *ck_b += *ck_a;
  }
}
