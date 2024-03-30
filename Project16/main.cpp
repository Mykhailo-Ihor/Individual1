#include "container.h"
#include <iomanip>
using namespace std;

int main()
{
	LinkedList travels;
	ifstream fin("Travels.txt");
    for(int i = 0; !fin.eof(); ++i)
    {
        try
        {
            travels.addtoEnd(Travel::Make_Instance(fin));
        }
        catch (const runtime_error& rt)
        {
            std::cout << "!!! ERROR: Bad class name '" << rt.what() << "' encountered at step #" << i + 1 << '\n';
            while (fin.get() != '\n') continue;
        }
    }
    travels.printAll();
    cout << left << setw(28) << "Total price of all travels" << ':' << travels.totalPrice() << endl;
    cout << left << setw(28) << "Most expensive car travel" << ':' << * travels.findMostExpensive(typeid(CarTravel)) << endl;
    cout << left << setw(28) << "Most expensive family travel" << ':' << *travels.findMostExpensive(typeid(FamilyTravel)) << endl;
    //Початковий варіант з викристанням дружньої функції
    //LinkedList carTravels = createOneTypeList(travels, typeid(CarTravel));
    //carTravels.printAll();
    //LinkedList familyTravels = createOneTypeList(travels, typeid(FamilyTravel));
    //familyTravels.printAll();
    CarTravelsList carTravels;
    carTravels.createList(travels);
    cout << "\nCar Travels:\n";
    carTravels.printAll();
    FamilyTravelsList familyTravels(travels);
    cout << "Family Travels:\n";
    familyTravels.printAll();
    Car MostEx = carTravels.findMostExpensiveCar();
    cout << "Most expensive "; MostEx.printOn();
    unsigned memq = familyTravels.findMembersQuantity();
    cout << "\nMembers quantity in cheapest travel: " << memq << endl;
    //Приклад винятку 
    FamilyTravelsList example;
    try
    {
        memq = example.findMembersQuantity();
    }
    catch (const runtime_error& ex)
    {
        cout << ex.what() << endl;
    }
	return 0;
}