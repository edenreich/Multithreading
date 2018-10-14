#include <iostream>
#include <thread>
#include <vector>

int val = 0;

void doWork()
{
  while (val < 10000000)
  {
    // Mutex is needed to lock the threads from writing to val.
    val++;
  }
}


int main()
{
  std::vector<std::thread> threads(32);

  for (int i = 0; i < threads.size(); i++)
  {
    threads[i] = std::thread(doWork);
  }

  for (int i = 0; i < threads.size(); i++)
  {
    threads[i].join();
  }

  // Everytime the value of val is different, because the threads are not synchronized.
  // Means two threads maybe four threads incrementing the global value at the same time.
  // results should be like 10000001 sometimes 10000003 depending on how many threads running concurrently
  std::cout << "The value of val is: " << val << std::endl;

  return 0;
}
