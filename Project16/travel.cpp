#include "travel.h"
#include <iomanip>
using namespace std;
Travel* Travel::Make_Instance(std::ifstream& fin)
{
	string className;
	fin >> className;
	if (className == "CarTravel")
	{
		Travel* CT = new CarTravel();
		fin >> *CT;
		return CT;
	}
	else if (className == "FamilyTravel")
	{
		Travel* FT = new FamilyTravel();
		fin >> *FT;
		return FT;
	}
	else
	{
		throw runtime_error(className);
	}
}
Travel::Travel(const Travel& T) : travel_place(T.travel_place)
{
	vehicle = T.getVehicle()->clone();
}

Transport* Travel::getVehicle() const
{
	return vehicle;
}

void Travel::readFrom(std::istream& is)
{
	is >> *vehicle >> travel_place;
}

std::istream& operator>>(std::istream& is, Travel& T)
{
	T.readFrom(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Travel& T)
{
	T.printOn();
	return os;
}

const double CarTravel::MIN_DISTANCE = 20.;
Travel* CarTravel::clone() const
{
	return new CarTravel(*this);
}

void CarTravel::printOn() const 
{
	cout << left << setw(25) << "Travel to " + travel_place;
	cout << setw(20) << "| Car: " + static_cast<Car*>(getVehicle())->getBrand();
	cout << "| Total price: " << getTravelPrice();
}
double CarTravel::getTravelPrice() const
{
	return vehicle->getPrice() * total_distance / 100;
}

double CarTravel::getDistance() const
{
	return total_distance;
}

void CarTravel::readFrom(std::istream& is)
{
	Travel::readFrom(is);
	is >> total_distance;
}

CarTravel& CarTravel::operator=(const CarTravel& CT)
{
	if (this != &CT)
	{
		total_distance = CT.total_distance;
		delete vehicle;
		vehicle = CT.getVehicle()->clone();
	}
	return *this;
}

Travel* FamilyTravel::clone() const
{
	return new FamilyTravel(*this);
}

void FamilyTravel::printOn() const
{
	cout << left << setw(25) << "Family travel to " + travel_place;
	cout << '|' << setw(19) << ' ' << "| Total price: " << getTravelPrice();
}
double FamilyTravel::getTravelPrice() const
{
	return members_quantity * getVehicle()->getPrice() + FAMILY_TRAVEL_COST;
}

void FamilyTravel::readFrom(std::istream& is)
{
	Travel::readFrom(is);
	is >> members_quantity;
}

FamilyTravel& FamilyTravel::operator=(const FamilyTravel& FT)
{
	if (this != &FT)
	{
		members_quantity = FT.members_quantity;
		delete vehicle;
		vehicle = FT.getVehicle()->clone();
	}
	return *this;
}
