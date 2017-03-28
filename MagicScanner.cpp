#include "Scanner.hpp"


int main(int argv, char ** argc)
{
	if(argv < 2)
	{
		cout << "Usage : MagicScanner inputfile" << endl;
		exit(0);
	}

	Scanner fileScanner(argc[1]);
}
