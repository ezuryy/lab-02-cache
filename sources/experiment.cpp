// Copyright 2020 Kidinova Daria <daria.kidinova@gmail.com>

#include <functions.h>

int64_t GLOBAL_VARIABLE;

std::unique_ptr<int64_t[]> MakeRandArray(const size_t &size) {
  std::unique_ptr<int64_t[]> arr(new int64_t[size]);
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

std::unique_ptr<int64_t[]> WarmingUp(std::unique_ptr<int64_t[]> arr,
                                     const size_t &size,
                                     const string &travelVariant,
                                     int64_t &elem) {
  if (travelVariant == DIRECT) {
    for (size_t i = 0; i < size; i += 8) {
      elem = arr[i];
    }
  } else if (travelVariant == REVERSE) {
    for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
      elem = arr[i];
    }
  } else if (travelVariant == RANDOM) {
    vector<size_t> indexesForRandomTravel;
    for (size_t j = 0; j < size; j += 8) indexesForRandomTravel.push_back(j);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexesForRandomTravel.begin(), indexesForRandomTravel.end(),
                 g);
    for (int i = static_cast<int>(size - 9); i >= 0; i -= 8) {
      elem = arr[i];
    }
  }
  return arr;
}

std::unique_ptr<int64_t[]> Duration(std::unique_ptr<int64_t[]> arr,
                                    const size_t &size,
                                    const string &travelVariant,
                                    int64_t &elem) {
  if (travelVariant == DIRECT) {
    for (size_t k = 0; k < 1000; ++k) {
      for (size_t i = 0; i < size; i += 8) {
        elem = arr[i];
      }
    }
  } else if (travelVariant == REVERSE) {
    for (size_t k = 0; k < 1000; ++k) {
      for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
        elem = arr[i];
      }
    }
  } else if (travelVariant == RANDOM) {
    vector<size_t> indexesForRandomTravel;
    for (size_t j = 0; j < size; j += 8) indexesForRandomTravel.push_back(j);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexesForRandomTravel.begin(), indexesForRandomTravel.end(),
                 g);
    for (size_t k = 0; k < 1000; ++k) {
      std::shuffle(indexesForRandomTravel.begin(), indexesForRandomTravel.end(),
                   g);
      for (const auto &index : indexesForRandomTravel) {
        elem = arr[index];
      }
    }
  }
  return arr;
}

double TimeOfExperimentDuration(const float &bufferSize,  // mb
                                const string &travelVariant) {
  int64_t elem = 0;
  auto size = static_cast<size_t>(1024 * 128 * bufferSize);
  std::unique_ptr<int64_t[]> arr = MakeRandArray(size);
  arr = WarmingUp(std::move(arr), size, travelVariant, elem);

  auto startTime = std::chrono::steady_clock::now();
  arr = Duration(std::move(arr), size, travelVariant, elem);
  auto endTime = std::chrono::steady_clock::now();

  std::chrono::duration<double> sortingTime = endTime - startTime;
  GLOBAL_VARIABLE = elem;
  return 8000000 * sortingTime.count() / size;
}
