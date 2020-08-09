typedef struct nano_entry {
    char name[50];
    uint32_t pos;
    uint32_t size;
    UTFLOAT speed;
    struct nano_entry *next;
} nano_entry;

typedef struct {
    int nval;
    int init;
    nano_entry root;
    nano_entry *last;
} nano_dict;

typedef struct {
    char ini[100];
    UTFLOAT curpos;
    nano_dict dict;
    int selected;
    nano_entry *sample;
    nano_entry **index; 
    ut_ftbl *ft;
    int sr;
} nanosamp;

typedef struct {
    nanosamp *smp;
    uint32_t index;
    int triggered;
} ut_nsmp;

int ut_nsmp_create(ut_nsmp **p);
int ut_nsmp_destroy(ut_nsmp **p);
int ut_nsmp_init(ut_data *ut, ut_nsmp *p, ut_ftbl *ft, int sr, const char *ini);
int ut_nsmp_compute(ut_data *ut, ut_nsmp *p, UTFLOAT *in, UTFLOAT *out);

int ut_nsmp_print_index(ut_data *ut, ut_nsmp *p);
