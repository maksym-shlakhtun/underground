#pragma once
#include <string>
#include <vector>

class Train;
class Human;

class Station
{
public:
	Station(std::string _Name);
	Station( std::string _Name, int _Capacity);
	Station(const Station & _temp) = delete;
	Station & operator = (const Station & _temp) = delete;
	~Station() {};

	std::string getName() const;
	int getCapacity() const;
	int getHumansCount() const;
	Human & getHuman() const;
	Train * getTrain(int _platform) const;


	bool hasTrains() const;
	bool hasTrain(int _trainNumber) const;
	bool hasArrivedRight() const;
	bool hasArrivedLeft() const;
	bool hasHumanInTrain(int _trainNumber) const;
	int getComeRight() const;
	int getComeLeft() const;
	void arrivedRight(Train *_train);
	void arrivedLeft(Train *_train);
	void departureRight();
	void departureLeft();

	int findHuman(Human & _human) const;
	int findHuman(std::string _humanName) const;
	void addHuman(Human * _human);
	int removeHuman(Human &_human);
	bool removeHuman(std::string _humanName);

	int findHumanInTrain(std::string _humanName, int _platform) const;
	bool moveHumanToTrain(std::string _humanName, std::string _direction);
	bool moveHumanToTrain(std::string _humanName, std::string _direction, int _carriageNumber);
	bool moveHumanFromTrainToStation(std::string _humanName);

	void isHumanAtTheStation(std::string _humanName) const;
	void isHumanAtTheStation(int _humanPos) const;


private:
	int m_Capacity;
	std::string m_Name;
	Train *m_pLeftTrain;
	Train *m_pRightTrain;
	std::vector <Human *> m_humans;

	void validCapacity(int _temp);
	int  invalidDirection(std::string _dsrection) const;
	void isArrived() const;
	void isArrived(int _direction) const;
	void isFullnes() const;
	void isHumanAtTheStation(Human & _human) const;

	
	void isHumanNotAtTheStation(int _humanPos) const;
	void isHumanAtTheTrain(std::string _humanName) const;
	//	int isAddHumanToTrain(std::string _humanName, std::string _direction) const;
};

inline void Station::validCapacity(int _temp)
{
	if (m_Capacity <= 0 || m_Capacity > 100)
		throw "Incorrect capacity";
}

inline int  Station::invalidDirection(std::string _direction) const
{
	if (_direction == "Right" || _direction == "right"||_direction == "platform1")
		return 1;
	if (_direction == "Left"|| _direction == "left"||_direction == "platform2")
		return 2;
	throw "Invalid direction";
}

inline void Station::isArrived() const
{
	if (!hasTrains())
		throw "Station has no trains";
}

inline void Station::isFullnes() const
{
	if ((getHumansCount() + 1) >= m_Capacity)
		throw "Station is full";
}

inline void Station::isArrived(int _direction) const
{
	if ((_direction == 1 && !hasArrivedRight()) || (_direction == 2 && !hasArrivedLeft()))
		throw "Train is not arrived to the station";
}

inline void Station::isHumanAtTheStation(Human & _human) const
{
	if (findHuman(_human) != -1)
		throw "Human is already at the station";
}

inline void Station::isHumanAtTheStation(std::string _humanName) const
{
	if (findHuman(_humanName) != -1)
		throw "Human is already at the station";
}

inline void Station::isHumanAtTheStation(int _humanPos) const
{
	if (_humanPos != -1)
		throw "Human is already at the station";
}

inline void Station::isHumanNotAtTheStation(int _humanPos) const
{
	if (_humanPos == -1)
		throw "Human is not at the station";
}


//inline void Station::isHumanAtTheTrain(std::string _humanName) const
//{
//	isArrived();
//	is()
//
//	if (findHumanInTrain(_humanName)==-1)
//
//
//}

//inline int Station::isAddHumanToTrain(std::string _humanName, std::string _direction) const
//{
//
//}