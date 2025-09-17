#ifndef BITS_H
#define BITS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus__
extern "C" {
#endif

/*
 * Return Value: the bit value
 * Function Description: given a pointer to some data and a bit position (0 indexed), test the bit and return its value
 * data: pointer to the data
 * pos: bit position (0 indexed)
 */
uint8_t testbit(void *data, size_t pos) {
    uint8_t *bytes = (uint8_t*)data; // cast it as a pointer to a byte, which we can increment and decrement or access like an array

    size_t byteIndex = pos / 8; // which byte in the bytes array we should access
    uint8_t bitIndex = pos % 8; // which bit in the byte in the bytes array we should access

    return (bytes[byteIndex] >> bitIndex) & 1;
}

/*
 * Function Description: given a pointer to some data and a bit position (0 indexed), set the bit to 1
 * data: pointer to the data
 * pos: bit position (0 indexed)
 */
void setbit(void *data, size_t pos) {
    uint8_t *bytes = (uint8_t*)data;

    size_t byteIndex = pos / 8;
    uint8_t bitIndex = pos % 8;

    bytes[byteIndex] |= 1 << bitIndex;
}

/*
 * Function Description: given a pointer to some data and a bit position (0 indexed), set the bit to 0
 * data: pointer to the data
 * pos: bit position (0 indexed)
 */
void resetbit(void *data, size_t pos) {
    uint8_t *bytes = (uint8_t*)data;

    size_t byteIndex = pos / 8;
    uint8_t bitIndex = pos % 8;

    bytes[byteIndex] &= ~(1 << bitIndex);
}

/*
 * Return Value: the new bit value
 * data: pointer to the data
 * pos: bit position (0 indexed)
 */
uint8_t togglebit(void *data, size_t pos) {
    if (testbit(data, pos)) {
        resetbit(data, pos);
        return 0;
    } else {
        setbit(data, pos);
        return 1;
    }
}

#ifdef __cplusplus__
}
#endif
#endif
