/**
 * jpg.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * JPG and FAT32-related data types in relation to a cluster
 */

#include <stdint.h>

/**
 * Common Data Types 
 *
 * The data types in this section are essentially aliases for C/C++ 
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;

/**
 * CLUSTER
 *
 * The CLUSTER contains information and first four bytes in a 512 bytes cluster.
 */
typedef struct 
{ 
    BYTE   firstByte; 
    BYTE   secondByte; 
    BYTE   thirdByte; 
    BYTE   fourthByte; 
    BYTE   cluster[508]; 
}
CLUSTER; 
