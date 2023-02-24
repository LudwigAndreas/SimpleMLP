#ifndef SIMPLEMLP_DATASETREADING_HPP
#define SIMPLEMLP_DATASETREADING_HPP

#include <vector>
#include <string>
#include <fstream>

#include "utils/Sample.hpp"

std::vector<std::string> split (std::string s, std::string delimiter);

std::vector<s21::Sample> ReadDataset(std::string filename);


#endif //SIMPLEMLP_DATASETREADING_HPP
