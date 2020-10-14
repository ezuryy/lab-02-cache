// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#include "../include/functions.h"

int64_t *MakeRandArray(const size_t &size) {
  auto *arr = new int64_t[size];
  std::random_device rd;
  std::mt19937 mt(rd());
  //[-2^63; 2^63-1]
  std::uniform_int_distribution<int64_t> dist(
      -(pow(2, 63)), static_cast<int64_t>(pow(2, 63) - 1));
  for (size_t i = 0; i < size; ++i) {
    arr[i] = dist(mt);
  }
  return arr;
}

double ExperimentDuration(const float &bufferSize,
                          const string &travelVariant) {
  auto size = static_cast<size_t>(1024 * 128 * bufferSize);
  int64_t *arr = MakeRandArray(size);
  int64_t elem = 0;
  std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
  std::chrono::duration<double> sortingTime{};

  if (travelVariant == "direct") {
    //прорев
    for (size_t i = 0; i < size; i += 8) {
      elem = arr[i];
    }
    //обход
    startTime = std::chrono::steady_clock::now();
    for (size_t k = 0; k < 1000; ++k) {
      for (size_t i = 0; i < size; i += 8) {
        elem = arr[i];
      }
    }
    endTime = std::chrono::steady_clock::now();

  } else if (travelVariant == "reverse") {
    //прогрев
    for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
      elem = arr[i];
    }
    //обход
    startTime = std::chrono::steady_clock::now();
    for (size_t k = 0; k < 1000; ++k) {
      for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
        elem = arr[i];
      }
    }
    endTime = std::chrono::steady_clock::now();

  } else if (travelVariant == "random") {
    vector<size_t> indexesForRandomTravel;
    for (size_t j = 0; j < size; j += 8) indexesForRandomTravel.push_back(j);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexesForRandomTravel.begin(), indexesForRandomTravel.end(),
                 g);
    //прогрев
    for (int i = static_cast<int>(size - 9); i >= 0; i -= 8) {
      elem = arr[i];
    }
    //обход
    startTime = std::chrono::steady_clock::now();
    for (size_t k = 0; k < 1000; ++k) {
      std::shuffle(indexesForRandomTravel.begin(), indexesForRandomTravel.end(),
                   g);
      for (const auto &index : indexesForRandomTravel) {
        elem = arr[index];
      }
    }
    endTime = std::chrono::steady_clock::now();
  }
  sortingTime = endTime - startTime;
  std::ofstream out;
  out.open("trash.txt");
  out << elem << '\n';
  remove("trash.txt");
  delete[] arr;
  return 8000000 * sortingTime.count() / size;
}
