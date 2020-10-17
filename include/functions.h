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

const string DIRECT = "direct";
const string REVERSE = "reverse";
const string RANDOM = "random";

std::unique_ptr<int64_t[]> MakeRandArray(const size_t &size);

std::unique_ptr<int64_t[]> WarmingUp(std::unique_ptr<int64_t[]> arr,
                                     const size_t& size,
                                     const string &travelVariant,
                                     int64_t &elem);

std::unique_ptr<int64_t[]> Duration(std::unique_ptr<int64_t[]> arr,
                                    const size_t& size,
                                    const string &travelVariant, int64_t &elem);

double TimeOfExperimentDuration(const float &bufferSize, //mb
                                const string &TravelVariant);

void PrintResultsOfExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime,
                              const string &TravelVariant);

YAML::Node WriteOneExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime);

void WriteToFileAllExperiments(const string &TravelVariant, std::ofstream &out,
                               const vector<YAML::Node> &experiments);

#endif  // TEMPLATE_FUNCTIONS_H
