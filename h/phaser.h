typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[10];
    UTFLOAT *MaxNotch1Freq;
    UTFLOAT *MinNotch1Freq;
    UTFLOAT *Notch_width;
    UTFLOAT *NotchFreq;
    UTFLOAT *VibratoMode;
    UTFLOAT *depth;
    UTFLOAT *feedback_gain;
    UTFLOAT *invert;
    UTFLOAT *level;
    UTFLOAT *lfobpm;
} ut_phaser;

int ut_phaser_create(ut_phaser **p);
int ut_phaser_destroy(ut_phaser **p);
int ut_phaser_init(ut_data *ut, ut_phaser *p);
int ut_phaser_compute(ut_data *ut, ut_phaser *p, 
	UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out1, UTFLOAT *out2);
