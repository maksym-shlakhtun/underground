#pragma once
#include "carriage.h"
#include <vector>

class Human;

class Train
{
public:
	Train(int _number);
	Train(int _number, int _maxCarriages);
	Train(const Train & _temp) = delete;
	Train & operator =(Train & _temp) = delete;
	~Train() {};

	int getNumber() const;
	int getNCarriages() const;
	int getHumansCount()const;
	Carriage *getCarriage(int _pos) const;

	int findCarriage(Carriage &_carriage) const;
	int findCarriage(int _number) const;
	void addCarriage(Carriage *_carriage);
	void addCarriage(int _number);
	void removeCarriage(int _number);
	void hasCarriages() const;
	bool isTrainFullness() const;
	bool  hasEmptySeats();
	
	bool isEmpty() const;
	int findHuman(Human &_human) const;
	int findHuman(std::string  _humanName) const;
	void addHuman(Human &_human);
	void addHuman(Human &_human, int  _carriage);
	Human * getAndRemoveHuman(std::string _humanName);
	//int getAddedpassengers() const;
	Human * getHuman(std::string _humanName) const;

	

private:
	
//	int m_trainCapacity;   
	std::vector <Carriage *> m_Carriages;
	int m_maxCarriages;
	int m_Number;

	void incorrectNumber(int _number) const;
	void incorrectMaxCarriages(int _maxCarriages)const;
	inline void NonexistentCarriageNumber(int _number) const;
};

inline void Train::incorrectNumber(int _number) const
{
	if (_number < 0)
		throw "Incorrect number ";
}

inline void Train::incorrectMaxCarriages(int _maxCarriages) const
{
	if (_maxCarriages <= 0 || _maxCarriages > 5)
		throw "Incorrect number of carriages";
}
inline void Train::NonexistentCarriageNumber(int _number) const
{
	if (_number <= 0 || _number > getNCarriages())
		throw "Incorrect nubmer of carriage";
}