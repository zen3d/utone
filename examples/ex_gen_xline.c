#include <stdio.h>
#include "utone.h"

int main() {
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl *ft;
    ut_ftbl_create(ut, &ft, 4096);
    ut_gen_xline(ut, ft, "0 0.0001 4096 1.0");
    int i;
    FILE *fp= fopen("plot.dat", "w");
    for(i = 0; i < ft->size; i++) {
        fprintf(fp, "%d %g\n", i, ft->tbl[i]);
    }
    printf("%ld plot points written to plot.dat. Run write_plot.sh to see the result.\n", ft->size); 
    fclose(fp);
    ut_ftbl_destroy(&ft);
    ut_destroy(&ut);
    return 0;
}
