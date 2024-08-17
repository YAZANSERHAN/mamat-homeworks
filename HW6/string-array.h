//
// Created by SRHNW on 8/3/2024.
//

#ifndef FOR_STUDENTS_STRING_ARRAY_H
#define FOR_STUDENTS_STRING_ARRAY_H

#include "string.h"

class StringArray {
public:
    StringArray();
    ~StringArray();
    void add(const String &str);
    size_t size() const;
    const String& operator[](size_t index) const;

private:
    String* strings;
    size_t capacity;
    size_t count;
    void resize();
};

#endif //FOR_STUDENTS_STRING_ARRAY_H
