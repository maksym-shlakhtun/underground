#include <vector>
#include<string>
#include "Subway_branch.h"
#include "station.h"
#include "depot.h"
#include "train.h"
#include "human.h"

SubwayBranch::SubwayBranch(const std::string & _Name, int _maxStations)
	: m_Name(_Name), m_maxStations(_maxStations)
{
	IncorrectMaxStations(m_maxStations);
}


const std::string & SubwayBranch::getName() const
{
	return m_Name;
}

int SubwayBranch::getMaxStations() const
{
	return m_maxStations;
}

int SubwayBranch::getStationsCount() const
{
	return m_Stations.size();
}

Station & SubwayBranch::getStation(int _pos) const
{
	if (_pos <0 || _pos>getStationsCount())
		throw  std::logic_error("There is incorrect number of station");
	return *m_Stations.at(_pos-1);
}


SubwayBranch::~SubwayBranch()
{
	for (Station * _pStation : m_Stations)
		delete _pStation;
}

Train * SubwayBranch::getTrain(int _platform, int _stationPosBegin) const
{
	return m_Stations[_stationPosBegin]->getTrain(_platform);
}

/*--------------------------------------------------------------------------------------------------------*/

bool SubwayBranch::hasStations() const
{
	return getStationsCount() > 0;
}


int SubwayBranch ::findStation(const std::string & _station) const
{
	for (int i = 0; i < getStationsCount(); i++)
		if (m_Stations[i]->getName() == _station)
			return i;
	return -1;
}


void SubwayBranch::addStation(Station *_pstation)
{
	wasStationAdded(_pstation->getName());
	m_Stations.push_back(_pstation);
}

void SubwayBranch::addStation(const std::string & _stationName)
{
	wasStationAdded(_stationName);
	Station *station1 = new Station(_stationName);
	m_Stations.push_back(station1);
}

void SubwayBranch::addStation(const std::string & _stationName, int _capacity)
{
	wasStationAdded(_stationName);
	Station *station1 = new Station(_stationName, _capacity);
	m_Stations.push_back(station1);
}

void SubwayBranch::addStationIntoPos(const std::string & _stationName, int _capacity, int _pos)
{
	wasStationAdded(_stationName);
	Station *station1 = new Station(_stationName, _capacity);
	m_Stations.insert(m_Stations.begin() + _pos - 1, station1);
}

void SubwayBranch::addStationIntoPos(const std::string & _stationName,  int _pos)
{
	wasStationAdded(_stationName);
	Station *station1 = new Station(_stationName);
	m_Stations.insert(m_Stations.begin() + _pos - 1, station1);
}

void SubwayBranch::addStationIntoPos(Station *_pstation, int _pos)
{
	wasStationAdded(_pstation->getName());
	m_Stations.insert(m_Stations.begin()+_pos-1, _pstation);
}

int SubwayBranch::removeStation(Station &_station)
{
	int _stationPos = findStation(_station.getName());
	if (_stationPos == -1)
		return _stationPos;
	m_Stations.erase(m_Stations.begin() + _stationPos);
	return 1;
}

int SubwayBranch::removeStation(const std::string & _stationName)
{
	int _stationPos = findStation(_stationName);
	if (_stationPos == -1)
		return _stationPos;
	if ((m_Stations[_stationPos]->hasTrains()) || (m_Stations[_stationPos]->hasArrivedLeft()) || (m_Stations[_stationPos]->hasArrivedRight()))
		throw std::logic_error("The station is using at the moment");
		m_Stations.erase(m_Stations.begin() + _stationPos);
	return 1;
}

/*--------------------------------------------------------------------------------------------------------*/

bool SubwayBranch::hasTrains() const
{
	for (int i = 0; i < getStationsCount(); i++)
		if(m_Stations[i]->hasTrains())
			return true;
	return false;
}

bool SubwayBranch::hasTrain(int _trainNumber) const
{
	for (int i = 0; i < getStationsCount(); i++)
		if (m_Stations[i]->hasTrain(_trainNumber))
			return true;
	return false;
}

void SubwayBranch::addTrainToBranch(int _trainNumber, const std::string & _stationName) const
{ 
	isDepotNotAttach();
	areStationsNotAdd();
	int _stationPos = findStation(_stationName);
	wasStationNotAdded(_stationPos);
	isEndStation(_stationPos);
	m_pDepot->areHasCarriagesIntoTrain(_trainNumber);
	int _trainPos = m_pDepot->findTrain(_trainNumber);
	//IsTrainAtTheBranch(_trainNumber);

	if (_stationPos == 0)
	{
		m_Stations[_stationPos]->arrivedRight(m_pDepot->getTrain(_trainPos));
		if (_stationPos == getStationsCount() - 1)
		{
			m_Stations[_stationPos]->arrivedLeft(m_pDepot->getTrain(_trainPos));
		}
	}
	m_pDepot->removeTrain(_trainPos);
}

void SubwayBranch::removeTrainIntoDepot(int _trainNumber) const
{
	isDepotNotAttach();
	int _stationPos = findTrain(_trainNumber);
	IsTrainNotAdd(_stationPos);
	isEndStation(_stationPos);

	//m_pDepot->hasHumans(_trainNumber);//or drop people to station
m_pDepot->addTrain(m_Stations[_stationPos]->getTrain(_trainNumber));	
hasRemoveTrainIntoDepot(_trainNumber, _stationPos);
	
	
}

void SubwayBranch::hasRemoveTrainIntoDepot(int _trainNumber, int _stationPos) const
{
	if (_stationPos == 0)
	{
		if (m_Stations[_stationPos]->getComeLeft() != _trainNumber)
			throw std::logic_error("Train has been at another platform");
		m_Stations[_stationPos]->departureLeft();
	}
	if (_stationPos == getStationsCount() - 1)
	{
		if (m_Stations[_stationPos]->getComeRight() != _trainNumber)
			throw std::logic_error("Train has been at another platform");
		m_Stations[_stationPos]->departureRight();
	}
}

int SubwayBranch::findTrain(int _number) const
{
	for (int i = 0; i < getStationsCount(); i++)
		if ((m_Stations[i]->getComeLeft()==_number) ||((m_Stations[i]->getComeRight() == _number)))
			return i;
	return -1;
}

void SubwayBranch::MoveTrain(int _trainNumber, const std::string & _stationName)
{
	int _stationPos = findStation(_stationName);
	int _stationPosBegin=findTrain(_trainNumber);
	int _platform=IncorrectStation(_trainNumber, _stationPos, _stationPosBegin);
	Train * train1 = getTrain(_platform, _stationPosBegin);
	if (_platform == 1)
	{
		m_Stations[_stationPosBegin]->departureRight();
		m_Stations[_stationPos]->arrivedRight(train1);
	}
	else
	{
		m_Stations[_stationPosBegin]->departureLeft();
		m_Stations[_stationPos]->arrivedLeft(train1);
	}
}

int SubwayBranch::IncorrectStation(int _trainNumber, int _stationPos,  int _stationPosBegin) const
{ 
	wasStationNotAdded( _stationPos);
	
	IsTrainNotAdd(_trainNumber);
	if (_stationPos - _stationPosBegin == 1)
	{
		if (!m_Stations[_stationPosBegin]->hasArrivedRight())
			throw std::logic_error("Train isn't at the station now");
		return 1;
	}
	if (_stationPosBegin - _stationPos == 1)
	{
		if (!m_Stations[_stationPosBegin]->hasArrivedLeft())
			throw "Train isn't at the station now";
		return 2;
	}
	throw std::logic_error("Train can not move to this station");
}
/*-----------------------------------------------------------------------------------------------------------------*/

int SubwayBranch::getDepotNumber() const
{
	if (hasDepot())
	return m_pDepot->getNumber();
	else return -1;
}

bool SubwayBranch::hasDepot() const
{
	return  m_pDepot != nullptr;
}

void SubwayBranch::hasDepot(int _depotNumber) const
{
	if (m_pDepot->getNumber() != _depotNumber)
		throw std::logic_error("Depot hasn't attached to the branch");
}

void SubwayBranch::addDepot(Depot & _depot)
{
	if (hasDepot())
		throw std::logic_error("Depot has already added to brunch");
	m_pDepot = &_depot;
}

void SubwayBranch::removeDepot()
{
	if (hasTrains())
		throw std::logic_error("Train from this depot is at the branch now");
	isDepotNotAttach();
	m_pDepot = nullptr;
}

void SubwayBranch::removeDepot(int _depotNumber)
{
	hasDepot(_depotNumber);
		if (hasTrains())
			throw std::logic_error("Train from this depot is at the branch now");
		isDepotNotAttach();
		m_pDepot = nullptr;
}

/*------------------------------------------------------------------------------------------------------------------------*/

void SubwayBranch::findHuman(const std::string &_humanName) const
{
	for (int i = 0; i < getStationsCount(); i++)
	{
		if ((m_Stations[i]->findHuman(_humanName) != -1) || (m_Stations[i]->findHumanInTrain(_humanName, 1) == 1) || (m_Stations[i]->findHumanInTrain(_humanName, 2) == 1))
			throw std::logic_error( "Human has been already at the branch");
	}
}


int  SubwayBranch::addHumanToStation(Human * _human, const std::string & _stationName)
{
	int _stationPos = findStation(_stationName);
	if (_stationPos != -1)
	{
		m_Stations[_stationPos]->addHuman(_human);
		return 1;
	}
	else return -1;
}


bool SubwayBranch::hasHumansInTrain(int _stationPos, int _trainNumber) const
{
	return m_Stations[_stationPos]->hasHumanInTrain(_trainNumber);
}


bool SubwayBranch::moveHumanFromTrainToStation(const std::string & _humanName, const std::string & _stationName)
{
	int _stationPos=findStation(_stationName);
	wasStationNotAdded(_stationPos);
	return m_Stations[_stationPos]->moveHumanFromTrainToStation(_humanName);
}

bool SubwayBranch::moveHumanFromStationToTrain(const std::string & _humanName,const std::string & _platform)
{
	for (int i = 0; i < getStationsCount(); i++)
	{
		if (m_Stations[i]->moveHumanToTrain(_humanName, _platform))
		{
			return true;
		}
	}
	return false;
}

bool SubwayBranch::moveHumanFromStationToTrain(const std::string & _humanName, const std::string & _platform, int _carriageNumber)
{
		for (int i = 0; i < getStationsCount(); i++)
	{
			if (m_Stations[i]->moveHumanToTrain(_humanName, _platform, _carriageNumber))
			{
				return true;
			}
	}
		return false;
}


bool SubwayBranch::removeHuman(const std::string & _humanName)
{
	bool _temp = false;
	for (int i = 0; i < getStationsCount(); i++)
	{
		if (m_Stations[i]->removeHuman(_humanName))
			_temp = true;
	}
	if (!_temp)
		throw std::logic_error("Human is situating at the train now");
	return _temp;
}

/*------------------------------------------------------------------------------------------------------------------------*/




