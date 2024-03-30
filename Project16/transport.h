#pragma once
#include <iostream>
#include <string>
class Transport 
{
protected:
	std::string manufacturer;
public:
	Transport() = default;
	Transport(std::string m) : manufacturer(m) {}
	Transport(const Transport& T) : manufacturer(T.manufacturer) {}
	virtual ~Transport() = default;
	virtual void printOn() const;
	virtual double getPrice() const abstract;
	virtual Transport* clone() const abstract;
	virtual void readFrom(std::istream& is);
};

std::istream& operator>>(std::istream& in, Transport& T);

class Car : public Transport 
{
private:
	double fuel_ñonsumption;
public:
	static const int FUEL_PRICE = 55;
	Car() : Transport(), fuel_ñonsumption(0) {}
	Car(std::string brand, double fuel_c) : Transport(brand), fuel_ñonsumption(fuel_c) {}
	Car(const Car& C) : Transport(C), fuel_ñonsumption(C.fuel_ñonsumption) {};
	virtual ~Car() = default;
	virtual void printOn() const override;
	virtual double getPrice() const override;
	virtual Transport* clone() const override;
	virtual void readFrom(std::istream& is) override;
	virtual std::string getBrand() const;
};

class Plane : public Transport {
private:
	double ticket_price;
public:
	Plane() : Transport(), ticket_price(0) {}
	Plane(std::string company, double price) : Transport(company), ticket_price(price) {}
	Plane(const Plane& P) : Transport(P), ticket_price(P.ticket_price) {}
	virtual ~Plane() = default;
	virtual void printOn() const override;
	virtual double getPrice() const override;
	virtual Transport* clone() const override;
	virtual void readFrom(std::istream& is) override;
};