#pragma once
#include<vector>
#include <string>


class Station;
class Depot;
class Train;
class Human;
enum class Platforms;

class SubwayBranch

{

public:

	SubwayBranch(const std::string &_name, int _maxStations=10);
	SubwayBranch(const SubwayBranch &) = delete;
	SubwayBranch & operator = (const SubwayBranch &) = delete;
	~SubwayBranch();

	const std::string & getName() const;
	int getMaxStations() const;
	int getStationsCount() const;
	Station & getStation(int _pos) const;
	Train * getTrain(Platforms _platform, int _stationPosBegin) const;

	/*--------------------------------------------------------------------------------------------------------*/

	bool hasStations() const;
	int findStation(const std::string & _stationName) const;
	int findStation(Station * _pstation) const;

	void addStation(Station * _pstation);
	void addStation(const std::string &_stationName);
	void addStation(const std::string &_stationName, int _capacity);
	void addStationIntoPos(const std::string &_stationName, int _capacity, int _pos);
	void addStationIntoPos(const std::string &_stationName, int _pos);
	void addStationIntoPos(Station * _pstation, int _pos);
	bool removeStation(const std::string &_stationName);
	bool removeStation(Station &_station);

	/*--------------------------------------------------------------------------------------------------------*/

	bool hasTrains() const;
	bool hasTrain(int _trainNumber) const;
	void hasRemoveTrainIntoDepot(int _trainNumber, int _stationPos) const;
	int findTrain(int _number) const;

	void addTrainToBranch(int _trainNumber, const std::string &_stationName) const;
	void addTrainToBranch(int _trainNumber, Station *_pstation) const;
	void removeTrainIntoDepot(int _trainNumber) const;

	void MoveTrain(int _trainNumber, const std::string &_stationName);
	int IncorrectStation(int _trainNumber, int _stationPos, int _stationPosBegin) const;

	/*--------------------------------------------------------------------------------------------------------*/
	int getDepotNumber() const;
	bool hasDepot() const;
	void hasDepot(int _depotNumber) const;

	void addDepot(Depot & _depot);
	void removeDepot();
	void removeDepot(int _depotNumber);



	/*--------------------------------------------------------------------------------------------------------*/

	void findHuman(const std::string & _humanName) const;
	void findHuman(const Human & _human) const;

	int addHumanToStation(Human * _phuman, const std::string & _stationName);
	bool hasHumansInTrain(int _stationPos, int _trainNumber) const;
	bool moveHumanFromTrainToStation(const std::string &_humanName, const std::string & _stationName);
	bool moveHumanFromStationToTrain(const std::string &_humanName, const std::string & _stationName);
	bool moveHumanFromStationToTrain(const std::string &_humanName, const std::string & _stationName, int _carriageNumber);

	bool removeHuman(const std::string & _humanName);
	/*--------------------------------------------------------------------------------------------------------*/

	void isDepotNotAttach() const;
	void areStationsNotAdd() const;
	void wasStationNotAdded(int _stationPos) const;
	void wasStationAdded(const std::string & _stationName) const;
	void IsTrainNotAdd(int _stationPos) const;
	void IsTrainAtTheBranch(int _trainNumber) const;
	void isEndStation(int _stationPos) const;
	void IncorrectMaxStations(int _maxStation) const;
	void IsStationsNotAdded() const;
	void IsStationsAdded() const;


	static int getMaxNormalStations();

private:

	static const int maxNormalStationsCount = 10;

	std::string m_Name;
	int m_maxStations;
	std::vector<Station *> m_Stations;
	Depot * m_pDepot;

	};


inline int SubwayBranch::getMaxNormalStations()
{
	return maxNormalStationsCount;
}

inline void SubwayBranch::isDepotNotAttach() const
{
	if (!hasDepot())
		throw std::logic_error("Depot hasn't been added to brunch");
}
inline void SubwayBranch::areStationsNotAdd() const
{
	if (!hasStations())
		throw std::logic_error("Subway branch doesn't have any station");
}
inline void SubwayBranch:: wasStationAdded(const std::string & _stationName) const
{
	if (findStation(_stationName )!= -1)
		throw std::logic_error("The branch have already included this station");
}
inline void SubwayBranch:: wasStationNotAdded(int _stationPos) const
{
	if (_stationPos == -1)
		throw std::logic_error("Subway branches aren't including this station now ");
}
inline void SubwayBranch::IsTrainNotAdd(int _stationPos) const
{
	if (_stationPos == -1)
		throw std::logic_error("Train hasn't been added to branch");
}

inline void SubwayBranch::IsTrainAtTheBranch(int _trainNumber) const
{
	if (findTrain(_trainNumber) != -1)
		throw std::logic_error("Train have already been at the branch");
}

inline void SubwayBranch::isEndStation(int _stationPos) const
{
if (_stationPos != 0 && _stationPos != getStationsCount() - 1)
		throw std::logic_error("This station isn't final station");
}

inline void SubwayBranch::IncorrectMaxStations(int _maxStations) const
{
	if (_maxStations < 0 || _maxStations>SubwayBranch::maxNormalStationsCount)
		throw std::logic_error("Incorrect maximum number of stations");
}

inline void SubwayBranch::IsStationsNotAdded() const
{
	if (getStationsCount() == 0)
		throw std::logic_error("There are no any stations at  the branch");
}

inline void SubwayBranch::IsStationsAdded() const
{
	throw std::logic_error("There are stations on the branch");
}