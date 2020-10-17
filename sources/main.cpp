// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#include <functions.h>

int main() {
  cout << "Cache L1 : 0.0625mb\n"
          "Cache L2 : 0.25mb\n"
          "Cache L3 : 3mb\n";
  const std::initializer_list<float> bufferSizes{
      0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 2, 4, 4.5};  // mb
  const std::initializer_list<string> travelVariants{DIRECT, REVERSE, RANDOM};

  std::ofstream out{"result.yaml"};
  for (const auto &travelVariant : travelVariants) {
    size_t counter = 1;
    vector<YAML::Node> experiments;
    for (const auto &bufferSize : bufferSizes) {
      double sortingTime = TimeOfExperimentDuration(bufferSize, travelVariant);
      PrintResultsOfExperiment(counter, bufferSize, sortingTime, travelVariant);
      experiments.emplace_back(
          WriteOneExperiment(counter, bufferSize, sortingTime));
      ++counter;
    }
    WriteToFileAllExperiments(travelVariant, out, experiments);
  }
  out.close();
}
