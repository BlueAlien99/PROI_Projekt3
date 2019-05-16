#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <string>
#include <set>

class Utilities{
public:
	static uint get_uint();
	static void getPermutations(std::string str, std::set<std::string> *perms, uint lock = 0);
};

#endif
