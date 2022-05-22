#include "gcmd.h"
#include "gcmd_conf.h"
#include "hashmap.h"

// current sequence number
static uint32_t seq_num = 0;

// hashmap that maps control numbers to functions
static hashmap_t* hm;

int gcmd_init() {
    hm = hm_create(100, 10); // TODO make this number less random?

    if(!hm) {
        // can't allocate memory
        return -1;
    }

    gcmd_entry_t entry;
    for(size_t i = 0; i < NUM_GCMDS; i++) {
        entry = gcmd_list[i];
        if(hm_add(hm, entry.control, (void*)(entry.func)) != HM_OK) {
            // can't add
            return -1;
        }
    }

    return 1;
}

void gcmd_parse(uint8_t* buff, size_t len, void* addr_info) {
    if(len != sizeof(gcmd_t)) {
        return;
    }

    gcmd_t* cmd = (gcmd_t*)buff;

    if(cmd->seq_num != seq_num) {
        // TODO send some kind of error
        return;
    }

    void* f = hm_get(hm, cmd->control);

    if(f == NULL) {
        // no such control number
        // TODO send some kind of error
        return;
    }

    seq_num++;

    void (*func)(uint16_t, void*) = (void (*)(uint16_t, void*))f;
    func(cmd->state, addr_info);
}
