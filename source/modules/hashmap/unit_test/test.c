#include <stdlib.h>
#include <stdio.h>
#include "../hashmap.h"

int main() {
    hashmap_t* hm = hm_create(1000);

    char* data1 = "test1";
    char* data2 = "test2";
    char* data3 = "test3";

    hm_add(hm, 1000, (void*)data1);
    hm_add(hm, 1007, (void*)data2);
    hm_add(hm, 2007, (void*)data3);

    printf("%s\n", (char*)hm_get(hm, 1000));
    printf("%s\n", (char*)hm_get(hm, 1007));
    printf("%s\n", (char*)hm_get(hm, 2007));
}
