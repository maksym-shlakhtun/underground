#include <iostream>
#include <vector>
#include "train.h"
#include"depot.h"
#include <algorithm>


Depot::Depot(int _depotNumber, int _trainsCapacity, int _carriagesCapacity)
:m_number(_depotNumber), m_trainsCapacity(_trainsCapacity), m_carriagesCapacity(_carriagesCapacity){
	incorrectCapacity(m_carriagesCapacity);
	incorrectCapacity(m_trainsCapacity);
	incorrectNumber(_depotNumber);
}

Depot::~Depot()
{
	for (Train *_pTrain : m_Trains)
	{
		delete _pTrain;
	}
	for (Carriage *_pCarriage : m_Carriages)
	{
		delete _pCarriage;
	}
}


int Depot::getNumber() 
{
	return m_number;
}

int Depot::getTrainsCapacity() const
{
	return m_trainsCapacity;
}

int Depot::getCarriagesCapacity()const
{
	return m_carriagesCapacity;
}

int Depot::getTrainsCount() const
{
	return m_Trains.size();
}
int Depot::getCarriagesCount() const
{
	return m_Carriages.size();
}


void Depot::isTrainsFullness() const
{
	if (getTrainsCount() + 1 > getTrainsCapacity())
		throw std::logic_error("Depo is already full");
}


bool Depot::hasTrain(int _trainPos) const
{
	if (_trainPos != -1)
		return true;
	return false;
}

int  Depot::findTrain(Train &_train) const
{
	for (int i = 0; i < getTrainsCount(); i++)
		if (m_Trains[i]->getNumber() == _train.getNumber())
			return i;
	return -1;
}

int  Depot::findTrain(int _trainNumber) const
{
	for (int i = 0; i < getTrainsCount(); i++)
		if (m_Trains[i]->getNumber() == _trainNumber)
			return i;
	return -1;
}

void Depot::addTrain(Train * _pTrain)
{
	/*int _trainPos = findTrain(_trainNumber);
	isTrainNotExist( _trainPos);*/
	isTrainsFullness();
	
	m_Trains.push_back(_pTrain);
}

void Depot::addTrain(int _trainNumber)
{
	/*int _trainPos = findTrain(_trainNumber);
	isTrainNotExist( _trainPos);*/
	isTrainsFullness();
	Train * _pTrain = new Train(_trainNumber);
	m_Trains.push_back(_pTrain);
}

void Depot::addTrain(int _trainNumber, int _maxCarriages)
{
	/*int _trainPos = findTrain(_trainNumber);
	isTrainNotExist(_trainPos);*/
	isTrainsFullness();
	Train * _pTrain = new Train(_trainNumber, _maxCarriages);
	m_Trains.push_back(_pTrain);
}

void Depot::removeTrain(Train &_train)
{
	int _pos = findTrain(_train);
	isTrainExist(_pos);
	m_Trains.erase(m_Trains.begin() + _pos);
	delete m_Trains[_pos];
}

void Depot::removeTrain(int _trainPos)
{
	//delete m_Trains[_trainPos];
	m_Trains.erase(m_Trains.begin() + _trainPos);
}


Train * Depot::getTrain(int _pos) const
{
	
	isTrainExist( _pos);

	return m_Trains.at(_pos);
}

int Depot::getNCarriages(int _trainNumber) 
{
	int _pos = findTrain(_trainNumber);
	isTrainExist(_pos);
	return m_Trains[_pos]->getNCarriages();
}


void Depot::isCarriagesFullness() const
{
	if (getCarriagesCount() + 1 > getCarriagesCapacity())
		throw std::logic_error("Depo is already full");
}

bool Depot::hasCarriage(int _carriageNumber) const
{
	return findCarriage(_carriageNumber) != -1;
}

int Depot::findCarriage(int _carriageNumber)const
{
	for (int i = 0; i < getCarriagesCount(); i++)
		if (m_Carriages[i]->getCarriageNumber() == _carriageNumber)
			return i;
	return -1;
}

void Depot::addCarriage(int _carriageNumber, int _capacity)
{
	if (hasCarriage(_carriageNumber))
	isCarriagesFullness();
	Carriage * _pCarriage = new Carriage(_carriageNumber, _capacity);
	m_Carriages.push_back(_pCarriage);
}

void Depot::addCarriage(int _carriageNumber)
{
	if (hasCarriage(_carriageNumber))
		throw std::logic_error("Carriage has already existed");
	isCarriagesFullness();
	Carriage * _pCarriage = new Carriage(_carriageNumber);
	m_Carriages.push_back(_pCarriage);
}

void Depot::removeCarriage(int _carriageNumber)
{
	int _pos = findCarriage(_carriageNumber);
	//isCarriageExist(_pos);
	delete m_Carriages[_pos];
	m_Carriages.erase(m_Carriages.begin() + _pos);
}

Carriage * Depot::getCarriage(int _carriageNumber) const
{
	nonpositiveNumber(_carriageNumber);
	int _pos = findCarriage(_carriageNumber);
	isCarriageExist( _pos);
	return m_Carriages.at(_pos);
}


void Depot::areHasCarriagesIntoTrain(int _trainNumber) const
{
	int _trainPos = findTrain(_trainNumber);
	isTrainExist(_trainPos);
	m_Trains[_trainPos]->hasCarriages();
}


//void Depot::hasHumans(int _trainPos) const
//{
//	isTrainExist(_trainPos);
//	if (!m_Trains[_trainPos]->isEmpty())
//		throw "Someone already at the train";
//}

void Depot::findHuman(const std::string &_humanName) const//не должно біть в депо
{
	for (int i = 0; i < getTrainsCount(); i++)
	{
		if (m_Trains[i]->findHuman(_humanName) != -1)
		throw std::logic_error("Human has been already at the train");
	}
}


void Depot::addCarriageToTrain(int _trainNumber, int _carriageNumber)
{
	int _carriagePos = findCarriage(_carriageNumber);
	isCarriageExist(_carriagePos);
	int _trainPos = findTrain(_trainNumber);
	isTrainExist(_trainPos);

	m_Trains[_trainPos]->addCarriage(m_Carriages[_carriagePos]);
	m_Carriages.erase(m_Carriages.begin() + _carriagePos);
}

void Depot::unfastenCarriage(int _trainNumber, int _carriageNumber)
{
	int _trainPos = findTrain(_trainNumber);
//	isTrainExist( _trainPos);
	int _carriagePos=m_Trains[_trainPos]->findCarriage(_carriageNumber);
	if (_carriagePos == -1)
		throw std::logic_error("Carriage hasn't connected to this train");
	m_Carriages.push_back(m_Trains[_trainPos]->getCarriage(_carriagePos));
	m_Trains[_trainPos]->removeCarriage(_carriageNumber);
}

