
#include "dslink/message_utils.h"


typedef struct Rid
{
    json_int_t _rid;
    json_t* _json;
} tRid;

json_t* merge_queue_messages(Vector* send_queue)
{
    json_t* top = json_object();
    json_t* reqs = NULL;
    json_t *resps = NULL;

    dslink_vector_foreach(send_queue) {
        json_t* obj = (json_t*)(*(void**)data);

        json_t* req = json_object_get(obj, "requests");
        if(!reqs) {
            reqs = req;
            json_object_set(top, "requests", json_incref(reqs));
        } else {
            size_t index = 0;
            json_t *value = NULL;
            json_array_foreach(req, index, value) {
                json_array_append(reqs, json_incref(value));
            }
        }

        json_t* resp = json_object_get(obj, "responses");
        if(!resps) {
            resps = resp;
            json_object_set(top, "responses", json_incref(resps));
        } else {
            size_t index = 0;
            json_t *value = NULL;
            json_array_foreach(resp, index, value) {
                json_array_append(resps, json_incref(value));
            }
        }

        json_decref(obj);
    }
    dslink_vector_foreach_end();
    vector_erase_range(send_queue, 0, vector_count(send_queue));

    return top;
}
