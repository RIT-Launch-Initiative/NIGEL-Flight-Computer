/*
*   Hashmap module
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>

#ifndef HASHMAP_C
typedef struct {} hashmap_t;
#endif

#define HASHMAP_DEFAULT_SIZE 1000

typedef enum {
    HM_OK,
    HM_FULL,
    HM_INVALID_KEY,
    HM_ERR
} hashmap_ret_t;

// create a new hashmap
// returns NULL on error
hashmap_t* hm_create(uint32_t num_entries);

// destroy a hashmap
void hm_destroy(hashmap_t* hm);

// add an entry
hashmap_ret_t hm_add(hashmap_t* hm, uint32_t key, void* value);

// remove an entry
hashmap_ret_t hm_rm(hashmap_t* hm, uint32_t key);

// get the value of an entry
// returns NULL on error
void* hm_get(hashmap_t* hm, uint32_t key);

#endif
