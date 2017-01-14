/*Things
-Input file
-Read file
*/
#include "FIleIO.h"
std::string inputText;
std::string returnText;
std::string ReturnTextItem(std::string lookFor,std::string fileName) {

	std::ifstream file = returnTextFile(fileName);
	if (file.is_open()) {
		while(std::getline(file, inputText)) {
			if (inputText == lookFor) {
				std::getline(file, inputText);
				returnText = inputText;
				std::getline(file, inputText);
				returnText.append('\n'+inputText);
				return returnText;
			}
		}
		
	}
	std::cout << "Cannot find " << lookFor << " in planetTextFile.txt" << '\n';
	return" ";
}

std::ifstream returnTextFile(std::string fileName) {
	std::ifstream file;
	file.open(fileName,std::ios::in);
	return file;
	
}