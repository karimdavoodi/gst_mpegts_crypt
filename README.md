# mpegtscrypt
Simple Gstreamer element for MPEG TS cryptography by BISS, AES128, AES256

## Usage: 
### For satellite channels that scrambled by BISS:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.1:3200" ! queue \
               ! mpegtscrypt method="biss" op="dec"  key="111111222222" \
               ! fakesink

```
### For secure trasfering:

#### In Server:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.1:3200" ! queue \
               ! mpegtscrypt method="aes256" op="enc"  key="111111222222" \
               ! udpsink host=229.1.1.2 port=3200
```
#### In Client:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.2:3200" ! queue \
               ! mpegtscrypt method="aes256" op="enc"  key="111111222222" \
               ! fakesink
```
## Help:
```
Factory Details:
  Rank                     none (0)
  Long-name                MPEG TS Cryptogrsphy
  Klass                    Filter
  Description              Encrypt/decrypt MPEG TS by BISS or AES
  Author                   Karim Davoodi <<karimdavoodi@gmail.com>>

Plugin Details:
  Name                     mpegtscrypt
  Description              Encrypt/decrypt mpegts by BISS and AES
  Filename                 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/libgstmpegtscrypt.so
  Version                  1.0.1
  License                  LGPL
  Source module            mpegtscrypt
  Binary package           Gstreamer
  Origin URL               https://github.com/karimdavoodi/gst_mpegts_crypt

GObject
 +----GInitiallyUnowned
       +----GstObject
             +----GstElement
                   +----GstMpegtsCrypt

Pad Templates:
  SRC template: 'src'
    Availability: Always
    Capabilities:
      video/mpegts
  
  SINK template: 'sink'
    Availability: Always
    Capabilities:
      video/mpegts

Element has no clocking capabilities.
Element has no URI handling capabilities.

Pads:
  SINK: 'sink'
    Pad Template: 'sink'
  SRC: 'src'
    Pad Template: 'src'

Element Properties:
  key                 : Crypto key string
                        flags: readable, writable
                        String. Default: ""
  method              : Method of cryptography
                        flags: readable, writable
                        Enum "GstMpegTsCryptMethod" Default: 0, "biss"
                           (0): biss             - BISS Method
                           (1): aes128_ecb       - AES128 ECB Method
                           (2): aes128_cbc       - AES128 CBC Method
                           (3): aes256_ecb       - AES256 ECB Method
                           (4): aes256_cbc       - AES256 CBC Method
  name                : The name of the object
                        flags: readable, writable
                        String. Default: "mpegtscrypt0"
  op                  : Cryptogrsphy operation
                        flags: readable, writable
                        Enum "GstMpegTsCryptOperation" Default: 0, "dec"
                           (0): dec              - Decrypt
                           (1): enc              - Encrypt
  parent              : The parent of the object
                        flags: readable, writable
                        Object of type "GstObject"
```
## TODO:
    - Add CCCAM methods to unscrambling of Satellite channels.     
    - Operate on the last remaind of TS packet (% 16) in AES algorithm.
    - Add other crypto algorithms.
    - Add Test Case
