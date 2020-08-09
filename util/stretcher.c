#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utone.h"


ut_data *sp;
ut_ftbl *ft;
ut_paulstretch *ps;

static void process(ut_data *sp, void *ud)
{
    UTFLOAT out;
    ut_paulstretch_compute(sp, ps, NULL, &out);
    ut_out(sp, 0, out);
}


int main(int argc, char *argv[])
{
    UTFLOAT stretch;
    UTFLOAT window;

    if(argc < 7) {
        fprintf(stderr, 
            "Usage: %s sr window_size stretch window  out_dur in.wav out.wav\n", 
            argv[0]
        );
        return 1;
    }

    ut_create(&sp);

    printf("samplerate = %d\n", atoi(argv[1]));
    sp->sr = atoi(argv[1]);

    ut_paulstretch_create(&ps);

    printf("window = %g\n", atof(argv[2]));
    window = atof(argv[2]);
    printf("stretch = %g\n", atof(argv[3]));
    stretch = atof(argv[3]);
    printf("out_dur = %g\n", atof(argv[4]));
    sp->len = sp->sr * atof(argv[4]);
    printf("input = %s\n", argv[5]);
    ut_ftbl_loadfile(sp, &ft, argv[5]);
    printf("output = %s\n", argv[6]);

    strncpy(sp->filename, argv[6], 60);

    ps->wrap = 0;

    ut_paulstretch_init(sp, ps, ft, window, stretch);


    ut_process(sp, NULL, process);

    ut_ftbl_destroy(&ft);
    ut_paulstretch_destroy(&ps);
    ut_destroy(&sp);
    return 0;
}
