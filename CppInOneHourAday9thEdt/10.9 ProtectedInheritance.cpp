#include <iostream>
using namespace std;

class Motor
{
public:
   void SwitchIgnition()
   {
      cout << "Ignition ON" << endl;
   }
   void PumpFuel()
   {
      cout << "Fuel in cylinders" << endl;
   }
   void FireCylinders()
   {
      cout << "Vroooom" << endl;
   }
};

class Car :protected Motor
{
public:
   void Move()
   {
      SwitchIgnition();
      PumpFuel();
      FireCylinders();
   }
};

class RaceCar :protected Car
{
public:
   void Move()
   {
      SwitchIgnition();  // RaceCar has access to members of
      PumpFuel();  // base Motor due to "protected" inheritance
      FireCylinders(); // between RaceCar & Car, Car & Motor
      FireCylinders();
      FireCylinders();
   }
};

int main()
{
   RaceCar myDreamCar;
   myDreamCar.Move();

   return 0;
}