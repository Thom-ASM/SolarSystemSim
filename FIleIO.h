#pragma once
#include <fstream>
#include <string>
#include<iostream>//Remove this?

std::string ReturnTextItem(std::string lookFor, std::string fileName);

std::ifstream returnTextFile(std::string fileName);