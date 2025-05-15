#ifndef INC_BP_WRAPPER_H_
#define INC_BP_WRAPPER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void BinProtocolInit();
void BinProtocolParse();
void BinProtocolFill(const uint8_t *buf, size_t buf_len);

#ifdef __cplusplus
}
#endif

#endif /* INC_BP_WRAPPER_H_ */
