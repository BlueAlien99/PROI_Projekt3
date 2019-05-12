#ifndef SETUP_H
#define SETUP_H

#include <memory>

class Setup{
	class SetupImpl;
	std::unique_ptr<SetupImpl> impl;
public:
	Setup();
	~Setup();
	void help();
	void run();
	void newBoard();
	void algorithm();
	void printDebBoard();
};

#endif
