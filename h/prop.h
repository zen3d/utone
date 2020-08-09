typedef struct {
    char type;
    uint32_t pos;
    uint32_t val;
    uint32_t cons;
} prop_event;

typedef struct {
    char type;
    void *ud;
} prop_val;

typedef struct prop_entry {
    prop_val val;
    struct prop_entry *next;
} prop_entry;

typedef struct prop_list {
    prop_entry root;
    prop_entry *last;
    uint32_t size;
    uint32_t pos;
    struct prop_list *top;
    uint32_t lvl;
} prop_list;

typedef struct {
    uint32_t stack[16];
    int pos;
} prop_stack;

typedef struct {
    uint32_t mul;
    uint32_t div;
    uint32_t tmp;
    uint32_t cons_mul;
    uint32_t cons_div;
    UTFLOAT scale;
    int mode;
    uint32_t pos;
    prop_list top;
    prop_list *main;
    prop_stack mstack;
    prop_stack cstack;
} prop_data;

typedef struct {
   prop_data *prp;
   prop_event evt;
   uint32_t count;
   UTFLOAT bpm;
   UTFLOAT lbpm;
} ut_prop;

int ut_prop_create(ut_prop **p);
int ut_prop_destroy(ut_prop **p);
int ut_prop_reset(ut_data *ut, ut_prop *p);
int ut_prop_init(ut_data *ut, ut_prop *p, const char *str);
int ut_prop_compute(ut_data *ut, ut_prop *p, UTFLOAT *in, UTFLOAT *out);
