#ifndef SDK_DSLINK_C_CLOSED_RESPONSE_H
#define SDK_DSLINK_C_CLOSED_RESPONSE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jansson.h>
#include "dslink/dslink.h"

int dslink_response_send_closed(DSLink *link, json_t *rid);

#ifdef __cplusplus
}
#endif

#endif // SDK_DSLINK_CLOSED_RESPONSE_H
