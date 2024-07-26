// Created by SRHNW on 7/22/2024.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"
#define MAX_GRADE 100
#define MIN_GRADE 0
#define INVALID -1

#ifndef HAVE_STRDUP
char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup) {
        memcpy(dup, s, len);
    }
    return dup;
}
#endif

typedef struct course {
    char* name;
    int grade;
} course_s;

typedef struct student {
    char* name;
    int id;
    struct list *courses;
} student_s;

struct grades {
    struct list *students;
};

int course_clone(void *element, void **output) {
    if (!element || !output) return INVALID;
    course_s *new_course = malloc(sizeof(course_s));
    if (!new_course) return INVALID;
    course_s *course = (course_s *)element;
    new_course->name = strdup(course->name);
    if (!new_course->name) {
        free(new_course);
        return INVALID;
    }
    new_course->grade = course->grade;
    *output = new_course;
    return 0;
}

void course_destroy(void *element) {
    if (!element) return;
    course_s *course = (course_s *)element;
    free(course->name);
    free(course);
}

int student_clone(void *element, void **output) {
    if (!element || !output) return INVALID;
    student_s *new_student = malloc(sizeof(student_s));
    if (!new_student) return INVALID;
    student_s *student = (student_s *)element;
    new_student->name = strdup(student->name);
    if (!new_student->name) {
        free(new_student);
        return INVALID;
    }
    new_student->id = student->id;
    new_student->courses = list_init(course_clone, course_destroy);
    struct iterator *p_list = list_begin(student->courses);
    while (p_list) {
        course_s *course = list_get(p_list);
        list_push_back(new_student->courses, course);
        p_list = list_next(p_list);
    }
    *output = new_student;
    return 0;
}

void student_destroy(void *element) {
    if (!element) return;
    student_s *student = (student_s *)element;
    list_destroy(student->courses);
    free(student->name);
    free(student);
}

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, or NULL in case of an error
 */
struct grades* grades_init() {
    struct grades *grades = malloc(sizeof(struct grades));
    if (!grades) return NULL;
    grades->students = list_init(student_clone, student_destroy);
    if (!grades->students) {
        free(grades);
        return NULL;
    }
    return grades;
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades) {
    if (!grades) return;
    list_destroy(grades->students);
    free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id) {
    if (!grades || !name || id < 0) return INVALID;

    struct iterator *p_list = list_begin(grades->students);
    while (p_list) {
        student_s *student = list_get(p_list);
        if (student->id == id) return INVALID; // Duplicate id found
        p_list = list_next(p_list);
    }

    // Allocate memory for a new student
    student_s *new_student = malloc(sizeof(student_s));
    if (!new_student) return INVALID;

    // Set student id and duplicate name
    new_student->id = id;
    new_student->name = strdup(name);
    if (!new_student->name) {
        free(new_student); // Free allocated memory if name duplication fails
        return INVALID;
    }

    // Initialize the courses list for the new student
    new_student->courses = list_init(course_clone, course_destroy);

    // Add the new student to the students list
    list_push_back(grades->students, new_student);
    return 0; // Success
}


/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Fails if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades, const char *name, int id, int grade) {
    if (!grades || (grade > MAX_GRADE || grade < MIN_GRADE)) {
        return INVALID;
    }
    struct iterator *p_list = list_begin(grades->students);
    student_s *student = NULL;
    while (p_list) {
        student = list_get(p_list);
        if (student->id == id) {
            break;
        }
        p_list = list_next(p_list);
    }
    if (!student || student->id != id) return INVALID; // Ensure student exists

    struct iterator *c_list = list_begin(student->courses);
    while (c_list) {
        course_s *course = list_get(c_list);
        if (strcmp(course->name, name) == 0) return INVALID; // Course already exists
        c_list = list_next(c_list);
    }
    course_s *new_course = malloc(sizeof(course_s));
    if (!new_course) return INVALID;
    new_course->name = strdup(name);
    if (!new_course->name) {
        free(new_course);
        return INVALID;
    }
    new_course->grade = grade;
    list_push_back(student->courses, new_course);
    return 0;
}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out) {
    if (!grades || !out) return INVALID;

    struct iterator *p_list = list_begin(grades->students);
    student_s *student = NULL;

    while (p_list) {
        student_s *current_student = list_get(p_list);
        if (current_student->id == id) {
            student = current_student;
            break;
        }
        p_list = list_next(p_list);
    }

    if (!student) {
        *out = NULL;
        return INVALID;
    }

    *out = strdup(student->name);
    if (!*out) return INVALID;

    struct iterator *c_list = list_begin(student->courses);
    if (!c_list) return 0.0; // No grades, average is zero

    int sum = 0, count = 0;
    while (c_list) {
        course_s *course = list_get(c_list);
        sum += course->grade;
        count++;
        c_list = list_next(c_list);
    }

    return count > 0 ? (float)sum / count : 0.0;
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id) {
    if (!grades) return INVALID;

    struct iterator *p_list = list_begin(grades->students);
    student_s *student = NULL;

    while (p_list) {
        student_s *current_student = list_get(p_list);
        if (current_student->id == id) {
            student = current_student;
            break;
        }
        p_list = list_next(p_list);
    }

    if (!student) return INVALID;

    printf("%s %d:", student->name, student->id);
    struct iterator *c_list = list_begin(student->courses);
    while (c_list) {
        course_s *course = list_get(c_list);
        printf(" %s %d", course->name, course->grade);
        if (list_next(c_list)) {
            printf(",");
        }
        c_list = list_next(c_list);
    }
    printf("\n");
    return 0;
}


/**
 * @brief Prints all students in "grades", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades) {
    if (!grades) return INVALID;
    struct iterator *p_list = list_begin(grades->students);
    while (p_list) {
        student_s *student = list_get(p_list);
        grades_print_student(grades, student->id);
        p_list = list_next(p_list);
    }
    return 0;
}
