#include "carriage.h"
#include "human.h"




Carriage::Carriage(int _number, int _capacity)
	: m_Capacity(_capacity), m_Number(_number)
{
	validCapacity(_capacity);
	if (_number < 0)
		throw std::logic_error("Incorrect number");
}


int Carriage::getCapacity() const
{
	return m_Capacity;
}


int Carriage::getHumansCount() const
{
	return m_passengers.size();
}

int Carriage::getCarriageNumber() const
{
	return m_Number;
}

Human const * Carriage::findHuman(const std::string & _humanName) const
{
	m_passengers.count( &_humanName );

	return nullptr;
}

bool Carriage::hasHuman( Human const & _passenger ) const
{
	return m_passengers.find( &_passenger.getName() ) != m_passengers.end();
}

bool Carriage::addHuman(Human const & _passenger)
{
	if (m_passengers.size() == m_Capacity)
		return false;

	return m_passengers.insert( std::make_pair( &_passenger.getName(), &_passenger ) ).second;
}


bool Carriage::embarkHuman(Human const & _passenger)
{
	if( m_passengers.count( &_passenger.getName() ) == 0)
		return false;

	m_passengers.erase( &_passenger.getName() );

	return true;
}

bool Carriage::isFull() const
{
	return (getHumansCount() == m_Capacity);
}

int Carriage::emptySeatsCount() const
{
	return m_Capacity - getHumansCount();
}

Carriage::PassengersIterator
Carriage::passengersBegin() const
{
	return m_passengers.cbegin();
}

Carriage::PassengersIterator
Carriage::passengersEnd() const
{
	return m_passengers.cend();
}
