#pragma onc;
//#include <iostream>
#include <gst/gst.h>
#include "gstmpegtscrypt.hpp"

#define CODEWORD_LENGTH 16
#define BISSKEY_LENGTH 6
extern "C" {
// include C functions from <dvbcsa/dvbcsa.h>
    typedef unsigned char		dvbcsa_cw_t[8];
    typedef struct dvbcsa_key_s	dvbcsa_key_t;
    struct dvbcsa_key_s * dvbcsa_key_alloc(void);
    void dvbcsa_key_free(struct dvbcsa_key_s *key);
    void dvbcsa_key_set (const dvbcsa_cw_t cw, struct dvbcsa_key_s *key);
    void dvbcsa_encrypt (const struct dvbcsa_key_s *key,
            unsigned char *data, unsigned int len);
    void dvbcsa_decrypt (const struct dvbcsa_key_s *key,
            unsigned char *data, unsigned int len);
}
void crypt_init(GstMpegtsCrypt* filter);
void crypt_finish(GstMpegtsCrypt* filter);
        
void crypt_packet_aes(GstMpegtsCrypt* filter, unsigned char *ts_packet);
void crypt_packet_biss(GstMpegtsCrypt* filter, unsigned char *ts_packet);
