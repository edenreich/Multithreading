#include <iostream>
#include <thread>

class MyClass
{
public:
  int val;
  MyClass(int val) : val(val) {}
};

void myFunction(int myInt1, int & myInt2, MyClass myClass1, MyClass & myClass2)
{
  std::cout << myInt1 << "\n";
  myInt1++;
  myInt2++;
  std::cout << myClass1.val << "\n";
  myClass2.val++;
}

int main()
{
  MyClass myClass1(100);
  MyClass myClass2(200);
  int myInt1 = 3;
  int myInt2 = 15;
  
  std::thread t1(myFunction, myInt1, std::ref(myInt2), myClass1, std::ref(myClass2));

  t1.join();

  std::cout << myInt2 << std::endl;
  std::cout << myClass2.val << std::endl;

  return 0;
}
