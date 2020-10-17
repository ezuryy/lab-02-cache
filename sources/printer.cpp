// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#include <functions.h>

void PrintResultsOfExperiment(const size_t &counter, const float &bufferSize,
                              const double &sortingTime,
                              const string &travelVariant) {
  if (counter == 1) {
    cout << "\ninvestigation: \n"
         << "\ttravel_variant: \"" << travelVariant << "\"\n"
         << "\texperiments:\n";
  }
  std::ostringstream size;
  size << bufferSize;
  cout << std::fixed << std::setprecision(2) << "\t- experiment: \n"
       << "\t\tnumber: " << counter << '\n'
       << "\t\tinput_data:\n"
       << "\t\t\tbuffer_size: \"" << size.str() << "mb\"\n"
       << "\t\tresults:\n"
       << "\t\t\tduration: \"" << sortingTime << "ns\"\n";
}
