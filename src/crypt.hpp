/*
 *    Copyright (c) 2020 Karim <<karimdavoodi@gmail.com>>
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */
#pragma onc;
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
