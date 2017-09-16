#include "station.h"
#include "train.h"
#include "human.h"



Station::Station(std::string _Name)
	:m_Capacity(10), m_Name(_Name), m_pLeftTrain(nullptr), m_pRightTrain(nullptr)
{}

Station::Station(std::string _Name, int _Capacity)
	:m_Capacity(_Capacity), m_Name(_Name), m_pLeftTrain(nullptr), m_pRightTrain(nullptr)
{
	validCapacity(_Capacity);
}


std::string Station::getName() const
{
	return m_Name;
}

int Station::getCapacity() const
{
	return m_Capacity;
}

int Station::getHumansCount() const
{
	return m_humans.size();
}

//Human & Station::getHuman() const
//{
//
//}

Train * Station::getTrain(int _platform) const
{
	isArrived(_platform);
	if (_platform==1)
		return m_pRightTrain;
	if (_platform == 2)
		return m_pLeftTrain;
	return nullptr;
}


bool Station::hasTrains() const
{
	if (!hasArrivedRight() && !hasArrivedLeft())
		return false;	
	return true;
}

bool Station::hasTrain(int _trainNumber) const
{
	if ((hasArrivedRight() && m_pRightTrain->getNumber()==_trainNumber)||(hasArrivedLeft() && m_pLeftTrain->getNumber() == _trainNumber))
		return true;
	return false;
}

bool Station::hasArrivedRight() const
{
	return m_pRightTrain != nullptr;
}

bool Station::hasArrivedLeft() const
{
	return m_pLeftTrain != nullptr;
}

int Station::getComeRight() const
{
	if (!hasArrivedRight())
		return -1;
	return m_pRightTrain->getNumber();
}

int Station::getComeLeft() const
{
	if (!hasArrivedLeft())
		return -1;
	return m_pLeftTrain->getNumber();
}

void Station::arrivedRight(Train &_train)
{
	if (m_pRightTrain)
		throw "Something has arrived in this station";
	m_pRightTrain = &_train;
}

void Station::arrivedLeft(Train &_train)
{
	if (m_pLeftTrain)
		throw "Something has arrived in this station";
	m_pLeftTrain = &_train;
}

void Station::departureRight()
{
	if (!m_pRightTrain)
		throw "No train is currently arrived";
		m_pRightTrain = nullptr;
}

void Station::departureLeft()
{
	if (!m_pLeftTrain)
		throw "No train is currently arrived";
	m_pLeftTrain = nullptr;
}


int Station::findHuman(Human & _human) const
{
	int nHuman = getHumansCount();
	for (int i = 0; i < nHuman; i++)
		if (m_humans[i] == (&_human))
			return i;
	return -1;
}

int Station::findHuman(std::string _humanName) const
{
	int nHuman = getHumansCount();
	for (int i = 0; i < nHuman; i++)
		if (m_humans[i]->getName() == _humanName)
			return i;
	return -1;
}



void Station::addHuman(Human * _human)
{
	isFullnes();
	isHumanAtTheStation( *_human);
	m_humans.push_back(_human);
}

//void Station::addHuman(std::string _humanName)
//{
//	isFullnes();
//	int _humanPos=findHuman(_humanName);
//	isHumanAtTheStation(_humanPos);
//	m_humans.push_back();
//}


int Station::removeHuman(Human &_human)
{
	int _humanPos = findHuman(_human);
//	isHumanNotAtTheStation(_humanPos);
	m_humans.erase(m_humans.begin() + _humanPos);
	return _humanPos;
}

int Station::removeHuman(std::string _humanName)
{
	int _humanPos = findHuman(_humanName);
//	isHumanNotAtTheStation(_humanPos);
	if (_humanPos!=-1)
	m_humans.erase(m_humans.begin() + _humanPos);
	return _humanPos;
}


int Station::findHumanInTrain(std::string _humanName, int _platform) const
{
	if ((hasArrivedLeft() && (m_pLeftTrain->findHuman(_humanName) != -1)) || (hasArrivedRight() && (m_pRightTrain->findHuman(_humanName) != -1)))
		return 1;
	else return -1;
}

int  Station::moveHumanToTrain(std::string _humanName, std::string _direction)
{
	int _humanPos = findHuman(_humanName);
	if (_humanPos == -1)
	{
		return -1;
	}
	//isHumanNotAtTheStation(_humanPos);
	int _platform = invalidDirection(_direction);
	isArrived(_platform);
	if (_platform == 1)
		m_pRightTrain->addHuman(*m_humans[_humanPos]);
	if (_platform == 2)
		m_pLeftTrain->addHuman(*m_humans[_humanPos]);
	m_humans.erase(m_humans.begin() + _humanPos);
	return 1;
}

int  Station::moveHumanToTrain(std::string _humanName, std::string _direction, int _carriageNumber)
{
	int _humanPos = findHuman(_humanName);
	//isHumanNotAtTheStation(_humanPos);
	if (_humanPos == -1)
	{
		return -1;
	}
	int _platform = invalidDirection(_direction);
	isArrived(_platform);
	if (_platform == 1)
		m_pRightTrain->addHuman(*m_humans[_humanPos], _carriageNumber);
	if (_platform == 2)
		m_pLeftTrain->addHuman(*m_humans[_humanPos], _carriageNumber);
	m_humans.erase(m_humans.begin() + _humanPos);
	return 1;
}


int Station::moveHumanFromTrainToStation(std::string _humanName)
{
	
	isArrived();
	Human * _human;
	if (hasArrivedLeft())
	{
		_human = m_pLeftTrain->getAndRemoveHuman(_humanName);
		if (_human != nullptr)
		{
			addHuman(_human);
			return 1;
		}
	
	}
	if (hasArrivedRight())
	{
		_human = m_pRightTrain->getAndRemoveHuman(_humanName);
		if (_human != nullptr)
		{
			addHuman(_human);
			return 1;
		}
		return -1;}

	throw "Human is not on Trains";
}
