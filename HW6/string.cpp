#include "string.h"
#include <cstring>
#include "string-array.h"

String::String() {  // Default constructor
    length = 0;
    data = new char[1];
    data[0] = '\0';
}

String::String(const char* str) { // Constructor from C-string
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

String::String(const String &str) { // Copy constructor
    length = str.size();
    data = new char[length + 1];
    strcpy(data, str.getData());
}

String::~String() { // Destructor
    delete[] data;
}

size_t String::size() const { // Get string size (excluding null terminator)
    return length;
}

const char* String::getData() const { // Accessor for raw data
    return data;
}

GenericString& String::operator=(const String &str) {
    if (this != &str) {
        delete[] data;
        length = str.size();
        data = new char[length + 1];
        strcpy(data, str.getData());
    }
    return *this;
}

GenericString& String::operator=(const char* str) {
    if (this->data != str) {  // Check for self-assignment
        delete[] data;  // Delete existing data

        if (str) {  // If the input string is not null
            length = strlen(str);
            data = new char[length + 1];  // Allocate memory for new string
            strcpy(data, str);  // Copy the string
        } else {  // Handle the case of assigning nullptr
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }
    return *this;  // Return the current object
}

bool String::operator==(const GenericString &other) const {
    // Compare lengths first
    if (this->length != other.as_string().size()) {
        return false;
    }

    // Compare data using strcmp
    if (strcmp(this->data, other.as_string().getData()) != 0) {
        return false;
    }

    return true;  // Both length and data are equal
}

bool String::operator==(const char *other) const {
    if (other == nullptr) {
        return false;  // A String is never equal to a nullptr
    }
    return strcmp(this->data, other) == 0;
}

StringArray String::split(const char *delimiters) const {
    StringArray result;
    char *copy = new char[length + 1];
    strcpy(copy, data);

    char *token = strtok(copy, delimiters);
    while (token != nullptr) {
        result.add(String(token));
        token = strtok(nullptr, delimiters);
    }
    delete[] copy;
    return result;
}

int String::to_integer() const {
    return std::atoi(data);
}

String& String::as_string() {
    return *this;
}

const String& String::as_string() const {
    return *this;
}

String& String::trim() {
    trim_whitespace();
    return *this;
}

void String::trim_whitespace() {
    if (data == nullptr) {
        return;
    }

    size_t start = 0;
    while (start < length && std::isspace(static_cast<unsigned char>(data[start]))) {
        ++start;
    }

    size_t end = length;
    while (end > start && std::isspace(static_cast<unsigned char>(data[end - 1]))) {
        --end;
    }

    size_t new_length = end - start;
    char *new_data = new char[new_length + 1];
    strncpy(new_data, data + start, new_length);
    new_data[new_length] = '\0';

    delete[] data;
    data = new_data;
    length = new_length;
}

GenericString* make_string(const char *str) { // Global function
    return new String(str);
}

String String::substr(size_t start) const {
    if (start >= length) {
        return String("");
    }
    return String(data + start);
}

bool String::starts_with(const String &prefix) const {
    if (prefix.size() > length) {
        return false;
    }
    return strncmp(data, prefix.getData(), prefix.size()) == 0;
}

bool String::is_empty() const {
    return length == 0;
}
