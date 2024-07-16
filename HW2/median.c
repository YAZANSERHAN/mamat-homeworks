#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MIN 0

void median(FILE *fd);

int main(int argc, char **argv) {
    FILE *fd;

    if (argc == 1 || !strcmp("-", argv[1])) {
        fd = stdin;
    } else { 
        fd = fopen(argv[1], "r");
    }

    if (!fd) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }   

    median(fd);

    if (fd != stdin) {
        fclose(fd);
    }

    return 0;
}

void median(FILE *fd) {
    int *grades = NULL;
    int grade;
    int retval;
    int count = 0;
    int capacity = 10;

    grades = (int *)malloc(capacity * sizeof(int));
    if (!grades) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    while (1) {
        retval = fscanf(fd, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) {
            fprintf(stderr, "Error: not a number\n");
            free(grades);
            exit(1);
        } else if (grade > MAX || grade < MIN) {
            fprintf(stderr, "Error at line %d: grade %d invalid\n", count + 1, grade);
        } else {
            if (count == capacity) {
                capacity *= 2;
                grades = (int *)realloc(grades, capacity * sizeof(int));
                if (!grades) {
                    fprintf(stderr, "Memory reallocation failed\n");
                    return;
                }
            }
            grades[count++] = grade;
        }
    }

    if (count == 0) {
        fprintf(stderr, "No valid grades to calculate median\n");
        free(grades);
        return;
    }

    // Sort the grades array
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (grades[j] > grades[j + 1]) {
                int temp = grades[j];
                grades[j] = grades[j + 1];
                grades[j + 1] = temp;
            }
        }
    }

    double median;
    if (count % 2 == 0) {
        median = (grades[count / 2 - 1] + grades[count / 2]) / 2.0;
    } else {
        median = grades[count / 2];
    }

    printf("Median: %.2lf\n", median);

    free(grades);
}
