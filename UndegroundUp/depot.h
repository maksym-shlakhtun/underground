#pragma once
#include <vector>

class Train;
class Carriage;

class  Depot
{
public:
	Depot::Depot(int _DepotNumber, int _trainCapacity=10, int _carriageCapacity=10);
	Depot(const Depot&) = delete;
	Depot & operator = (const Depot &) = delete;
	~Depot();

int getNumber();
int getTrainsCapacity() const;
int getCarriagesCapacity() const;
int getTrainsCount() const;
int getCarriagesCount() const;

void isTrainsFullness() const;
bool hasTrain(int _trainNumber) const;
int findTrain(int _trainNumber) const;
int findTrain(Train &_train) const;
void  addTrain(Train * _train);
void	addTrain(int _trainNumber);
void	addTrain(int _trainNumber, int _maxCarriages);
void removeTrain(Train & _train);
void removeTrain(int _trainPos);
Train * getTrain(int _pos) const;
int getNCarriages(int _trainNumber);

void isCarriagesFullness() const;
bool hasCarriage(int _carriageNumber) const;
int findCarriage(Carriage & _carriage) const;
int findCarriage(int _carriageNumber) const;
void	addCarriage(int _carriageNumber, int _carriage);
void	addCarriage(int _carriageNumber);
void removeCarriage(int _carriageNumber);
Carriage * getCarriage(int _carriageNumber) const;

void areHasCarriagesIntoTrain(int _trainNumber) const;
void hasHumans(int _trainNumber) const;
void findHuman(std::string _humanName) const;

void addCarriageToTrain(int _trainNumber, int _carriageNumber);
void unfastenCarriage(int _trainNumber, int _carriageNumber);

void isTrainNotExist(int _trainPos) const;
void isCarriageExist(int _pos) const;

		private:
			std::vector<Train*> m_Trains;
			std::vector<Carriage*>m_Carriages;
			int m_trainsCapacity;
			int m_carriagesCapacity;
			int m_number;

			void incorrectNumber(int _depotNumber) const;
			void incorrectCapacity(int _capacity) const;
			void isTrainExist(int _pos) const;
			void nonpositiveNumber(int _number) const;
};

inline void Depot::incorrectNumber(int _depotNumber) const
{
	if (_depotNumber <= 0 )
		throw "Incorrect number";
}

inline void Depot::incorrectCapacity(int _capacity) const
{
	if (_capacity <= 0 || _capacity > 10)
		throw "Incorrect capacity";
}

inline void Depot::isTrainExist(int _trainPos) const
{
	if (!hasTrain(_trainPos))
		throw "Train is not on the depot";
}

inline void Depot::isTrainNotExist(int _trainPos)const
{
	if (hasTrain(_trainPos))
		throw std::logic_error( "Train is already on the depot" );
}

inline void Depot::isCarriageExist(int _pos) const
{
	if (_pos == -1)
		throw "Carriage is not exist";
}

inline void Depot::nonpositiveNumber(int _number) const
{
	if (_number < 1)
		throw "Incorrect namber of train";
}