
#ifndef UT_VOC
#define UT_VOC
typedef struct ut_voc ut_voc;

int ut_voc_create(ut_voc **voc);
int ut_voc_destroy(ut_voc **voc);
int ut_voc_init(ut_data *ut, ut_voc *voc);
int ut_voc_compute(ut_data *ut, ut_voc *voc, UTFLOAT *out);
int ut_voc_tract_compute(ut_data *ut, ut_voc *voc, UTFLOAT *in, UTFLOAT *out);

void ut_voc_set_frequency(ut_voc *voc, UTFLOAT freq);
UTFLOAT * ut_voc_get_frequency_ptr(ut_voc *voc);

UTFLOAT* ut_voc_get_tract_diameters(ut_voc *voc);
UTFLOAT* ut_voc_get_current_tract_diameters(ut_voc *voc);
int ut_voc_get_tract_size(ut_voc *voc);
UTFLOAT* ut_voc_get_nose_diameters(ut_voc *voc);
int ut_voc_get_nose_size(ut_voc *voc);
void ut_voc_set_tongue_shape(ut_voc *voc,
    UTFLOAT tongue_index,
    UTFLOAT tongue_diameter);
void ut_voc_set_tenseness(ut_voc *voc, UTFLOAT breathiness);
UTFLOAT * ut_voc_get_tenseness_ptr(ut_voc *voc);
void ut_voc_set_velum(ut_voc *voc, UTFLOAT velum);
UTFLOAT * ut_voc_get_velum_ptr(ut_voc *voc);

void ut_voc_set_diameters(ut_voc *voc,
    int blade_start,
    int lip_start,
    int tip_start,
    UTFLOAT tongue_index,
    UTFLOAT tongue_diameter,
    UTFLOAT *diameters);

int ut_voc_get_counter(ut_voc *voc);


#endif

