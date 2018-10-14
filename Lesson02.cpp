#include <iostream>
#include <thread>

void myFunction()
{
  std::cout << "Hello from myFunction!\n";
}

class MyFunctor
{
public:
  void operator()()
  {
    std::cout << "Hello from MyFunctor!\n";
  }
};

int main()
{
  MyFunctor mf;

  std::thread t1(myFunction);
  std::thread t2(mf);
  std::thread t3{ MyFunctor() };
  std::thread t4([] {
    std::cout << "Hello from myLambda\n";
  });

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}
