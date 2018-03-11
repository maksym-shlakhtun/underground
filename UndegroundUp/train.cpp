#include "train.h"
#include "human.h"
#include "carriage.h"


Train::Train(int _number)
	:m_maxCarriages(5), m_Number(_number)
{
	incorrectNumber(_number);
}

Train::Train(int _number, int _maxCarriages)
	: m_maxCarriages(_maxCarriages), m_Number(_number)
{
	incorrectNumber(_number);
	incorrectMaxCarriages(_maxCarriages);
}


int Train::getNumber() const
{
	return m_Number;
}

int Train::getNCarriages() const
{
	return m_Carriages.size();
}

int Train::getHumansCount() const
{
	int i = 0;
	for (Carriage* _pCarriage : m_Carriages)
	{
		i =i+ _pCarriage->getHumansCount();
	}
	return i;
}

Carriage * Train::getCarriage(int _pos) const
{
	return m_Carriages.at(_pos);
}


int Train::findCarriage(Carriage &_carriage) const
{

	int _nCarriage = getNCarriages();
	for (int i = 0; i < _nCarriage; i++)
		if (m_Carriages[i]->getCarriageNumber() == (_carriage.getCarriageNumber()))
			return i;
	return -1;
}

int Train::findCarriage(int _carriage) const
{

	int _nCarriage = getNCarriages();
	for (int i = 0; i < _nCarriage; i++)
		if (m_Carriages[i]->getCarriageNumber() == _carriage)
			return i;
	return -1;
}

void Train::addCarriage(Carriage *_carriage) 
{
	if (getNCarriages() + 1 > m_maxCarriages)
		throw "The train is full";
	if (findCarriage(*_carriage) != -1)
		throw "The carriage already attached to the train";
		m_Carriages.push_back(_carriage);
}

void Train::removeCarriage(int _number)
{
	hasCarriages();
	int _pos = findCarriage(_number);
	if (findCarriage(_number) == -1)
		throw "The cariage dont attached to the train";
	if (m_Carriages[_pos]->getHumansCount() != 0)
		throw "There are people in the carriage";
	m_Carriages.erase(m_Carriages.begin() + _pos);
}

void  Train::hasCarriages() const
{
	if (getNCarriages() == 0)
		throw "Carriages are not connected to the train";
}

bool Train::isTrainFullness()  const
{
	if (getNCarriages() != m_maxCarriages)
		return true;
	return false;
}

bool Train::hasEmptySeats()
{
	for (Carriage *_pCarriage : m_Carriages)
		if (_pCarriage->nEmptySeats() > 0)
			return true;
	return false;
}


bool Train::isEmpty() const
{
	if (getHumansCount() == 0)
		return true;
	else return false;
}

int Train::findHuman(Human &_human) const
{
	for (int i = 0; i < getNCarriages(); i++)
		if (m_Carriages[i]->findHuman(_human) != -1)
			return i;
	return -1;
}

int Train::findHuman(std::string  _humanName) const
{
	for (int i = 0; i < getNCarriages(); i++)
		if (m_Carriages[i]->findHuman(_humanName) != -1)
			return i;
	return -1;
}

void Train::addHuman(Human &_human)
{
	hasCarriages();
	if (findHuman(_human) != -1)
		throw "Human is at tne train now";
	if (!hasEmptySeats())
		throw"The train is full";
		for (int i = 0; i < getNCarriages(); i++)
			if (m_Carriages[i]->addHuman(_human) == 1)
				break;
	}

void Train::addHuman(Human &_human, int _carriage) 
{	
	hasCarriages();
	NonexistentCarriageNumber(_carriage);
		if (findHuman(_human) != -1)
		throw "Human is at tne train now";

	if (m_Carriages[_carriage - 1]->addHuman(_human)==-1)
		throw "The carriage is full";
}

Human * Train::getAndRemoveHuman(std::string _humanName)
{
	/*int i = findHuman(_humanName);
	if (i == -1)
		throw "Human is not on this train";*/
	
	int _humanPos = 0;
	for (int i = 0; i < getNCarriages(); i++)
	{
		_humanPos = m_Carriages[i]->findHuman(_humanName);
		if (_humanPos != -1)
		return	m_Carriages[i]->getAndRemoveHuman(_humanPos);
	}
	return nullptr;

}

Human * Train::getHuman(std::string _humanName) const
{
	int _humanPos= 0;
	for (int i = 0; i < getNCarriages() - 1; i++)
	{
		_humanPos = m_Carriages[i]->findHuman(_humanName);
		if (_humanPos != -1)
			m_Carriages[i]->getHuman(_humanPos);
	}
		return nullptr;
}




