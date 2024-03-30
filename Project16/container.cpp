#include "container.h"
using namespace std;

LinkedList::LinkedList(const LinkedList& other)
    : head(nullptr), end(nullptr), size(other.size)
{
    if (other.head == nullptr)
    {
        return;
    }
    head = new Node(other.head->data);
    Node* curr = head;
    Node* otherCurr = other.head->next;
    while (otherCurr != nullptr)
    {
        curr->next = new Node(otherCurr->data);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    end = curr;
}

Travel*& LinkedList::operator[](int index)
{
    if (index < 0 || index > size - 1)
    {
        ostringstream oss;
        oss << "Error: Cannot get element at position #" << index << endl;
        throw out_of_range(oss.str());
    }
    Node* curr = head;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    return curr->data;
}

const Travel* LinkedList::operator[](int index) const
{
    if (index < 0 || index > size - 1)
    {
        ostringstream oss;
        oss << "Error: Cannot get element at position #" << index << endl;
        throw out_of_range(oss.str());
    }
    Node* curr = head;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    return curr->data;
}

unsigned LinkedList::getSize() const
{
    return size;
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this == &other) {
        return *this;
    }
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    if (other.head == nullptr)
    {
        return *this;
    }
    head = new Node(other.head->data);
    Node* curr = head;
    Node* otherCurr = other.head->next;
    while (otherCurr != nullptr)
    {
        curr->next = new Node(otherCurr->data);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    return *this;
}

void LinkedList::addtoEnd(const Travel* val)
{
    ++size;
    if (head == nullptr)
    {
        head = new Node(val);
        end = head;
        return;
    }
    Node* curr = end;
    curr->next = new Node(val);
    end = end->next;
}

void LinkedList::printAll() const
{
    Node* curr = head;
    if (curr == nullptr)
    {
        cout << "List is empty :(\n";
    }
    else
    {
        while (curr != nullptr)
        {

            cout << *curr->data << " ";
            curr = curr->next;
            cout << endl;
        }
    }
}

void LinkedList::insert(Travel* val, int index)
{
    if (index < 0 || index > size - 1)
    {
        ostringstream oss;
        oss << "Error: Cannot insert element at position #" << index << endl;
        throw out_of_range(oss.str());
    }
    Node* newNode = new Node(val);
    Node phantom(nullptr, head);
    Node* curr = &phantom;
    for (int i = 0; i < index; ++i)
    {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
    head = phantom.next;
    end = newNode;
    ++size;
}

Travel& LinkedList::getTravel(int index) const
{
    if (index < 0 || index > size - 1)
    {
        ostringstream oss;
        oss << "Error: Cannot get element at position #" << index << endl;
        throw out_of_range(oss.str());
    }
    Node* curr = head;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    return *curr->data;
}

void LinkedList::remove(int index)
{
    if (index < 0 || index > size - 1)
    {
        ostringstream oss;
        oss << "Error: Cannot remove element at position #" << index << endl;
        throw out_of_range(oss.str());
    }
    Node phantom(nullptr, head);
    Node* curr = &phantom;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    Node* temp = curr->next;
    if (temp == end)
    {
        end = curr;
    }
    curr->next = curr->next->next;
    delete temp;
    head = phantom.next;
    --size;
}

void LinkedList::removeAll()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    end = nullptr;
    size = 0;
}

double LinkedList::totalPrice() const
{
    double res = 0;
    Node* curr = head;
    while (curr != nullptr)
    {
        res += curr->data->getTravelPrice();
        curr = curr->next;
    }
    return res;
}

Travel* LinkedList::findMostExpensive(const type_info& type) const
{
    Node* curr = head;
    Travel* res = nullptr;
    if (type == typeid(CarTravel))
        res = new CarTravel();
    else if (type == typeid(FamilyTravel))
        res = new FamilyTravel();
    else
        throw runtime_error("Invalid type. Expecting type CarTravel/FamilyTravel");

    while (curr != nullptr)
    {
        if (typeid(*curr->data) == type)
        {
            if (curr->data->getTravelPrice() > res->getTravelPrice())
            {
                res = curr->data;
            }
        }
        curr = curr->next;
    }
    return res;
}

LinkedList::~LinkedList()
{
    removeAll();
}

//LinkedList createOneTypeList(const LinkedList& LL, const type_info& type)
//{
//    LinkedList res;
//    LinkedList::Node* curr = LL.head;
//    while (curr != nullptr)
//    {
//        if (typeid(*curr->data) == type)
//        {
//            res.addtoEnd(curr->data);
//        }
//        curr = curr->next;
//    }
//    return res;
//}

void CarTravelsList::createList(const LinkedList& LL)
{
    removeAll();
    for (int i = 0; i < LL.getSize(); ++i)
    {
        if (typeid(*LL[i]) == typeid(CarTravel))
            addtoEnd(LL[i]);
    }
}

void CarTravelsList::printAll() const
{
    LinkedList::printAll();
}

Car CarTravelsList::findMostExpensiveCar() const
{
    if (head == nullptr)
    {
        throw runtime_error("List is empty :(");
    }
    Car res = *static_cast<Car*>(head->data->getVehicle());
    Node* curr = head->next;
    while (curr != nullptr)
    {
        if (res.getPrice() < curr->data->getVehicle()->getPrice())
            res = *static_cast<Car*>(curr->data->getVehicle());
        curr = curr->next;
    }
    return res;
}

void FamilyTravelsList::createList(const LinkedList& LL)
{
    removeAll();
    for (int i = 0; i < LL.getSize(); ++i)
    {
        if (typeid(*LL[i]) == typeid(FamilyTravel))
            addtoEnd(LL[i]);
    }
}

void FamilyTravelsList::printAll() const
{
    LinkedList::printAll();
}

unsigned FamilyTravelsList::findMembersQuantity() const
{
    if (head == nullptr)
    {
        throw runtime_error("List is empty :(");
    }
    FamilyTravel temp = *static_cast<FamilyTravel*>(head->data);
    Node* curr = head->next;
    while (curr != nullptr)
    {
        if (temp.getTravelPrice() > curr->data->getTravelPrice())
            temp = *static_cast<FamilyTravel*>(curr->data);
        curr = curr->next;
    }
    unsigned res = (temp.getTravelPrice() - FamilyTravel::FAMILY_TRAVEL_COST) / temp.getVehicle()->getPrice() ;
    return res;
}
