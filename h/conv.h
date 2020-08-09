typedef struct {
    UTFLOAT aOut[1];
    UTFLOAT aIn;
    UTFLOAT iPartLen;
    UTFLOAT iSkipSamples;
    UTFLOAT iTotLen;
    int initDone;
    int nChannels;
    int cnt;
    int nPartitions;
    int partSize;
    int rbCnt;
    UTFLOAT *tmpBuf;
    UTFLOAT *ringBuf;
    UTFLOAT *IR_Data[1];
    UTFLOAT *outBuffers[1];
    ut_auxdata auxData;
    ut_ftbl *ftbl;
    ut_fft fft;
} ut_conv;

int ut_conv_create(ut_conv **p);
int ut_conv_destroy(ut_conv **p);
int ut_conv_init(ut_data *ut, ut_conv *p, ut_ftbl *ft, UTFLOAT iPartLen);
int ut_conv_compute(ut_data *ut, ut_conv *p, UTFLOAT *in, UTFLOAT *out);
