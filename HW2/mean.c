#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MIN 0

void mean(FILE *fd); 

int main(int argc, char **argv){
    FILE *fd;

    if(argc == 1 || !strcmp("-", argv[1])){
        fd = stdin;
    } else { 
        fd = fopen(argv[1], "r");
    }
    if(!f){
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
         }   
    mean(f);
    if (fd != stdin) {
        fclose(fd);
    }
    return 0;
}

void mean(FILE *fd){
    int grade;
    int retval;
    double grade_sum; 
    int line_n;
    int fine_grades_number;

    avg = 0;
    line_n = 0;

    while(1){
        retval = fscanf(fd, "%d", &grade);
        if(retval == EOF){
            break;
        }
        else if(retval != 1){ 
            fprintf(stderr, "Error: not a number\n|");
            exit(1);
        }
        else if(grade > MAX || grade < MIN){
        fprintf(stderr, "Error at line "%d": grade "%d" \n",)line_number, grade;
        }
        else{
         grade_sum += grade;
         fine_grades_number++;
          }
        line_n++;
    }
   printf("%.2lf\n", grade_sum / fine_grades_number);
}
