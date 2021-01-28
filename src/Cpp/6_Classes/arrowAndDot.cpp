#include <iostream>
#include <string>

using namespace std;

class Human {
private:
    int age;

public:
    string name;

    Human(int humanAge, string humanName) 
         : age(humanAge), name(std::move(humanName)) {}

    void DoSomething() {
        cout << age << endl;
    }

    static void DisplayAge(const Human& person) {
        cout << person.age << endl;
    }

    // ...
};

int main() {
    // Usage of Dot(.) 
    Human firstMan(13, "Jim"); // firstMan is an instance of class Human
    cout << firstMan.name << endl; // accessing member attributes
    firstMan.DoSomething(); // accessing member functions

    // Usage of Pointer Operator (->)
    Human* secondMan = new Human(24, "Tom");
    cout << secondMan->name << endl; // accessing member attributes
    secondMan->DoSomething(); // accessing member functions
    cout << (*secondMan).name << endl; // accessing member attributes
    (*secondMan).DoSomething(); // accessing member functions

    // Usage of Double Colon (::)
    //Human::DisplayAge(firstMan);
    firstMan.DisplayAge(firstMan); // ok but not recommended
    secondMan->DisplayAge(firstMan); // ok but not recommended

    delete(secondMan);

    return 0;
}
