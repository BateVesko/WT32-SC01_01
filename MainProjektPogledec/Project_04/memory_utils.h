//Project_03
#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <Arduino.h>
#include "esp_heap_caps.h"

void printMemoryUsage() {
    size_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t totalHeap = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    size_t usedHeap = totalHeap - freeHeap;

    Serial.print("Used memory: ");
    Serial.print(usedHeap);
    Serial.print(" bytes, Free memory: ");
    Serial.print(freeHeap);
    Serial.println(" bytes");
}

#endif // MEMORY_UTILS_H
