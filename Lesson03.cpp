#include <iostream>
#include <thread>

void myFunction()
{
  std::cout << "hello from myFunction!" << "\n";
  std::cout << std::this_thread::get_id() << "\n";
}

int main()
{
  std::thread t1(myFunction);
  std::thread t2(myFunction);

  t1.join();
  t2.join();

  return 0;
}
