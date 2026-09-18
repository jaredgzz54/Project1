#include "Resource.h"
#include <iostream>

Resource::Resource() : resourceId(0), name("Default Resource"), isAvailable(true) {}

Resource::Resource(int id, string resName, bool available) : resourceId(id), name(resName), isAvailable(available) {}

int Resource::getResourceId() const {
  return resourceId;
}

string Resource::getName() const {
  return name;
}

bool Resource::getAvailability() const {
  return isAvailable;
}

void Resource::setAvailability(bool available){
  isAvailable = available;
}

void Resource::display() const {
  cout<<"Resource ID: "<<resourceId<<" | Name: "<<name<<" | Status: "<<(isAvailable ? "Available" : "Reserved")<<endl;
}
