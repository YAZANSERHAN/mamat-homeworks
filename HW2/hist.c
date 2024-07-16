#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *f;
    int nbins = 10;

    if (argc == 1 || !strcmp("-", argv[1])) { 
        f = stdin;
    } else { 
        f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
            return 1;
        }
    }

    if (argc == 4 && strcmp(argv[2], "-nbins") == 0) {
        nbins = atoi(argv[3]);
        if (nbins <= 0) {
            fprintf(stderr, "Invalid number of bins: \"%s\"\n", argv[3]);
            return 1;
        }
    }

    int grade = 0;
    int line_n = 1;
    int bin_size = 100 / nbins;
    int *hist = (int *)calloc(nbins, sizeof(int));

    if (!hist) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    while (1) {
        int retval = fscanf(f, "%d", &grade);

        if (retval == EOF) {
            break;
        } else if (retval != 1) {
            fprintf(stderr, "Error: not a number at line %d\n", line_n);
            free(hist);
            if (f != stdin) fclose(f);
            return 1;
        }

        if (grade < 0 || grade > 100) {
            fprintf(stderr, "Error at line %d: grade %d invalid\n", line_n, grade);
            free(hist);
            if (f != stdin) fclose(f);
            return 1;
        }

        int bin_index = grade / bin_size;
        if (bin_index >= nbins) {
            bin_index = nbins - 1;  // Ensure the last bin includes the grade 100
        }

        hist[bin_index]++;
        line_n++;
    }

    for (int i = 0; i < nbins; i++) {
        int start = i * bin_size;
        int end = (i == nbins - 1) ? 100 : (i + 1) * bin_size - 1;
        printf("%d-%d\t%d\n", start, end, hist[i]);
    }

    free(hist);
    if (f != stdin) fclose(f);

    return 0;
}
