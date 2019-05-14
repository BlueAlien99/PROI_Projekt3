#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>

class IOHandler{
public:
	static void genProblemsTxt();
	static void solveProblems();
	static void exportVisualised(bool result, std::string config, std::string board);
};

#endif
