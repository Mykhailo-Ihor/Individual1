#pragma once
#include "travel.h"
#include <sstream>
class LinkedList 
{
public:
    struct Node
    {
        Travel* data;
        Node* next;
        Node(const Travel* val, Node* p = nullptr) : next(p)
        {
            if (val != nullptr)
                 data = val->clone();
            else data = nullptr;
        }
        ~Node()
        {
            delete data;
        }
    };
protected:
    Node* head;
    Node* end;
    unsigned size;
public:
    LinkedList() : head(), end(), size(0) {}

    LinkedList(Travel* val, Node* next = nullptr) : size(1) { head = new Node(val, next); end = head; }

    LinkedList(const LinkedList& other);

    Travel*& operator[] (int index);

    const Travel* operator[] (int index) const;

    unsigned getSize() const;

    LinkedList& operator=(const LinkedList& other);

    void addtoEnd(const Travel* val);

    void printAll() const;

    void insert(Travel* val, int index);

    Travel& getTravel(int index) const;
   
    void remove(int index);

    void removeAll(); 

    double totalPrice() const;

    Travel* findMostExpensive(const type_info& type) const;
    
    ~LinkedList();

    //Початковий варіант створення двох окремих контейнерів
    //friend LinkedList createOneTypeList(const LinkedList& LL, const type_info& type); 
};

class CarTravelsList : private LinkedList
{
public:
    CarTravelsList() = default;
    CarTravelsList(const LinkedList& LL) { createList(LL); }
    void createList(const LinkedList& LL);
    void printAll() const;
    Car findMostExpensiveCar() const;
};

class FamilyTravelsList :private LinkedList
{
public:
    FamilyTravelsList() = default;
    FamilyTravelsList(const LinkedList& LL) { createList(LL); }
    void createList(const LinkedList& LL);
    void printAll() const;
    unsigned findMembersQuantity() const;
};