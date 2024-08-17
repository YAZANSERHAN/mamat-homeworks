#ifndef FOR_STUDENTS_STRING_H
#define FOR_STUDENTS_STRING_H

#include "generic-field.h"  // Assuming this is needed
#include <iostream>

class StringArray;  // Forward declaration if not included in generic-field.h

class String : public GenericString {
public:
    String();
    String(const String &str);
    String(const char *str);
    ~String();

    size_t size() const;

    GenericString& operator=(const String& str) ;
    GenericString& operator=(const char* str) override;

    bool operator==(const GenericString &other) const override;
    bool operator==(const char *other) const override;

    StringArray split(const char *delimiters) const override;
    int to_integer() const override;
    String& as_string() override;
    const String& as_string() const override;
    String& trim() override;

    String substr(size_t start) const;

    bool starts_with(const String &prefix) const;
    bool is_empty() const;
    const char* getData() const;  // Declaration

private:
    size_t length;
    char* data;
    void trim_whitespace();
};

// Free function declaration
GenericString* make_string(const char *str);

#endif  // FOR_STUDENTS_STRING_H
