# gst_mpegts_crypt
Simple Gstreamer element for MPEG TS cryptography by BISS, AES128, AES256

#Usage: 
## For satellite channels that scrambled by BISS:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.1:3200" ! queue \
               ! mpegtscrypt method="biss" op="dec"  key="111111222222" \
               ! fakesink

```
## For secure trasfering:

### In Server:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.1:3200" ! queue \
               ! mpegtscrypt method="aes256" op="enc"  key="111111222222" \
               ! udpsink host=229.1.1.2 port=3200
```
### In Client:
```
$ gst-launch-1.0 udpsrc uri="udp://229.1.1.2:3200" ! queue \
               ! mpegtscrypt method="aes256" op="enc"  key="111111222222" \
               ! fakesink
```
