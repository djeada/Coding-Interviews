#include <iostream>
#include <string>

class Human {
private:
  int age;
  std::string occupation;

public:
  std::string name;

  // Constructor to initialize a Human object
  Human(int humanAge, const std::string &humanName,
        const std::string &humanOccupation)
      : age(humanAge), name(humanName), occupation(humanOccupation) {}

  // Member function to simulate an action
  void DoSomething() const {
    std::cout << name << " of age " << age << " is doing something.\n";
  }

  // Member function to set occupation
  void SetOccupation(const std::string &newOccupation) {
    occupation = newOccupation;
  }

  // Member function to display occupation
  void DisplayOccupation() const {
    std::cout << name << " works as a " << occupation << ".\n";
  }

  // Static function to display age of a Human object
  static void DisplayAge(const Human &person) {
    std::cout << person.name << " is " << person.age << " years old.\n";
  }
};

int main() {
  // Usage of Dot(.)
  Human firstMan(13, "Jim", "Student");
  std::cout << "Name: " << firstMan.name << std::endl;
  firstMan.DoSomething();
  firstMan.DisplayOccupation();

  // Usage of Pointer Operator (->)
  Human *secondMan = new Human(24, "Tom", "Engineer");
  std::cout << "Name: " << secondMan->name << std::endl;
  secondMan->DoSomething();
  secondMan->DisplayOccupation();

  // Change occupation
  secondMan->SetOccupation("Data Scientist");
  secondMan->DisplayOccupation();

  // Usage of Double Colon (::)
  Human::DisplayAge(firstMan);

  delete secondMan;

  return 0;
}
