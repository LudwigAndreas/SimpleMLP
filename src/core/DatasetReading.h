#ifndef SIMPLEMLP_DATASETREADING_H
#define SIMPLEMLP_DATASETREADING_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "utils/Sample.h"

std::vector<std::string> split(std::string s, std::string delimiter);

std::vector<s21::Sample> ReadDataset(std::string filename);

std::map<int, char> readSymbolMapping(const std::string &filename);

#endif  // SIMPLEMLP_DATASETREADING_H
