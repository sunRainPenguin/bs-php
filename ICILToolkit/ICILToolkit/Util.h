#include "XMLParser.h"
#include <windows.h>
#include <fstream>

class Util
{
public:
	Util();
	~Util();

	static void generatePNG(XMLParser* parser);
};

