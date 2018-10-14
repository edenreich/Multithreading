#include <iostream>
#include <thread>

void doWork(int & data)
{
  data = 0;
  
  for (int i = 0; i < 1000000; i++)
  {
    data += i;
  }
}

int myFunction()
{
  int val = 0;
  
  std::thread t1(doWork, std::ref(val));
  
  // Detach the thread to run in the background.
  t1.detach();

  // Getting random results everytime this function is called.
  // Because the thread still did not finish the work before we return the value.
  return val;
}


int main()
{
  std::cout << myFunction() << std::endl;

  return 0;
}
