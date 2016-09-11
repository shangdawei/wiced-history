/*
 * Broadcom Proprietary and Confidential. Copyright 2016 Broadcom
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chacha.h"
#include "chacha_test_vectors.h"


int chacha_self_test( void )
{
    int vector;
    chacha_context_t x;
    uint8_t input[64];
    uint8_t output[64];

    for ( vector = 0;vector < chacha_test_vectors_count; vector++ )
    {
        const chacha_vector_t* curr = &chacha_test_vectors[vector];
        chacha_keysetup( &x, curr->key, curr->key_len );
        chacha_ivsetup( &x, curr->iv );
        memset( input, 0, 64 );
        chacha_encrypt_bytes( &x, input, output, 64, curr->rounds );
        if ( 0 != memcmp( output, curr->keystream_block, 64 ) )
        {
            printf( "ChaCha %s, keylen %lu, rounds %u - Output Compare failure 1\n", curr->description, (unsigned long) curr->key_len, curr->rounds );
            return -1;
        }
        chacha_encrypt_bytes( &x, input, output, 64, curr->rounds );
        if ( 0 != memcmp( output, curr->keystream_block_1, 64 ) )
        {
            printf( "ChaCha %s, keylen %lu, rounds %u - Output Compare failure 2\n", curr->description, (unsigned long) curr->key_len, curr->rounds );
            return -1;
        }
    }
    return 0;
}


/* from section 2.3.1 of draft-nir-cfrg-chacha20-poly1305-05 */
const uint8_t chacha20_block_test1_key[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

const uint8_t chacha20_block_test1_nonce[] =
{
    0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00,
};

const chacha_context_t chacha20_block_test1_start_state =
{
    .input =
    {
       0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
       0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
       0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
       0x00000001, 0x09000000, 0x4a000000, 0x00000000,
    }
};

const chacha_context_t chacha20_block_test1_state_after_encryption =
{
    .input =
    {
           0x837778ab, 0xe238d763, 0xa67ae21e, 0x5950bb2f,
           0xc4f2d0c7, 0xfc62bb2f, 0x8fa018fc, 0x3f5ec7b7,
           0x335271c2, 0xf29489f3, 0xeabda8fc, 0x82e46ebd,
           0xd19c12b4, 0xb04e16de, 0x9e83d0cb, 0x4e3c50a2,
    }
};

const uint8_t chacha20_block_test1_output[] =
{
    0x10, 0xf1, 0xe7, 0xe4, 0xd1, 0x3b, 0x59, 0x15, 0x50, 0x0f, 0xdd, 0x1f, 0xa3, 0x20, 0x71, 0xc4,
    0xc7, 0xd1, 0xf4, 0xc7, 0x33, 0xc0, 0x68, 0x03, 0x04, 0x22, 0xaa, 0x9a, 0xc3, 0xd4, 0x6c, 0x4e,
    0xd2, 0x82, 0x64, 0x46, 0x07, 0x9f, 0xaa, 0x09, 0x14, 0xc2, 0xd7, 0x05, 0xd9, 0x8b, 0x02, 0xa2,
    0xb5, 0x12, 0x9c, 0xd1, 0xde, 0x16, 0x4e, 0xb9, 0xcb, 0xd0, 0x83, 0xe8, 0xa2, 0x50, 0x3c, 0x4e,
};

/* from section 2.6.1 of draft-nir-cfrg-chacha20-poly1305-05 */
const uint8_t chacha20_block_test2_key[] =
{
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
};

const uint8_t chacha20_block_test2_nonce[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};

const uint8_t chacha20_block_test2_output[] =
{
    0x8a, 0xd5, 0xa0, 0x8b, 0x90, 0x5f, 0x81, 0xcc, 0x81, 0x50, 0x40, 0x27, 0x4a, 0xb2, 0x94, 0x71,
    0xa8, 0x33, 0xb6, 0x37, 0xe3, 0xfd, 0x0d, 0xa5, 0x08, 0xdb, 0xb8, 0xe2, 0xfd, 0xd1, 0xa6, 0x46,
    0x82, 0x37, 0xa0, 0x7d, 0x33, 0xa2, 0x83, 0x91, 0x71, 0xd2, 0x8a, 0x14, 0xd1, 0x73, 0x67, 0xb4,
    0x5a, 0x87, 0xc1, 0x3c, 0xf1, 0xde, 0x07, 0x86, 0x86, 0x30, 0x5c, 0xca, 0x87, 0xeb, 0x85, 0x70,
};

int test_chacha20_block_function( void )
{
    uint8_t output_random[64];
    chacha20_block_function( chacha20_block_test1_key, chacha20_block_test1_nonce, 1, output_random );
    if ( 0 != memcmp( output_random, chacha20_block_test1_output, 64 ) )
    {
        return -1;
    }
    chacha20_block_function( chacha20_block_test2_key, chacha20_block_test2_nonce, 0, output_random );
    return memcmp( output_random, chacha20_block_test2_output, 64 );
}



typedef struct
{
    uint8_t        key[32];
    uint8_t        nonce[8];
    uint32_t       keystream_length;
    const uint8_t* keystream;
} chacha20_keystream_test_t;

/* Obtained from section 7 of http://tools.ietf.org/html/draft-agl-tls-chacha20poly1305 */

static const uint8_t keystream0_expected_data[] =
{
    0x76, 0xb8, 0xe0, 0xad, 0xa0, 0xf1, 0x3d, 0x90,
    0x40, 0x5d, 0x6a, 0xe5, 0x53, 0x86, 0xbd, 0x28,
    0xbd, 0xd2, 0x19, 0xb8, 0xa0, 0x8d, 0xed, 0x1a,
    0xa8, 0x36, 0xef, 0xcc, 0x8b, 0x77, 0x0d, 0xc7,
    0xda, 0x41, 0x59, 0x7c, 0x51, 0x57, 0x48, 0x8d,
    0x77, 0x24, 0xe0, 0x3f, 0xb8, 0xd8, 0x4a, 0x37,
    0x6a, 0x43, 0xb8, 0xf4, 0x15, 0x18, 0xa1, 0x1c,
    0xc3, 0x87, 0xb6, 0x69, 0xb2, 0xee, 0x65, 0x86,
};

static const uint8_t keystream1_expected_data[] =
{
    0x45, 0x40, 0xf0, 0x5a, 0x9f, 0x1f, 0xb2, 0x96,
    0xd7, 0x73, 0x6e, 0x7b, 0x20, 0x8e, 0x3c, 0x96,
    0xeb, 0x4f, 0xe1, 0x83, 0x46, 0x88, 0xd2, 0x60,
    0x4f, 0x45, 0x09, 0x52, 0xed, 0x43, 0x2d, 0x41,
    0xbb, 0xe2, 0xa0, 0xb6, 0xea, 0x75, 0x66, 0xd2,
    0xa5, 0xd1, 0xe7, 0xe2, 0x0d, 0x42, 0xaf, 0x2c,
    0x53, 0xd7, 0x92, 0xb1, 0xc4, 0x3f, 0xea, 0x81,
    0x7e, 0x9a, 0xd2, 0x75, 0xae, 0x54, 0x69, 0x63,
};


static const uint8_t keystream2_expected_data[] =
{
    0xde, 0x9c, 0xba, 0x7b, 0xf3, 0xd6, 0x9e, 0xf5,
    0xe7, 0x86, 0xdc, 0x63, 0x97, 0x3f, 0x65, 0x3a,
    0x0b, 0x49, 0xe0, 0x15, 0xad, 0xbf, 0xf7, 0x13,
    0x4f, 0xcb, 0x7d, 0xf1, 0x37, 0x82, 0x10, 0x31,
    0xe8, 0x5a, 0x05, 0x02, 0x78, 0xa7, 0x08, 0x45,
    0x27, 0x21, 0x4f, 0x73, 0xef, 0xc7, 0xfa, 0x5b,
    0x52, 0x77, 0x06, 0x2e, 0xb7, 0xa0, 0x43, 0x3e,
    0x44, 0x5f, 0x41, 0xe3,
};

static const uint8_t keystream3_expected_data[] =
{
    0xef, 0x3f, 0xdf, 0xd6, 0xc6, 0x15, 0x78, 0xfb,
    0xf5, 0xcf, 0x35, 0xbd, 0x3d, 0xd3, 0x3b, 0x80,
    0x09, 0x63, 0x16, 0x34, 0xd2, 0x1e, 0x42, 0xac,
    0x33, 0x96, 0x0b, 0xd1, 0x38, 0xe5, 0x0d, 0x32,
    0x11, 0x1e, 0x4c, 0xaf, 0x23, 0x7e, 0xe5, 0x3c,
    0xa8, 0xad, 0x64, 0x26, 0x19, 0x4a, 0x88, 0x54,
    0x5d, 0xdc, 0x49, 0x7a, 0x0b, 0x46, 0x6e, 0x7d,
    0x6b, 0xbd, 0xb0, 0x04, 0x1b, 0x2f, 0x58, 0x6b,
};

static const uint8_t keystream4_expected_data[] =
{
    0xf7, 0x98, 0xa1, 0x89, 0xf1, 0x95, 0xe6, 0x69,
    0x82, 0x10, 0x5f, 0xfb, 0x64, 0x0b, 0xb7, 0x75,
    0x7f, 0x57, 0x9d, 0xa3, 0x16, 0x02, 0xfc, 0x93,
    0xec, 0x01, 0xac, 0x56, 0xf8, 0x5a, 0xc3, 0xc1,
    0x34, 0xa4, 0x54, 0x7b, 0x73, 0x3b, 0x46, 0x41,
    0x30, 0x42, 0xc9, 0x44, 0x00, 0x49, 0x17, 0x69,
    0x05, 0xd3, 0xbe, 0x59, 0xea, 0x1c, 0x53, 0xf1,
    0x59, 0x16, 0x15, 0x5c, 0x2b, 0xe8, 0x24, 0x1a,
    0x38, 0x00, 0x8b, 0x9a, 0x26, 0xbc, 0x35, 0x94,
    0x1e, 0x24, 0x44, 0x17, 0x7c, 0x8a, 0xde, 0x66,
    0x89, 0xde, 0x95, 0x26, 0x49, 0x86, 0xd9, 0x58,
    0x89, 0xfb, 0x60, 0xe8, 0x46, 0x29, 0xc9, 0xbd,
    0x9a, 0x5a, 0xcb, 0x1c, 0xc1, 0x18, 0xbe, 0x56,
    0x3e, 0xb9, 0xb3, 0xa4, 0xa4, 0x72, 0xf8, 0x2e,
    0x09, 0xa7, 0xe7, 0x78, 0x49, 0x2b, 0x56, 0x2e,
    0xf7, 0x13, 0x0e, 0x88, 0xdf, 0xe0, 0x31, 0xc7,
    0x9d, 0xb9, 0xd4, 0xf7, 0xc7, 0xa8, 0x99, 0x15,
    0x1b, 0x9a, 0x47, 0x50, 0x32, 0xb6, 0x3f, 0xc3,
    0x85, 0x24, 0x5f, 0xe0, 0x54, 0xe3, 0xdd, 0x5a,
    0x97, 0xa5, 0xf5, 0x76, 0xfe, 0x06, 0x40, 0x25,
    0xd3, 0xce, 0x04, 0x2c, 0x56, 0x6a, 0xb2, 0xc5,
    0x07, 0xb1, 0x38, 0xdb, 0x85, 0x3e, 0x3d, 0x69,
    0x59, 0x66, 0x09, 0x96, 0x54, 0x6c, 0xc9, 0xc4,
    0xa6, 0xea, 0xfd, 0xc7, 0x77, 0xc0, 0x40, 0xd7,
    0x0e, 0xaf, 0x46, 0xf7, 0x6d, 0xad, 0x39, 0x79,
    0xe5, 0xc5, 0x36, 0x0c, 0x33, 0x17, 0x16, 0x6a,
    0x1c, 0x89, 0x4c, 0x94, 0xa3, 0x71, 0x87, 0x6a,
    0x94, 0xdf, 0x76, 0x28, 0xfe, 0x4e, 0xaa, 0xf2,
    0xcc, 0xb2, 0x7d, 0x5a, 0xaa, 0xe0, 0xad, 0x7a,
    0xd0, 0xf9, 0xd4, 0xb6, 0xad, 0x3b, 0x54, 0x09,
    0x87, 0x46, 0xd4, 0x52, 0x4d, 0x38, 0x40, 0x7a,
    0x6d, 0xeb, 0x3a, 0xb7, 0x8f, 0xab, 0x78, 0xc9,
};

static const chacha20_keystream_test_t keystream_tests[] =
{
        {
           .key   = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .nonce = {
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .keystream_length = sizeof(keystream0_expected_data),
           .keystream = keystream0_expected_data,
        },
        {
           .key   = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                    },
           .nonce = {
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .keystream_length = sizeof(keystream1_expected_data),
           .keystream = keystream1_expected_data,
        },
        {
           .key   = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .nonce = {
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                    },
           .keystream_length = sizeof(keystream2_expected_data),
           .keystream = keystream2_expected_data,
        },
        {
           .key   = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .nonce = {
                      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    },
           .keystream_length = sizeof(keystream3_expected_data),
           .keystream = keystream3_expected_data,
        },
        {
           .key   = {
                      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                      0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                    },
           .nonce = {
                      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    },
           .keystream_length = sizeof(keystream4_expected_data),
           .keystream = keystream4_expected_data,
        },
};


int test_chacha20_tls_keystream( void )
{
    int test_number;
    const uint64_t block_count = 0;

    for( test_number = 0; test_number < sizeof( keystream_tests ) / sizeof( chacha20_keystream_test_t ); test_number++ )
    {
        chacha_context_t context;

        uint8_t* buffer = (uint8_t*) malloc( keystream_tests[test_number].keystream_length );
        if ( buffer == NULL )
        {
            return -1;
        }
        chacha_keysetup( &context, keystream_tests[test_number].key, 256 );
        chacha20_tls_ivsetup( &context, keystream_tests[test_number].nonce, block_count );
        chacha_keystream_bytes( &context, buffer, keystream_tests[test_number].keystream_length, 20 );

        if ( 0 != memcmp( keystream_tests[test_number].keystream, buffer, keystream_tests[test_number].keystream_length ) )
        {
            return -2;
        }

        free( buffer );
    }
    return 0;
}


