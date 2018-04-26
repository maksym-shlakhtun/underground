#pragma once

#include <unordered_map> 
#include <string>

class Human;

class Carriage
{

private:

	class PointerToStringComparator
	{
	public:

		bool operator () (std::string const * _lhs, std::string const * _rhs) const
		{
			return *_lhs == *_rhs;
		}
	};

	typedef
		std::unordered_map<
				std::string const *
			,	Human const *
			,	std::hash< std::string const * >
			,	PointerToStringComparator
		>
		HumanContainer;

public:

	typedef HumanContainer::const_iterator PassengersIterator;

	Carriage(int _number, int _capacity = 10 );

	Carriage(const Carriage &) = delete;
	Carriage & operator = (const Carriage & _temp) = delete;
	~Carriage() {}

	int getCapacity() const;
	int getHumansCount() const;
	int getCarriageNumber() const;

	bool addHuman(Human const & _passenger);
	bool embarkHuman(Human const & _passenger);

	Human const * findHuman(const std::string &_humanName) const;
	bool hasHuman ( Human const & _human) const;

	PassengersIterator passengersBegin () const;
	PassengersIterator passengersEnd () const;

	bool isFull() const;
	int emptySeatsCount() const;

private:
	int m_Capacity;
	HumanContainer m_passengers;
	int m_Number;
	
	void validCapacity(int _temp) const;
	void isHumanInCarriage(int _humanPos) const;
};

inline void Carriage::validCapacity(int _temp) const
{
	if (m_Capacity <= 0 || m_Capacity > 100)
		throw std::logic_error("Incorrect capacity");
}

inline void Carriage::isHumanInCarriage(int _humanPos) const
{
	if (_humanPos == -1)
		throw std::logic_error("There are no human at the carriage");
}
