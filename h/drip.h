typedef struct ut_drip{

    UTFLOAT amp; /* How loud */
    UTFLOAT dettack; /* How loud */
    UTFLOAT num_tubes;
    UTFLOAT damp;
    UTFLOAT shake_max;
    UTFLOAT freq;
    UTFLOAT freq1;
    UTFLOAT freq2;

    UTFLOAT num_objectsSave;
    UTFLOAT shake_maxSave;
    UTFLOAT shakeEnergy;
    UTFLOAT outputs00;
    UTFLOAT outputs01;
    UTFLOAT outputs10;
    UTFLOAT outputs11;
    UTFLOAT outputs20;
    UTFLOAT outputs21;
    UTFLOAT coeffs00;
    UTFLOAT coeffs01;
    UTFLOAT coeffs10;
    UTFLOAT coeffs11;
    UTFLOAT coeffs20;
    UTFLOAT coeffs21;
    UTFLOAT finalZ0;
    UTFLOAT finalZ1;
    UTFLOAT finalZ2;
    UTFLOAT sndLevel;
    UTFLOAT gains0;
    UTFLOAT gains1;
    UTFLOAT gains2;
    UTFLOAT center_freqs0;
    UTFLOAT center_freqs1;
    UTFLOAT center_freqs2;
    UTFLOAT soundDecay;
    UTFLOAT systemDecay;
    UTFLOAT num_objects;
    UTFLOAT totalEnergy;
    UTFLOAT decayScale;
    UTFLOAT res_freq0;
    UTFLOAT res_freq1;
    UTFLOAT res_freq2;
    UTFLOAT shake_damp;
    int kloop;
} ut_drip;

int ut_drip_create(ut_drip **p);
int ut_drip_destroy(ut_drip **p);
int ut_drip_init(ut_data *ut, ut_drip *p, UTFLOAT dettack);
int ut_drip_compute(ut_data *ut, ut_drip *p, UTFLOAT *trig, UTFLOAT *out);
