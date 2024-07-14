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
    }

    if (!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    if (argc == 4 && strcmp(argv[2], "-nbins") == 0) {
        nbins = atoi(argv[3]);
    }

    int grade = 0;
    int line_n = 1;
    int bins = 100 / nbins;
    int *hist = (int *)malloc(bins * sizeof(int));

    while (1) {
        int retval = fscanf(f, "%d", &grade);

        if(retval == EOF){
            break;
        } else if(retval != 1)
        {
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }

        if (grade < 0 || grade > 100) {
            fprintf(stderr, "Error at line %d: grade %d invalid\n", line_n, grade);
            exit(1);
        }

        for (int i = 0; i < nbins; i++) {
            if (grade >= i * bins && grade < (i + 1) * bins) {
                hist[i]++;
            }
        }

        if (grade >= nbins * bins && grade <= 100) {
            hist[nbins - 1]++;
        }

        line_n++;
    }

    for (int i = 1; i <= nbins; i++) {
        int end = (i * bins) - 1;

        if (i == nbins) {
            end = 100;
        }

        printf("%d-%d\t%d\n", (i - 1) * bins, end, hist[i - 1]);
    }
}