typedef struct ut_rpi{
    ut_data *ut;
    void *ud;
    void (*callback)(ut_data *, void *);
}ut_rpi;
int ut_rpi_process(ut_data *ut, void *ud, void (*callback)(ut_data *, void *));
