#ifndef _QRDECODE_H_
#define _QRDECODE_H_

#ifdef __cplusplus  
extern "C"
{
#endif

int QRDecode(const char *file, char *data, int maxlen);

#ifdef __cplusplus
}
#endif

#endif
