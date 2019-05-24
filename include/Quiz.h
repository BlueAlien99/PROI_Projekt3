#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>

class Quiz{
private:
	void generator(std::vector<std::pair<std::string, std::string> > *ques);
	bool question(std::string q, std::string a);
};

#endif
