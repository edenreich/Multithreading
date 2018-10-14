#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

template <typename typeArr>
long long sumNormal(typeArr * arr, int arrLength)
{
  long long sum = 0;
  
  for (int i = 0; i < arrLength; i++)
  {
    sum += arr[i];
  }

  return sum;
}

long long sumParallel(int * arr, int arrLength)
{
  // We check to see how many parallel threads are supported in the current system.
  int hardwareCon = std::thread::hardware_concurrency();
  int supportedThreads = hardwareCon == 0 ? 2 : hardwareCon;

  // We split the amount of datasets per thread.
  const int minDataPerThread = 1000;
  int maxAmountOfThread = (arrLength + minDataPerThread - 1) / minDataPerThread;
  int amountOfThreads = supportedThreads > maxAmountOfThread ? maxAmountOfThread : supportedThreads;
  int dataPerThread = arrLength / amountOfThreads;

  std::vector<long long> results(amountOfThreads);
  std::vector<std::thread> threads(amountOfThreads - 1);

  for (int i = 0; i < amountOfThreads - 1; i++) {
    threads[i] = std::thread([=](long long &result) {
      result = sumNormal(arr + dataPerThread * i, dataPerThread);
    }, std::ref(results[i]));
  }

  int startOffset = dataPerThread * (amountOfThreads - 1);
  results[amountOfThreads - 1] = sumNormal(arr + startOffset, arrLength - startOffset);

  for (int i = 0; i < amountOfThreads - 1; i++)
  {
    threads[i].join();
  }

  return sumNormal(results.data(), results.size());
}

#define ARRAY_SIZE 100000000
int main()
{
  int * arr = new int[ARRAY_SIZE];

  // Fill the arr with integers.
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    arr[i] = i;
  }

  int timeNormal = 0;
  int timeParallel = 0;

  {
    auto start = std::chrono::high_resolution_clock::now();
    long long val = sumNormal(arr, ARRAY_SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    timeNormal = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    std::cout << val << std::endl;
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    long long val = sumParallel(arr, ARRAY_SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    timeParallel = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    std::cout << val << std::endl;
  }

  std::cout << timeNormal << "ms" << std::endl;
  std::cout << timeParallel << "ms" << std::endl;

  delete arr;

  return 0;
}
