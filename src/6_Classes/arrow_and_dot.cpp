#include <iostream>
#include <string>

class Human {
private:
  int age;

public:
  std::string name;

  Human(int humanAge, std::string humanName)
      : age(humanAge), name(std::move(humanName)) {}

  void DoSomething() { std::cout << age << std::endl; }

  static void DisplayAge(const Human &person) {
    std::cout << person.age << std::endl;
  }
};

int main() {
  // Usage of Dot(.)
  Human firstMan(13, "Jim"); // firstMan is an instance of class Human
  std::cout << firstMan.name << std::endl; // accessing member attributes
  firstMan.DoSomething();                  // accessing member functions

  // Usage of Pointer Operator (->)
  Human *secondMan = new Human(24, "Tom");
  std::cout << secondMan->name << std::endl;   // accessing member attributes
  secondMan->DoSomething();                    // accessing member functions
  std::cout << (*secondMan).name << std::endl; // accessing member attributes
  (*secondMan).DoSomething();                  // accessing member functions

  // Usage of Double Colon (::)
  Human::DisplayAge(firstMan);
  firstMan.DisplayAge(firstMan);   // ok but not recommended
  secondMan->DisplayAge(firstMan); // ok but not recommended

  delete (secondMan);

  return 0;
}
