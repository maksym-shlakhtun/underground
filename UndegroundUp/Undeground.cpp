#include <iostream>
#include <vector>
#include <string>

#include "Undeground.h"
#include "Subway_branch.h"
#include "station.h"
#include "train.h"
#include "carriage.h"
#include "human.h"
#include "depot.h"


Undeground::~Undeground()
{
	for (SubwayBranch *_pBranch : m_Branches)
	{
		delete _pBranch;
	}
	for (Depot * _pDepot : m_Depots)
	{
		delete _pDepot;
	}
	for (Human *_pHuman : m_Humans)
	{
		delete _pHuman;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Undeground::createBranch(const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchAdded(_branchPos);
	SubwayBranch * _branch = new SubwayBranch(_branchName);
	m_Branches.push_back(_branch);
}

void Undeground::createBranch(const std::string & _branchName, int _maxStations)
{
	int _branchPos = findBranch(_branchName);
	wasBranchAdded(_branchPos);
	SubwayBranch * _branch = new SubwayBranch(_branchName, _maxStations);
	m_Branches.push_back(_branch);
}


void Undeground::removeBranch(const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->IsStationsAdded();
	m_Branches.erase(m_Branches.begin() + _branchPos);
}


int Undeground::getBranchesCount() const
{
	return m_Branches.size();
}

const std::string & Undeground::getBranchName(int _branchPos) const
{
	return m_Branches.at(_branchPos)->getName();
}

int Undeground::getBranchMaxStations(const std::string & _branchName) const
{
	int _branchPos=findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	return m_Branches[_branchPos]->getMaxStations();
}

int Undeground::getStationCount(const std::string & _branchName) const
{
	int _branchPos=findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	return m_Branches[_branchPos]->getStationsCount();
}


bool Undeground::hasBranch(const std::string & _branchName) const
{
	return findBranch(_branchName) != -1;
}

int Undeground::findBranch(const std::string & _branchName) const
{
	for (int i = 0; i < getBranchesCount(); i++)
		if (m_Branches[i]->getName() == _branchName)
			return i;
	return -1;
}


void Undeground::wasBranchAdded(int _branchPos) const
{
	if (_branchPos != -1)
		throw std::logic_error("Branch's name has already existed");
}

void Undeground::wasBranchNotAdded(int _branchPos) const
{
	if (_branchPos == -1)
		throw std::logic_error("Branch's name doesn't exist");
}

void Undeground::wasBranchesNotAdded() const
{
	if (getBranchesCount()==0)
	throw std::logic_error("There are no branches at the underground");
}

/*----------------------------------------------------------------------------------------------------------------------*/


void Undeground::addStationToBranch(const std::string & _stationName, const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addStation(_stationName);
}

void Undeground::addStationToBranch(const std::string & _stationName, int _capacity, const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addStation(_stationName, _capacity);
}

void Undeground::addStationToBranchIntoPos(const std::string & _stationName,  int _pos, const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addStationIntoPos(_stationName, _pos);
}

void Undeground::addStationToBranchIntoPos(const std::string & _stationName, int _capacity, int _pos, const std::string & _branchName)
{
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addStationIntoPos(_stationName, _capacity , _pos);
}

void Undeground::removeStation(const std::string & _stationName)
{
	wasBranchesNotAdded();
	int _temp = 0;
	for (int i = 0; i < getBranchesCount(); i++)
	{
		_temp = m_Branches[i]->removeStation(_stationName);
		if (_temp == 1)
			break;
	}
	m_Branches[0]->wasStationNotAdded(_temp);
}


/*--------------------------------------------------------------------------------------------------------*/

int Undeground::getDepotsCount() const
{
	return m_Depots.size();
}

int Undeground::findDepot(int _depotNumber) const
{
	for (int i = 0; i < getDepotsCount(); i++)
		if (m_Depots[i]->getNumber() == _depotNumber)
			return i;
	return -1;
}
int Undeground::findDepotIntoBranches(int _depotNumber) const
{
	for (int i = 0; i < getBranchesCount(); i++)
		if (m_Branches[i]->getDepotNumber() == _depotNumber)
			return i;
	return -1;
}

void Undeground::createDepot(int _depotNumber)
{
	int _depotPos = findDepot(_depotNumber);
	if (_depotPos != -1)
		throw std::logic_error("This depo already exist");
	Depot * _depot = new Depot(_depotNumber);
	m_Depots.push_back(_depot);
}

void Undeground::createDepot(int _depotNumber, int _trainsCapacity, int _carriagesCapacity)
{
	int _depotPos = findDepot(_depotNumber);
	if (_depotPos != -1)
		throw std::logic_error("This depo already exist");
	Depot * _depot = new Depot(_depotNumber, _trainsCapacity,  _carriagesCapacity);
	m_Depots.push_back(_depot);
}

void Undeground::addDepotToBranch(int _depotNumber, const std::string & _branchName)
{
	wasDepotsNotAdded();
	int _depotPos = findDepot(_depotNumber);
	wasDepotNotAdded( _depotPos);
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addDepot(*m_Depots[_depotPos]);
}

void Undeground::removeDepotFromBranch(int _depotNumber, const std::string & _branchName)
{
	wasDepotsNotAdded();
	int _depotPos = findDepot(_depotNumber);
	wasDepotNotAdded(_depotPos);
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->removeDepot(_depotNumber);
}

void Undeground::removeDepot(int _depotNumber)
{
	wasDepotsNotAdded();
	int _depotPos = findDepot(_depotNumber);
	wasDepotNotAdded(_depotPos);
	for (int i = 0; i < getBranchesCount(); i++)
	{
		if (m_Branches[i]->getDepotNumber() == _depotNumber)
			throw std::logic_error( "The depot still attaches to the branch");
	}
	m_Depots.erase(m_Depots.begin()+_depotPos);
}

void Undeground::wasDepotNotAdded(int _depotPos) const
{
	if (_depotPos == -1)
		throw std::logic_error("There is no depo with this number");
}

void Undeground:: wasDepotsNotAdded() const
{
	if (getDepotsCount() == 0)
		throw std::logic_error("There are no depots at the underground");
}


int Undeground::hasAddedTrainToDepot(int _trainNumber, int _depotNumber) const
{
	wasDepotsNotAdded();
	int  _depotPos = -1;
	int  _trainPos = -1;
	for (int i = 0; i < getDepotsCount(); i++)
	{
		_trainPos = m_Depots[i]->findTrain(_trainNumber);
		m_Depots[i]->isTrainNotExist(_trainPos);
		if (m_Depots[i]->getNumber() == _depotNumber)
			_depotPos = i;
	}
	wasDepotNotAdded(_depotPos);
	return _depotPos;
}

void Undeground::addTrainToDepot(int _trainNumber, int _depotNumber)
{
	wasDepotsNotAdded();
	m_Depots[hasAddedTrainToDepot( _trainNumber,  _depotNumber)]->addTrain(_trainNumber);
}

void Undeground::addTrainToDepot(int _trainNumber, int _maxCarriages, int _depotNumber)
{
	wasDepotsNotAdded();
	m_Depots[hasAddedTrainToDepot(_trainNumber, _depotNumber)]->addTrain(_trainNumber, _maxCarriages);
}

void Undeground::addTrainToBranch(int _trainNumber, const std::string & _branchName, const std::string & _stationName)
{
	wasDepotsNotAdded();
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->addTrainToBranch(_trainNumber,  _stationName);
}

void Undeground::removeTrainFromBranch(int _trainNumber, const std::string & _branchName)
{
	wasDepotsNotAdded();
	int _branchPos = findBranch(_branchName);
	wasBranchNotAdded(_branchPos);
	m_Branches[_branchPos]->removeTrainIntoDepot(_trainNumber);
}

void Undeground::addTrainToStation(int _trainNumber, const std::string & _stationName)
{
	wasDepotsNotAdded();
	wasBranchesNotAdded();
	int _stationPos = -1;
	for (int i = 0; i < getBranchesCount(); i++)
	{
		_stationPos = m_Branches[i]->findStation(_stationName);
		if (_stationPos != -1)
			m_Branches[i]->MoveTrain(_trainNumber, _stationName);
		break;
	}
	m_Branches[0]->wasStationNotAdded(_stationPos);
}

void Undeground::removeTrain(int _trainNumber)
{
	wasDepotsNotAdded();
	int _temp = 0;
	int _branchPos;
	for (int i = 0; i < getDepotsCount(); i++)
	{
		int _trainPos = m_Depots[i]->findTrain(_trainNumber);
		if (_trainPos != -1)
			_branchPos = findDepotIntoBranches(m_Depots[i]->getNumber());
		if ((_branchPos == -1) || ((_branchPos != -1) && (m_Branches[_branchPos]->findTrain(_trainNumber) == -1)))
			m_Depots[i]->removeTrain(_trainPos);
		_temp = 1;
	}
	if (_temp == 0)
		throw std::logic_error("This train has been already at the branch");
}

void Undeground::addCarriageToDepot(int _carriageNumber, int _depotNumber)
{
	wasDepotsNotAdded();
	int _depotPos = findDepot(_depotNumber);
	wasDepotNotAdded( _depotPos);
	m_Depots[_depotPos]->addCarriage(_carriageNumber);
}

void Undeground::addCarriageToDepot(int _carriageNumber, int _capacity, int _depotNumber)
{
	wasDepotsNotAdded();
	int _depotPos = findDepot(_depotNumber);
	wasDepotNotAdded(_depotPos);
	m_Depots[_depotPos]->addCarriage(_carriageNumber, _capacity);
}

void Undeground::addCarriageToTrain(int _carriageNumber, int _trainNumber)
{
	wasDepotsNotAdded();
	int _trainPos;
	int _carriagePos;
	int _branchPos;
	for (int i = 0; i < getDepotsCount(); i++)
	{
		_trainPos = m_Depots[i]->findTrain(_trainNumber);
		_carriagePos = m_Depots[i]->findCarriage(_carriageNumber);
		_branchPos= findDepotIntoBranches(m_Depots[i]->getNumber());
		if (
				(
						 (_trainPos != -1)
					&& (_carriagePos != -1) 
					&& (_branchPos == -1)
				) 
				|| 
				(
						(_trainPos != -1) 
					&& (_carriagePos != -1) 
					&& (_branchPos != -1) 
					&& !(m_Branches[_branchPos]->hasTrain(_trainNumber))
				)
			)
			m_Depots[i]->addCarriageToTrain(_trainNumber, _carriageNumber);
		else throw std::logic_error("You can't add this carriage to train");
	}
}

void Undeground::removeCarriageFromTrain(int _carriageNumber, int _trainNumber)
{
	wasDepotsNotAdded();
	int _trainPos;
	int _carriagePos;
	int _branchPos;
	int _temp=-1;
	for (int i = 0; i < getDepotsCount(); i++)
	{
		_trainPos = m_Depots[i]->findTrain(_trainNumber);
		_branchPos = findDepotIntoBranches(m_Depots[i]->getNumber());
		if ((_trainPos != -1) && (_branchPos == -1))
		{
			m_Depots[i]->unfastenCarriage(_carriageNumber, _trainNumber);
			_temp = 1;
		}
		break;
	}
		if (_temp==-1)
			throw std::logic_error("You can't disconnect this carriage from the train");
}

void Undeground::removeCarriage(int _carriageNumber)
{
	wasDepotsNotAdded();
	int _carriagePos=-1;
	for (int i = 0; i < getDepotsCount(); i++)
	{
		_carriagePos = m_Depots[i]->findCarriage(_carriageNumber);
		if (_carriagePos != -1)
			m_Depots[i]->removeCarriage(_carriagePos);
		break;
	}
	m_Depots[0]->isCarriageExist(_carriagePos);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

int Undeground::getHumansCount() const
{
	return m_Humans.size();
}


int Undeground::findHuman(const std::string & _humanName) const
{
	for (int i = 0; i < getHumansCount(); i++)
	{
		if (m_Humans[i]->getName() == _humanName)
			return i;
	}
	return -1;
}

void Undeground::findHumanIntoUndeground(const std::string & _humanName) const
{
	for (int i = 0; i < getBranchesCount(); i++)
		m_Branches[i]->findHuman(_humanName);
}


void Undeground::createHuman(const std::string & _humanName)
{
	int _humanPos = findHuman(_humanName);
	wasHumanAdded(_humanPos);
	Human * _human = new Human(_humanName);
	m_Humans.push_back(_human);
}

void Undeground::addHumanToStation(const std::string &  _humanName, const std::string & _stationName)
{
	wasBranchesNotAdded();
	int _humanPos = findHuman(_humanName);
	int _stationPos;
	int _temp=-1;
	wasHumanNotAdded(_humanPos);
	findHumanIntoUndeground(_humanName);
	for (int i = 0; i < getBranchesCount(); i++)
	{
		_temp=m_Branches[i]->addHumanToStation(m_Humans[_humanPos], _stationName);
		if (_temp == 1)
			break;
	}
		m_Branches[0]->wasStationNotAdded(_temp);
}

void Undeground::addHumanToTrain(const std::string &  _humanName, const std::string & _platform)
{
	hasAddHuman(_humanName);
	for (int i = 0; i<getBranchesCount(); i++)
	{
		if (m_Branches[i]->moveHumanFromStationToTrain(_humanName, _platform))
			return;
	}
	throw std::logic_error("This operation is not possible");
}

void Undeground::addHumanToTrain(const std::string &  _humanName, const std::string & _platform, int _carriageNumber)
{
	hasAddHuman(_humanName);
	for (int i = 0; i<getBranchesCount(); i++)
	{
		 if (m_Branches[i]->moveHumanFromStationToTrain(_humanName, _platform, _carriageNumber))
		 return;
	}
		throw std::logic_error("This operation is not possible");
}

void Undeground::moveHumanFromTrainToStation(const std::string & _humanName, const std::string & _stationName) 
{
	hasAddHuman(_humanName);
	for (int i = 0; i<getBranchesCount(); i++)
	{
		if (m_Branches[i]->moveHumanFromTrainToStation(_humanName, _stationName))
			return;
	}
	throw std::logic_error("Human isn't situating at the train now");
}

void Undeground::hasAddHuman(const std::string &  _humanName) const
{
	int _humanPos = findHuman(_humanName);
	wasBranchesNotAdded();
	wasHumanNotAdded(_humanPos);
}
void Undeground::permanentlyRemoveHuman(const std::string & _humanName)
{
	int _humanPos = findHuman(_humanName);
	removeHuman(_humanName, _humanPos);
	m_Humans.erase(m_Humans.begin() + _humanPos);
}

void Undeground::removeHumanFromStation(const std::string &  _humanName)
{
	int _humanPos = findHuman(_humanName);
	removeHuman(_humanName, _humanPos);
}


void Undeground::wasHumanAdded(int _humanPos) const 
{
	if (_humanPos != -1)
		throw std::logic_error("Human's name has already exist");
}

void Undeground::wasHumanNotAdded(int _humanPos) const
{
	if (_humanPos == -1)
		throw std::logic_error("Human hasn't been add");
}


void Undeground::removeHuman(const std::string &  _humanName, int  _humanPos)
{
	wasHumanNotAdded(_humanPos);

	for (int i = 0; i < getBranchesCount(); i++)
	{
		if (m_Branches[i]->removeHuman(_humanName))
			break;
	}
}