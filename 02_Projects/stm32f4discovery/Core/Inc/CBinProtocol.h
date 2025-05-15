/**
 * @file CBinProtocol.h
 * @brief Declaration of the binary protocol parser class.
 *
 * THIS FILE WAS AUTOMATICALLY GENERATED FROM
 * A TEMPLATE AND A JSON CONFIGURATION FILE
 *
 * @date 20.03.2025 at 10:07:55
 */

#ifndef C_BIN_PROT_H
#define C_BIN_PROT_H

#include <stdint.h>

#include "RingBuffer.h"

#define RB_BUFFER_SZ 128
#define CKSUM_SZ 2

class CBinProtocol
{
public:

  /**
   * @brief Supported message
   */
  enum class EMessageIds : uint8_t
  {
    eNAV_PVT = 0x07, ///< UBX-NAV-PVT (0x01 0x07)
    eNAV_EOE = 0x61, ///< UBX-NAV-EOE (0x01 0x61)
  };

  /**
   * @brief Message header data structure of UBX packet.
   */
  struct SMessageDataHeader
  {
    uint8_t uMsgClass;
    uint8_t uMsgId;
    uint16_t uMsgLen;
  };

  /**
   * @brief Message header structure of UBX packet.
   */
  struct SMessageHeader
  {
    static constexpr uint8_t uMarker1_ { 0xb5 };
    static constexpr uint8_t uMarker2_ { 0x62 };
    SMessageDataHeader oData_;
  };

  /**
   * Get a pointer to the binary protocol parser class instance.
   */
  static CBinProtocol& GetInstance();

  /**
   * Initialize the binary protocol parser class. Creates and initializes all the member objects.
   */
  void Init();

  /**
   * Run the binary protocol parser class.
   */
  void Parse();

  /**
   * Run the queue filler.
   */
  void Fill(const uint8_t *buf, size_t buf_len);

protected:

private:
  /**
   * The default constructor. Called only by the CBinProtocol::GetInstance().
   */
  CBinProtocol();
  ~CBinProtocol() = default;

  Ringbuffer buffer_;

  //
  // Declaration of private functions
  //
  bool findNextMessageHeader(uint8_t* data);
  void decodeMessage(const uint8_t* data, CBinProtocol::EMessageIds messsage_id);
  void calculateChecksum(uint8_t *data, uint16_t length, uint8_t *ck_a, uint8_t *ck_b);

};

#endif /* C_BIN_PROT_H */
