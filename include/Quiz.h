#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>

struct Player{
	std::string name;
	uint totalQues;
	uint correctQues;
	int time;
	int score;

	Player(uint totalQues = 0)
	: name(""), totalQues(totalQues), correctQues(0), time(0), score(0) {
	}
};

class Quiz{
public:
	static void run();
private:
	static void generator(std::vector<std::pair<std::string, std::string> > *ques);
	static bool question(std::string q, std::string a);
};

#endif
