#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int val = 0;
std::mutex myMutex;

void doWork()
{
  for (int i = 0; i < 1000000; i++)
  {
    std::lock_guard<std::mutex> guard(myMutex);
    val++;
  }
}

int main()
{
  std::thread t1(doWork);

  t1.join();

  std::cout << "The value of val is: " << val << "\n";

  return 0;
}
