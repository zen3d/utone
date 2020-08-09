typedef struct{
    void (*reinit)(void *);
    void (*compute)(void *, UTFLOAT *out);
    void *ud;
    int started;
}ut_tevent;

int ut_tevent_create(ut_tevent **te);
int ut_tevent_destroy(ut_tevent **te);
int ut_tevent_init(ut_data *ut, ut_tevent *te, 
        void (*reinit)(void*), void (*compute)(void *, UTFLOAT *out), void *ud);
int ut_tevent_compute(ut_data *ut, ut_tevent *te, UTFLOAT *in, UTFLOAT *out);
