#include "Util.h"
#include <iostream>

int main()
{
	// parse LD
	XMLParser* xmlParser = new XMLParser("LD.xml");
	xmlParser->parseLD();
	Util::generatePNG(xmlParser);

	// parse FB
	xmlParser = new XMLParser("FB.xml");
	xmlParser->parseFB();
	
	return 0;
}

// vim:et
