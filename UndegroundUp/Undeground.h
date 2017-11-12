#pragma once
#include <iostream>
#include <vector>
#include <string>

class SubwayBranch;
class Station;
class Train;
class Carriage;
class Human;
class Depot;

class Undeground
{
public:
	Undeground()=default;
	Undeground(const Undeground &) = delete;
	Undeground & operator =(const Undeground &) = delete;
	~Undeground();

	/*--------------------------------------------------------------------------------------------------------*/
	
	int getBranchesCount() const;
	std::string getBranchName(int _branchPos) const;
	int getBranchMaxStations(std::string _branchName) const;
	int getStationCount(std::string _branchName) const;
	bool hasBranch(std::string _branchName) const;
	int findBranch(std::string _branchName) const;

	void createBranch(std::string _branchName);
	void createBranch(std::string _branchName, int _maxStations);	
	void removeBranch(std::string _branchName);
	
	void wasBranchAdded(int _branchpos) const;
	void wasBranchNotAdded(int _branchPos) const;
	void wasBranchesNotAdded() const;

	/*--------------------------------------------------------------------------------------------------------*/
	
	void addStationToBranch(std::string _stationName, std::string _branchName);
	void addStationToBranch(std::string _stationName, int _capacity, std::string _branchName);
	void addStationToBranchIntoPos(std::string _stationName,  int _pos, std::string _branchName);
	void addStationToBranchIntoPos(std::string _stationName, int _capacity, int _pos, std::string _branchName);

	void removeStation(std::string _stationName);

	/*--------------------------------------------------------------------------------------------------------*/
	int getDepotsCount() const;
	int findDepot(int _depotNumber) const;
	int findDepotIntoBranches(int _depotNumber) const;

	void createDepot(int _depotNumber);
	void createDepot(int _depotNumber, int _trainsCapacity, int _carriagesCapacity);
	void addDepotToBranch(int _depotNumber, std::string _branchName);
	void removeDepotFromBranch(int _depotNumber, std::string _branchName);
	void removeDepot(int _depotNumber);
	 
	void wasDepotNotAdded(int _depotPos) const;
	void wasDepotsNotAdded() const;

	int hasAddedTrainToDepot(int _trainNumber, int _depotNumber) const;
	void addTrainToDepot(int _trainNumber, int _depotNumber);
	void addTrainToDepot(int _trainNumber, int _maxCarriages, int _depotNumber);
	void addTrainToBranch(int _trainNumber, std::string _branchName, std::string _stationName);
	void removeTrainFromBranch(int _trainNumber, std::string _branchName);
	void addTrainToStation(int _trainNumber, std::string _stationName);
	void removeTrain(int _trainNumber);

	void addCarriageToDepot(int _carriageNumber, int _depotNumber);
	void addCarriageToDepot(int _carriageNumber, int _capacity, int _depotNumber);
	void addCarriageToTrain(int _carriageNumber, int _trainNumber);
	void removeCarriageFromTrain(int _carriageNumber, int _trainNumber);
	void removeCarriage(int _carriageNumber);

	/*--------------------------------------------------------------------------------------------------------*/

	int getHumansCount() const;
	int findHuman(std::string _humanName) const;
	void findHumanIntoUndeground(std::string _humanName) const;

	void createHuman(std::string _humanName);
	void addHumanToStation(std::string  _humanName, std::string _stationName);
	void addHumanToTrain(std::string  _humanName, std::string _platform);
	void addHumanToTrain(std::string  _humanName, std::string _platform, int _carriageNumber);
	void hasAddHuman(std::string  _humanName) const;
	void permanentlyRemoveHuman(std::string _humanName);
	void removeHumanFromStation(std::string  _humanName);
	void moveHumanFromTrainToStation(std::string _humanName, std::string _stationName);

	void wasHumanAdded(int _humanPos) const;
	void wasHumanNotAdded(int _humanPos) const;

private:

	std::vector<SubwayBranch *> m_Branches;
	std::vector<Depot *> m_Depots;
	std::vector<Human *>m_Humans;
	std::vector<Train *>m_Trains;

	void removeHuman(std::string  _humanName, int _humanPos);



};

