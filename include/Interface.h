#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>

class Interface{
	class InterfaceImpl;
	std::unique_ptr<InterfaceImpl> impl;
public:
	Interface(uint xx, uint yy, uint pa = 0, uint ro = 0,
			uint bi = 0, uint qu = 0, uint kn = 0, uint ki = 0);
	~Interface();
	int isSqFree(uint xx, uint yy);
	bool algorithm();
	void printBoard(bool debug);
	void printConfig();
};

#endif
