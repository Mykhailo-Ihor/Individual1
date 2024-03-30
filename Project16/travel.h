#pragma once
#include "transport.h"
#include <fstream>
class Travel
{
protected:
	Transport* vehicle;
	std::string travel_place;
public:
	static Travel* Make_Instance(std::ifstream& fin);
	Travel() = default;
	Travel(Transport* T, std::string place) : vehicle(T), travel_place(place) {}
	Travel(const Travel& T);
	~Travel() { delete vehicle; }
	virtual Travel* clone() const abstract;
	virtual double getTravelPrice() const abstract;
	virtual void printOn() const abstract;
	Transport* getVehicle() const;
	virtual void readFrom(std::istream& is);
};

std::istream& operator >> (std::istream& is, Travel& T);
std::ostream& operator << (std::ostream& os, const Travel& T);

class CarTravel : public Travel
{
private:
	double total_distance;
public:
	static const double MIN_DISTANCE;
	CarTravel() : Travel(new Car, ""),total_distance(MIN_DISTANCE) {};
	CarTravel(Transport* T, std::string place, double distance) : Travel(T, place) { total_distance = (distance > 1) ? distance : MIN_DISTANCE; }
	CarTravel(const CarTravel& CT) : Travel(CT),total_distance(CT.total_distance) {};
	~CarTravel() = default;
	virtual Travel* clone() const;
	virtual void printOn() const override;
	virtual double getTravelPrice() const override;
	double getDistance() const;
	virtual void readFrom(std::istream& is) override;
	CarTravel& operator = (const CarTravel& CT);
};

class FamilyTravel : public Travel
{
private:
	unsigned members_quantity;
public:
	static const unsigned MIN_MQUANTITY = 3;
	static const unsigned FAMILY_TRAVEL_COST = 1000;
	FamilyTravel() : Travel(new Plane, ""), members_quantity(MIN_MQUANTITY) {}
	FamilyTravel(Transport* T, std::string place, unsigned q) : Travel(T, place) { members_quantity = (q >= 3) ? q : MIN_MQUANTITY; }
	FamilyTravel(const FamilyTravel& FT) : Travel(FT), members_quantity(FT.members_quantity) {};
	~FamilyTravel() = default;
	virtual Travel* clone() const;
	virtual void printOn() const override;
	virtual double getTravelPrice() const override;
	virtual void readFrom(std::istream& is) override;
	FamilyTravel& operator = (const FamilyTravel& FT);
};