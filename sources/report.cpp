// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#include "../include/functions.h"

YAML::Node WriteOneExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime) {
  YAML::Node node;
  node["experiment"]["number"] = counter;
  std::ostringstream size;
  size << bufferSize << "mb";
  node["experiment"]["input_data"]["buffer_size"] = size.str();
  std::ostringstream time;
  time << std::fixed << std::setprecision(2) << sortingTime << "ns";
  node["experiment"]["results"]["duration"] = time.str();
  return node;
}

void WriteToFileAllExperiments(const string &travelVariant, std::ofstream &out,
                               const vector<YAML::Node> &experiments) {
  YAML::Node node;
  node["investigation"]["travel_variant"] = travelVariant;
  node["investigation"]["experiments"] = experiments;
  out << node << "\n\n";
}
