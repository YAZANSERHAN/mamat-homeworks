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
    int line_number = 1;
    int grade;
    int hist[MAX + 1] = {0}; // Include MAX in the range
    int fine_grades_num = 0;
    int wrong_grades = 0;
    int counter = 0;
    int median_grade;
    int retval;

    while (1) {
        retval = fscanf(fd, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) { 
            fprintf(stderr, "Error: not a number at line %d\n", line_number);
            wrong_grades++;
        } else if (grade > MAX || grade < MIN) {
            fprintf(stderr, "Error at line %d: grade %d out of bounds\n", line_number, grade);
            wrong_grades++;
        } else {
            hist[grade]++;
            fine_grades_num++;
        }
        line_number++;
    }

    int median_position = fine_grades_num / 2;
    for (int i = 0; i <= MAX; i++) {
        counter += hist[i];
        if (counter > median_position) {
            median_grade = i;
            break;
        }
    }

    fprintf(stdout, "Median grade: %d\n", median_grade);
}
