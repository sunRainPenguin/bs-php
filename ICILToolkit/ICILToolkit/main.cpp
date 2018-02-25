#include "Util.h"
#include <iostream>

int main()
{
	XMLParser* xmlParser = new XMLParser("LD.xml");
	string LDExp = xmlParser->parseLD();
	xmlParser = new XMLParser("FB.xml");
	string FBStmtList = xmlParser->parseFB();
	Util::generatePNG(xmlParser);
	std::cout << "LDExp :  \n" << LDExp << std::endl;
	return 0;
}

// vim:et
