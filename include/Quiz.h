#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>

class Quiz{
public:
	static void run();
private:
	struct Player{
		std::string name;
		uint totalQues;
		uint correctQues;
		double time;
		int score;
		Player(uint totalQues)
		: name(""), totalQues(totalQues), correctQues(0), time(0), score(0) {
		}
	};
	static void generator(std::vector<std::pair<std::string, std::string> > *ques);
	static bool question(std::string q, std::string a);
};

#endif
