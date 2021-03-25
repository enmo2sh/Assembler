#ifndef OPERATIONS
#define OPERATIONS
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string, int> getformat();
map<string, string> getopcode();
map<string, int> getNumOperands();
vector<string> noSpace(string line);

#endif // OPERATIONS


