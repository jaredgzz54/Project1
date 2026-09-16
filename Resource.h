#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource{
private:
  int resourceld;
  string name;
  bool isAvailable;

public:
  Resource();
  Resource(int id, string resName, bool available);

int getResource() const;
string getName() const;
bool getAvailability() const;

void setAvailability(bool available);
void display() const;

};

#endif RESOURCE_H
