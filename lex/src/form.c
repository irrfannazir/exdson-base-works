#include <stdio.h>

int change_to_form(const char *fnw, const char *fn1, const char *fn2) {
    FILE *fhw = fopen(fnw, "w");
    FILE *fh1 = fopen(fn1, "r");
    FILE *fh2 = fopen(fn2, "r");
    if (!fhw || !fh1 || !fh2) {
        if (fhw) fclose(fhw);
        if (fh1) fclose(fh1);
        if (fh2) fclose(fh2);
        return -1;
    }

    int isnewline, lexValue;
    while (fscanf(fh1, "%d %d", &isnewline, &lexValue) == 2) {
        if (isnewline) {
            fprintf(fhw, "0 \n-1 %d\n", lexValue);
        } else {
            fprintf(fhw, "%d ", lexValue);
            int c;
            while ((c = fgetc(fh2)) != EOF && c != '\n') {
                fputc(c, fhw);
            }
            fputc('\n', fhw);
        }
    }
    fputs("0 \n", fhw);

    int ret = (ferror(fh1) || ferror(fh2) || ferror(fhw)) ? -1 : 0;
    fclose(fhw);
    fclose(fh1);
    fclose(fh2);
    return ret;
}