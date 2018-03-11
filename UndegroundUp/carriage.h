#pragma once
#include <vector> 
#include <string>

class Human;

class Carriage
{
public:

	Carriage(int _number, int _capacity=10);
	Carriage(const Carriage &) = delete;
	Carriage & operator = (Carriage & _temp) = delete;
	~Carriage() {}

	int getCapacity() const;
	int getHumansCount() const;
	int getCarriageNumber();
	Human * getHuman(const std::string &_humanName) const;
	Human * getHuman(int _humanPos) const;

	int addHuman(Human &_passenger);
	Human * getAndRemoveHuman (int _humanPos);
	int findHuman(Human & _human) const;
	int findHuman(std::string _humanName) const;
	
	bool Follness() const;
	int  nEmptySeats() const;


private:
	int m_Capacity;
	std::vector <Human *> m_passengers;
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
