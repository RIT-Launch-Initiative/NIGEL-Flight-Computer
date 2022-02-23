#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t key;
    void* value;
} hashmap_entry_t;

typedef struct {
    uint32_t size;            // number of entries
    hashmap_entry_t* entries; // array of entries
    uint8_t* used ;           // if entry is used or free
} hashmap_t;

#define HASHMAP_C
#include "hashmap.h"


hashmap_t* hm_create(uint32_t num_entries) {
    hashmap_t* hm = (hashmap_t*)malloc(sizeof(hashmap_t));
    hm->size = num_entries;
    hm->entries = (hashmap_entry_t*)calloc(num_entries, sizeof(hashmap_entry_t));
    hm->used = (uint8_t*)calloc(num_entries, sizeof(uint8_t));

    return hm;
}

void hm_destroy(hashmap_t* hm) {
    free(hm->entries);
    free(hm->used);
    free(hm);
}


// NOTE: the way we add we don't look for collisions with other keys
// the first key added will be returned by get until it is removed
hashmap_ret_t hm_add(hashmap_t* hm, uint32_t key, void* value) {
    uint32_t index = key % hm->size;

    // find a location closest to index and to the right
    for(uint32_t i = index; i < hm->size; i++) {
        if(!hm->used[i]) {
            // this is our location!
            hm->entries[i].key = key;
            hm->entries[i].value = value;
            hm->used[i] = 1;

            return HM_OK;
        }
    }

    return HM_FULL;
}

hashmap_ret_t hm_rm(hashmap_t* hm, uint32_t key) {
    uint32_t index = key % hm->size;

    // find the key starting from it's leftmost possible location
    for(uint32_t i = index; i < hm->size; i++) {
        if(hm->used[i]) {
            if(hm->entries[i].key == key) {
                // this is it!
                hm->used[i] = 0;

                return HM_OK;
            }
        }
    }

    // couldn't find the key to remove
    return HM_INVALID_KEY;
}

void* hm_get(hashmap_t* hm, uint32_t key) {
    uint32_t index = key % hm->size;

    // find the key starting from it's leftmost possible location
    for(uint32_t i = index; i < hm->size; i++) {
        if(hm->used[i]) {
            if(hm->entries[i].key == key) {
                // this is it!
                return hm->entries[i].value;
            }
        }
    }

    // no such key :(
    return NULL;
}
