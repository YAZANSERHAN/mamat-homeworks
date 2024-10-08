#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MIN 0

void max(FILE *fd); 

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

    max(fd);

    if (fd != stdin) {
        fclose(fd);
    }

    return 0;
}

void max(FILE *fd) {
    int line_number = 1;
    int grade;
    int max_grade = MIN;
    int retval;

    while (1) {
        retval = fscanf(fd, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) { 
            fprintf(stderr, "Error: not a number at line %d\n", line_number);
            exit(1);
        } else if (grade > MAX || grade < MIN) {
            fprintf(stderr, "Error at line %d: grade %d invalid\n", line_number, grade);
        } else {
            if (max_grade < grade) {
                max_grade = grade;
            }
        }
        line_number++;
    }

    fprintf(stdout, "%d\n", max_grade);
}
