#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>
#include <vector>

class IOHandler{
public:
	static void genProblemsTxt();
	static void solveProblems();
	static void findSolution(std::string config, std::vector<int> *board);
	static void saveSolution(bool result, std::string config, std::string board);
	static void exportVisualised(bool result, std::string config, std::string board);
};

#endif
