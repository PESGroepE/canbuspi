/**
@file Event.cpp
*/

#include "Event.h"

Event::Event():type(NONE),data() {}

Event::Event(Type t, std::string d):type(t), data(d) {

}

Type Event::getType() const {
    return type;
}

std::string Event::getData() const {
    return data;
}

void Event::setType(Type t) {
    type = t;
}

void Event::setData(std::string s) {
    data = s;
}
