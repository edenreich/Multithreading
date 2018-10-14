#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // Stands for MUTual EXclusion

int val = 0;
std::mutex myMutex;

void doWork()
{
  for (int i = 0; i < 100000; i++)
  {
    // The value will only be written by single thread at a time.
    // The other ones will be waiting.
    myMutex.lock();
    val++;
    myMutex.unlock();
  }

  // for (int i = 0; i < 100000; i++)
  // {
  //   if (myMutex.try_lock())
  //   {
  //     val++;
  //     myMutex.unlock();
  //   }
  //   else
  //   {
  //      // do some other cleanup work with the threads instead of making them wait.
  //      // do note the result of val will be unpredicted, because they skip in the else block instead of waiting.
  //   }
  // }
}

int main()
{
  std::vector<std::thread> threads(10);

  for (int i = 0; i < threads.size(); i++)
  {
    threads[i] = std::thread(doWork);
  }

  for (int i = 0; i < threads.size(); i++)
  {
    threads[i].join();
  }

  std::cout << "The value of val is: " << val << std::endl;

  return 0;
}
