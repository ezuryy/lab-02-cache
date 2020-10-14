// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#ifndef TEMPLATE_FUNCTIONS_H
#define TEMPLATE_FUNCTIONS_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

using std::cout;
using std::string;
using std::vector;

int64_t *MakeRandArray(const size_t &size);

double ExperimentDuration(const float &bufferSize, const string &TravelVariant);

void PrintResultsOfExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime,
                              const string &TravelVariant);

YAML::Node WriteOneExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime);

void WriteToFileAllExperiments(const string &TravelVariant, std::ofstream &out,
                               const vector<YAML::Node> &experiments);

#endif  // TEMPLATE_FUNCTIONS_H
