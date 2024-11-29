#include "pch.h"
#include <iostream>
#include "Computer.h"


int main(int argc, char* argv[])
{
	Computer computer;
	Position pos = computer.GenerateTarget();
	std::cout << "Position: " << pos.x << " " << pos.y << std::endl;

	std::cout << "Hello World!";
}
