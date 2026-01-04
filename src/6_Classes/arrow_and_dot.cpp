/*
 * Task: Demonstrate member access with dot and arrow operators in C++.
 *
 * Arrow and Dot Showcase
 *
 * Demonstrate how to access class members using both the dot (.) and arrow (->)
 * operators in C++. A class "Human" is defined with private and public members.
 * We create an object (accessed via the dot operator) and a pointer to an
 * object (accessed via the arrow operator). The program also uses the scope
 * resolution operator (::) to call a static member function.
 *
 * ASCII Illustration:
 *
 *       +--------------+
 *       |    Human     |
 *       +--------------+
 *       | - age        |
 *       | - occupation |
 *       | + name       |
 *       +--------------+
 *             |
 *   +---------+---------+
 *   |                   |
 * Object             Pointer
 * (dot operator)     (arrow operator)
 *
 * Example Output:
 * Name: Jim
 * Jim of age 13 is doing something.
 * Jim works as a Student.
 * Name: Tom
 * Tom of age 24 is doing something.
 * Tom works as a Engineer.
 * Tom works as a Data Scientist.
 * Jim is 13 years old.
 */

#include <iostream>
#include <string>

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const std::string &got, const std::string &expected,
                   const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=\"" << expected << "\" got=\""
              << got << "\"\n";
  }

  void expectEqual(int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

class Human {
private:
  int age;
  std::string occupation;

public:
  std::string name;

  Human(int humanAge, const std::string &humanName,
        const std::string &humanOccupation)
      : age(humanAge), name(humanName), occupation(humanOccupation) {}

  void DoSomething() const {
    std::cout << name << " of age " << age << " is doing something.\n";
  }

  void SetOccupation(const std::string &newOccupation) {
    occupation = newOccupation;
  }

  void DisplayOccupation() const {
    std::cout << name << " works as a " << occupation << ".\n";
  }

  int GetAge() const { return age; }
  const std::string &GetOccupation() const { return occupation; }

  static void DisplayAge(const Human &person) {
    std::cout << person.name << " is " << person.age << " years old.\n";
  }
};

int main() {
  TestRunner runner;
  // Using the dot operator on an object
  Human firstMan(13, "Jim", "Student");
  std::cout << "Name: " << firstMan.name << "\n";
  firstMan.DoSomething();
  firstMan.DisplayOccupation();
  runner.expectEqual(firstMan.name, "Jim", "dot operator name");
  runner.expectEqual(firstMan.GetAge(), 13, "dot operator age");
  runner.expectEqual(firstMan.GetOccupation(), "Student",
                     "dot operator occupation");

  // Using the arrow operator on a pointer to an object
  Human *secondMan = new Human(24, "Tom", "Engineer");
  std::cout << "Name: " << secondMan->name << "\n";
  secondMan->DoSomething();
  secondMan->DisplayOccupation();

  // Changing occupation using the pointer
  secondMan->SetOccupation("Data Scientist");
  secondMan->DisplayOccupation();
  runner.expectEqual(secondMan->name, "Tom", "arrow operator name");
  runner.expectEqual(secondMan->GetAge(), 24, "arrow operator age");
  runner.expectEqual(secondMan->GetOccupation(), "Data Scientist",
                     "arrow operator occupation");

  // Using the scope resolution operator to call a static member function
  Human::DisplayAge(firstMan);

  delete secondMan;
  runner.summary();
  return 0;
}
