#include "transport.h"

using namespace std;

std::istream& operator>>(std::istream& is, Transport& T)
{
	T.readFrom(is);
	return is;
}

void Transport::printOn() const
{
	cout << "The cost of use: " << getPrice();
}

void Transport::readFrom(std::istream& is)
{
	getline(is, manufacturer, ',');
}

void Car::printOn() const
{
	cout << "Car. Brand: " << manufacturer << " | ";
	Transport::printOn();
}

double Car::getPrice() const
{
	return fuel_ñonsumption*FUEL_PRICE;
}

Transport* Car::clone() const
{
	return new Car(*this);
}

void Car::readFrom(std::istream& is)
{
	Transport::readFrom(is);
	is >> fuel_ñonsumption;
}

std::string Car::getBrand() const
{
	return manufacturer;
}

void Plane::printOn() const
{
	cout << "Plane. Airline: " << manufacturer << " | ";
	Transport::printOn();
}

double Plane::getPrice() const
{
	return ticket_price;
}

Transport* Plane::clone() const
{
	return new Plane(*this);
}

void Plane::readFrom(std::istream& is)
{
	Transport::readFrom(is);
	is >> ticket_price;
}
