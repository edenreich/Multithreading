#include <iostream>
#include <thread>

int main()
{
  // The amount of thread which can run concurrency on the current system.
  int numThreads = std::thread::hardware_concurrency();

  std::cout << numThreads;

  return 0;
}
