int uta_open(ut_data *ut, ut_audio *uta, const char *name, int mode);
size_t uta_write_buf(ut_data *ut, ut_audio *uta, UTFLOAT *buf, uint32_t size);
size_t uta_read_buf(ut_data *ut, ut_audio *uta, UTFLOAT *buf, uint32_t size);
int uta_close(ut_audio *uta);
