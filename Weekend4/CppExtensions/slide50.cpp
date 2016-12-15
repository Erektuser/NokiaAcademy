#include <string>
#include <iostream>

using namespace std;

class Person
 {
 private:
    int age;
    string name;
 public:   
    Person(int p_age, string p_name)
    {
       cout << "Person constructor" << endl;
       age = p_age;
       name = p_name;
    }
    ~Person()
    {
       cout << "Person destructor" << endl;
    }
    void Introduce()
    {
       cout << "Hello, my name is " << name <<
       " and I'm " << age << " years old" << endl;
    }
 };

int main() {
try {
    Person* group[10];
    for(int i=0;i<10;i++)
       group[i] =  new Person(i, "Anonymous");
     for(Person* person : group)
       person->Introduce(); //may throw exception
    for(Person* person : group)
       delete person;
    return 0;
 }
 catch(runtime_error& e) {
    cout << "Error" << e.what() << endl;
 }
}
