#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "Quiz.h"

#include <fstream>
#include <string>
#include <vector>

class IOHandler{
public:
	static void cleanup();
	static void genProblemsTxt();
	static void solveProblems(bool brute);
	static void findSolution(std::string config, std::vector<int> *board);
	static void saveSolution(bool result, std::string config, std::string board);
	static void exportVisualised(bool result, std::string config, std::string board);
	static void saveQuizScore(std::string name, uint correct, uint total,
													int time, int score);
	static void printScoreboard();
private:
	static bool importPlayerStats(struct Player *player, std::ifstream *file);
	static std::string extractString(std::string key, std::string data);
	static uint extractUint(std::string key, std::string data);
};

#endif
