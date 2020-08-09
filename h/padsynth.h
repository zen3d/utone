typedef struct ut_padsynth {
    UTFLOAT cps;
    UTFLOAT bw;
    ut_ftbl *amps;
} ut_padsynth;

int ut_gen_padsynth(ut_data *ut, ut_ftbl *ps, ut_ftbl *amps, UTFLOAT f, UTFLOAT bw);

UTFLOAT ut_padsynth_profile(UTFLOAT fi, UTFLOAT bwi);

int ut_padsynth_ifft(int N, UTFLOAT *freq_amp, 
        UTFLOAT *freq_phase, UTFLOAT *smp); 

int ut_padsynth_normalize(int N, UTFLOAT *smp);
