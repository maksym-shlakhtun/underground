#include "carriage.h"
#include "human.h"




Carriage::Carriage(int _number)
	:m_Capacity(50), m_Number(_number)
{
	if (_number < 0)
		throw "Incorrect number";
}

Carriage::Carriage( int _number, int _capacity)
	: m_Capacity(_capacity), m_Number(_number)
{
	validCapacity(_capacity);
	if (_number < 0)
		throw "Incorrect number";
}


int Carriage::getCapacity() const
{
	return m_Capacity;
}

void Carriage::setCapacity(int _capacity)    //?
{
	validCapacity(_capacity);
	m_Capacity = _capacity;
}

int Carriage::getHumansCount() const
{
	return m_passengers.size();
}

int Carriage::getNumber()
{
	return m_Number;
}

Human * Carriage::getHuman(std::string _humanName) const
{
	int _humanPos = findHuman(_humanName);
	if (_humanPos == -1)
		return nullptr;
	return m_passengers[_humanPos];
}

Human * Carriage::getHuman(int _humanPos) const
{
	return m_passengers.at(_humanPos);
}


int Carriage::addHuman(Human & _passenger)
{
	if (m_passengers.size() == m_Capacity)
		return -1;

/*	else
		if (findHuman( _passenger) != -1)
			throw "Human is alredy in the carriage";*/

		m_passengers.push_back(&_passenger);
		return 1;
	
}


int Carriage::findHuman(Human & _human) const
{
	int nHuman = getHumansCount();
	for (int i = 0; i < nHuman; i++)
		if (m_passengers[i] == (&_human))
			return i;
	return -1;
}

int Carriage::findHuman(std::string _humanName) const
{
	int nHuman = getHumansCount();
	for (int i = 0; i < nHuman; i++)
		if (m_passengers[i]->getName()== _humanName)
			return i;
	return -1;
}

Human * Carriage::getAndRemoveHuman(int _humanPos)
{
	Human * _human = getHuman(_humanPos);
	m_passengers.erase(m_passengers.begin() + _humanPos);
	return _human;
}

int Carriage::Follness() const
{
	if (getHumansCount() + 1 >= m_Capacity)
		return -1;
	else return 1;
}

int  Carriage::nEmptySeats() const
{
	return m_Capacity - getHumansCount();
}
