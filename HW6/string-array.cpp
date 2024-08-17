//
// Created by SRHNW on 8/3/2024.
//

#include "string-array.h"
#include "string.h"
#include <stdexcept>  // For std::out_of_range
#include <cstring> 

StringArray::StringArray() : strings(nullptr), capacity(10), count(0) {
    strings = new String[capacity];
}

StringArray::~StringArray(){
    delete[] strings;
}

void StringArray::add(const String &str){
    if(count==capacity)
    {
        resize();
    }
    strings[count++]=str;
}

size_t StringArray::size() const{
    return count;
}

const String& StringArray::operator[](size_t index) const{
    if(index >= count){
        throw std::out_of_range("Index out of range");
    }
    return strings[index];
}

void StringArray::resize(){
    size_t newCapacity = capacity == 0 ? 1 : capacity*2;
    String* newArray = new String[newCapacity];

    for(size_t i=0; i < count; i++){
        newArray[i] = strings[i];
    }
    delete[] strings;
    strings = newArray;
    capacity = newCapacity;
}

