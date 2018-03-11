#pragma once
#include <string>
#include <vector>

class Train;
class Human;

class Station
{
public:
	

	Station(const std::string & _name, int _capacity=10);
	Station(const Station & _temp) = delete;
	const Station & operator = (const Station & _temp) = delete;
	~Station() {}

	const std::string & getName() const;
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

	int findHuman(const Human & _human) const;
	int findHuman(const std::string & _humanName) const;
	void addHuman(Human * _human);
	int removeHuman(Human &_human);

	bool removeHuman(const std::string &_humanName);

	int findHumanInTrain(const std::string & _humanName, int _platform) const;
	bool moveHumanToTrain(const std::string & _humanName, const int _platform);
	bool moveHumanToTrain(const std::string & _humanName, const int _platform, int _carriageNumber);

	bool moveHumanFromTrainToStation(const std::string & _humanName);

	void isHumanAtTheStation(const std::string & _humanName) const;
	void isHumanAtTheStation(int _humanPos) const;


private:
	int m_Capacity;
	std::string m_Name;
	Train *m_pLeftTrain;
	Train *m_pRightTrain;
	std::vector <Human *> m_humans;

	void validCapacity(int _temp);

	void isArrived() const;
	void isArrived(int _direction) const;
	void isFullnes() const;
	void isHumanAtTheStation(Human & _human) const;

	
	void isHumanNotAtTheStation(int _humanPos) const;
	void isHumanAtTheTrain(const std::string & _humanName) const;
	//	int isAddHumanToTrain(std::string _humanName, std::string _direction) const;
};

inline void Station::validCapacity(int _temp)
{
	if (m_Capacity <= 0 || m_Capacity > 100)
		throw std::logic_error("Incorrect capacity");
}

inline void Station::isArrived() const
{
	if (!hasTrains())
		throw std::logic_error("Station hasn't any trains");
}

inline void Station::isFullnes() const
{
	if ((getHumansCount() + 1) >= m_Capacity)
		throw std::logic_error("Station is full");
}

inline void Station::isArrived(int _direction) const
{
	if ((_direction == 1 && !hasArrivedRight()) || (_direction == 2 && !hasArrivedLeft()))
		throw std::logic_error("Train hasn't arrived to the station");
}

inline void Station::isHumanAtTheStation(Human & _human) const
{
	if (findHuman(_human) != -1)
		throw std::logic_error("Human is at the station now");
}

inline void Station::isHumanAtTheStation(const std::string & _humanName) const
{
	if (findHuman(_humanName) != -1)
		throw std::logic_error("Human is at the station now");
}

inline void Station::isHumanAtTheStation(int _humanPos) const
{
	if (_humanPos != -1)
		throw std::logic_error("Human is at the station");
}

inline void Station::isHumanNotAtTheStation(int _humanPos) const
{
	if (_humanPos == -1)
		throw std::logic_error("Human isn't at the station");
}