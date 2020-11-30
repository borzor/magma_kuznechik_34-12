#include "duck.h"

int main()
{
    struct bckey our_key, our_second_key;
    ak_uint8 key_magma[32] = {
        0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf6, 0xf5, 0xf4, 0xf3, 0xf2, 0xf1, 0xf0,
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    ak_uint8 key_kuzn[32] = {
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
    };

    ak_uint8 ivctr_magma[4] = {0x78, 0x56, 0x34, 0x12};
    ak_uint8 ivctr_kuzn[8] = {0xf0, 0xce, 0xab, 0x90, 0x78, 0x56, 0x34, 0x12};
    ak_uint8 in_kuzn[79] = {
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x0a, 0xff, 0xee, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0x00, 0x0a, 0xff, 0xee, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x11, 0x00, 0x0a, 0xff, 0xee, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22
    };
    ak_uint8 in_magma[39] = {
            0x59, 0x0a, 0x13, 0x3c, 0x6b, 0xf0, 0xde, 0x92,
            0x20, 0x9d, 0x18, 0xf8, 0x04, 0xc7, 0x54, 0xdb,
            0x4c, 0x02, 0xa8, 0x67, 0x2e, 0xfb, 0x98, 0x4a,
            0x41, 0x7e, 0xb5, 0x17, 0x9b, 0x40, 0x12, 0x89,
            0x59, 0x0a, 0x13, 0x3c, 0x6b, 0xf0, 0xde
        };
    ak_uint8 buf[128];

    if(!ak_libakrypt_create(ak_function_log_stderr)) return ak_libakrypt_destroy();
    ak_libakrypt_destroy();
    if(ak_bckey_context_create_magma(&our_key) != ak_error_ok)
        return ak_libakrypt_destroy();
    if(ak_bckey_context_create_kuznechik(&our_second_key) != ak_error_ok)
        return ak_libakrypt_destroy();


    ak_bckey_context_set_key(&our_second_key, key_kuzn, sizeof (key_kuzn));
    printf("kuzn in\n");
    for(int j=0; j<4; j++){
        for(int i = 0; i < 16; i++){
            printf("%02x ", in_kuzn[16*j+i]);
        }
        printf("\n");
    }
    BR_gamma(&our_second_key, in_kuzn, buf, sizeof (in_kuzn), ivctr_kuzn, 8);
    printf("\ncrypted\n");
    for(int j=0; j < 4; j++){
        for(int i = 0; i < 16; i++){
            printf("%02x ", buf[16*j+i]);
        }
        printf("\n");
    }
    BR_gamma(&our_second_key, buf, buf, sizeof (in_kuzn), ivctr_kuzn, 8);
    printf("\ndecrypted \n");
    for(int j=0; j < 4; j++){
        for(int i = 0; i < 16; i++){
            printf("%02x ", buf[16*j+i]);
        }
        printf("\n");
    }
/*
    ak_bckey_context_set_key(&our_key, key_magma, sizeof (key_magma));
    printf("magma in\n");
    for(int j=0; j<5; j++){
        for(int i = 0; i < 8; i++){
            printf("%02x ", in_magma[8*j+i]);
        }
        printf("\n");
    }
    BR_gamma(&our_key, in_magma, buf, sizeof (in_magma), ivctr_magma, 4);
    printf("\ncrypted\n");
    for(int j=0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            printf("%02x ", buf[8*j+i]);
        }
        printf("\n");
    }
    BR_gamma(&our_key, buf, buf, sizeof (in_magma), ivctr_magma, 4);
    printf("\ndecrypted \n");
    for(int j=0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            printf("%02x ", buf[8*j+i]);
        }
        printf("\n");
    }
*/
    return 0;
}
