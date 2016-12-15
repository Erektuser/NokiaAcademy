class Person{
public:
    int getAge(){ return age; }
protected:
    int age;
};

class Employee: public Person{
public:
    int getSalary(){ return salary; }
protected:
    int salary;
};

class Manager: public Employee{
public:
    int getBonus(){ return bonus; }
protected:
    int bonus;
};

class Technician: public Employee{
public:
    bool isWillingToWorkNightShift(){
        return canWorkNightShift;
    }
protected:
    bool canWorkNightShift;
};


int main()
{
    Manager manager;
    manager.getAge();
    manager.getBonus();

    Technician technic;
    technic.getAge();
    technic.isWillingToWorkNightShift();

    return 0;

}
