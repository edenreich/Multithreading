#include <iostream>
#include <thread>

// Do work..
void myFunction()
{
  while (true)
  {

  }
}


int main()
{
  // Spawn a thread.
  std::thread t1(myFunction);
  
  // Not possible to copy the thread like so.
  // std::thread t2 = t1;

  // Move the thread to t2
  std::thread t2 = std::move(t1);
  
  // Move the thread back to t1
  t1 = std::move(t2);

  // Create a new t2 thread.
  t2 = std::thread(myFunction);

  // Move the newly created t2 into an active thread = Program crush.
  // because this thread is already active.
  // t1 = std::move(t2);

  t1.join();
  t2.join();

  return 0;
}
