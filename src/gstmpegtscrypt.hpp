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
#ifndef __GST_MPEGTSCRYPT_H__
#define __GST_MPEGTSCRYPT_H__

#include <openssl/aes.h>
#include <gst/gst.h>
#include <gst/base/base.h>


G_BEGIN_DECLS

/* #defines don't like whitespacey bits */
#define GST_TYPE_MPEGTSCRYPT \
  (gst_mpegts_crypt_get_type())
#define GST_MPEGTSCRYPT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MPEGTSCRYPT,GstMpegtsCrypt))
#define GST_MPEGTSCRYPT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MPEGTSCRYPT,GstMpegtsCryptClass))
#define GST_IS_MPEGTSCRYPT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MPEGTSCRYPT))
#define GST_IS_MPEGTSCRYPT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MPEGTSCRYPT))

typedef struct _GstMpegtsCrypt      GstMpegtsCrypt;
typedef struct _GstMpegtsCryptClass GstMpegtsCryptClass;

#include "crypt.hpp"
#define TS_PACKET_SIZE 188

enum
{
  PROP_0,
  PROP_METHOD,
  PROP_KEY,
  PROP_OPERATION
};
typedef enum {
    MPEGTSCRYPT_METHOD_BISS,
    MPEGTSCRYPT_METHOD_AES128_ECB,
    MPEGTSCRYPT_METHOD_AES128_CBC,
    MPEGTSCRYPT_METHOD_AES256_ECB,
    MPEGTSCRYPT_METHOD_AES256_CBC
} GstMpegTsCryptMethod;
typedef enum {
    MPEGTSCRYPT_OPERATION_DEC,
    MPEGTSCRYPT_OPERATION_ENC
} GstMpegTsCryptOperation;

struct _GstMpegtsCrypt
{
  GstElement element;

  GstPad *sinkpad, *srcpad;
  GstAdapter* adapter;

  GstMpegTsCryptMethod method;
  GstMpegTsCryptOperation operation;
   gchar key[256];
  gboolean init_crypt;
  
  // BISS key
  dvbcsa_key_t	*biss_csakey[2];
  // AES  key
  AES_KEY   aes_enc_key;
  AES_KEY   aes_dec_key;
  unsigned char aes_iv_enc[AES_BLOCK_SIZE];
  unsigned char aes_iv_dec[AES_BLOCK_SIZE];

};

struct _GstMpegtsCryptClass 
{
  GstElementClass parent_class;
};

GType gst_mpegts_crypt_get_type (void);

G_END_DECLS

#endif /* __GST_MPEGTSCRYPT_H__ */
