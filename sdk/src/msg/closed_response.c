#include <stdlib.h>
#include "dslink/mem/mem.h"
#include "dslink/ws.h"
#include "dslink/msg/closed_response.h"

int dslink_response_send_closed(DSLink *link, json_t *rid)
{
    json_t *top = json_object();
    if (!top) {
        return DSLINK_ALLOC_ERR;
    }

    json_t *resps = json_array();
    if (!resps) {
        json_delete(top);
        return DSLINK_ALLOC_ERR;
    }
    json_object_set_new_nocheck(top, "responses", resps);
    json_t *resp = json_object();
    if (!resp) {
        json_delete(top);
        return DSLINK_ALLOC_ERR;
    }
    json_array_append_new(resps, resp);
    json_object_set(resp, "rid", rid);
    json_object_set_new_nocheck(resp, "stream", json_string_nocheck("closed"));
    dslink_ws_send_obj(link->_ws, top);
    json_delete(top);
    return 0;
}

