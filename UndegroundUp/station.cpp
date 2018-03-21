#include "station.h"
#include "train.h"
#include "human.h"



Station::Station(const std::string & _name, int _capacity)
	:m_Capacity(_capacity), m_Name(_name), m_pLeftTrain(nullptr), m_pRightTrain(nullptr)
{
	validCapacity(_capacity);
}



const std::string & Station::getName() const
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

Train * Station::getTrain(Platforms _platform) const
{
	isArrived(_platform);
	if (_platform==Platforms::Right)
		return m_pRightTrain;
	if (_platform == Platforms::Left)
		return m_pLeftTrain;
	return nullptr;
}

Train * Station::getTrain(int _trainNumber) const
{
	if (getTrainNumber(Platforms::Right) == _trainNumber)
		return m_pRightTrain;
		if (getTrainNumber(Platforms::Left) == _trainNumber)
			return m_pLeftTrain;
			else
				return nullptr;
}

int Station::getTrainNumber(Platforms _platform) const
{
	if (hasArrivedRight() && (_platform == Platforms::Right))
		return m_pRightTrain->getNumber();
	if (hasArrivedLeft() && (_platform == Platforms::Left))
		return m_pLeftTrain->getNumber();
	else return - 1;
}


bool Station::hasTrains() const
{
	return (hasArrivedRight() || hasArrivedLeft());
}

bool Station::hasTrain(int _trainNumber) const
{
	return
		(
			hasArrivedRight()
			&& m_pRightTrain->getNumber() == _trainNumber
			)
		||
		(
			hasArrivedLeft()
			&& m_pLeftTrain->getNumber() == _trainNumber
		);
		
	}

bool Station::hasArrivedRight() const
{
	return m_pRightTrain != nullptr;
}

bool Station::hasArrivedLeft() const
{
	return m_pLeftTrain != nullptr;
}


bool Station::hasHumanInTrain(int _trainNumber) const
{
	return
		(
			(
					(getComeLeft() == _trainNumber)
				&& (m_pLeftTrain->isEmpty())
			)
			|| 
			(
					(getComeRight())
				&& (m_pRightTrain->isEmpty())
			)
		);

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

void Station::arrivedRight(Train *_train)
{
	if (m_pRightTrain)
		throw std::logic_error("Something has arrived in this station");
	m_pRightTrain = _train;
}

void Station::arrivedLeft(Train *_train)
{
	if (m_pLeftTrain)
		throw std::logic_error( "Something has arrived in this station");
	m_pLeftTrain = _train;
}

void Station::departureRight()
{
	if (!m_pRightTrain)
		throw std::logic_error("Train isn't at the platform now");
		m_pRightTrain = nullptr;
}

void Station::departureLeft()
{
	if (!m_pLeftTrain)
		throw std::logic_error("Train isn't at the platform now");;
	m_pLeftTrain = nullptr;
}


int Station::findHuman(const Human & _human) const
{
	int nHuman = getHumansCount();
	for (int i = 0; i < nHuman; i++)
		if (m_humans[i] == (&_human))
			return i;
	return -1;
}

int Station::findHuman(const std::string & _humanName) const
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
	isHumanAtTheStation(*_human);
	m_humans.push_back(_human);
}


int Station::removeHuman(Human &_human)
{
	int _humanPos = findHuman(_human);
	m_humans.erase(m_humans.begin() + _humanPos);
	return _humanPos;
}

bool Station::removeHuman(const std::string & _humanName)
{
	int _humanPos = findHuman(_humanName);
	if (_humanPos != -1)
	{
		m_humans.erase(m_humans.begin() + _humanPos);
		return true;
	}
	else 
		return false;
}


bool Station::findHumanInTrain(const std::string & _humanName, int _platform) const
{
	if
		(
			(
					hasArrivedLeft()
				&& (m_pLeftTrain->findHuman(_humanName) != -1)
			)
			||
			(
					hasArrivedRight()
				&& (m_pRightTrain->findHuman(_humanName) != -1)
			)
		)
		return true;
	else 
		return false;
}

bool Station::findHumanInTrain(const Human & _human, int _platform) const
{
	if
		(
		(
			hasArrivedLeft()
			&& (m_pLeftTrain->findHuman(_human) != -1)
			)
			||
			(
				hasArrivedRight()
				&& (m_pRightTrain->findHuman(_human) != -1)
				)
			)
		return true;
	else
		return false;
}


bool  Station::moveHumanToTrain(const std::string & _humanName, Platforms _platform)
{
	int _humanPos = findHuman(_humanName);
	if (_humanPos == -1)
	{
		return false;
	}
	isArrived(_platform);
	if (_platform == Platforms::Right)
	{
		m_pRightTrain->addHuman(m_humans[_humanPos]);
	}
	else
	{
		m_pLeftTrain->addHuman(m_humans[_humanPos]);
	}
		m_humans.erase(m_humans.begin() + _humanPos);
		return true;
}

bool  Station::moveHumanToTrain(const std::string &_humanName, Platforms _platform, int _carriageNumber)
{
	int _humanPos = findHuman(_humanName);
	if (_humanPos == -1)
	{
		return false;
	}
	isArrived(_platform);
	if (_platform == Platforms::Right)
	{
		m_pRightTrain->addHuman(m_humans[_humanPos], _carriageNumber);
	}
	else
	{
		m_pLeftTrain->addHuman(m_humans[_humanPos], _carriageNumber);
	}
		m_humans.erase(m_humans.begin() + _humanPos);
		return true;

}

bool Station::moveHumanFromTrainToStation(const std::string &_humanName)
{
	isArrived();
	Human * _human;
	if (hasArrivedLeft())
	{
		_human = m_pLeftTrain->getAndRemoveHuman(_humanName);
	}
	else
	{
		_human = m_pRightTrain->getAndRemoveHuman(_humanName);
	}
	if (_human != nullptr)
	{
		addHuman(_human);
		return true;
	}
	else false;
}
			


