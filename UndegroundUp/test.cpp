#include <iostream>
#include <cassert>
#include <string>
#include "human.h"
#include "station.h"
#include "carriage.h"
#include "train.h"
#include "depot.h"
#include "Subway_branch.h"
#include "Undeground.h"


int main() {

//	Human * human1 = new Human("Igor");
//	Human *human2 = new Human("Masha", "Sportyvna", "Armiyska");
//	Human *human3 = new Human("Kate", "Sportyvna", "Armiyska");
//
//
//	Station *station1 = new Station( "Sportyvna", 100);
//	Station *station2 = new Station( "Armiyska", 80);
//	Station *station3 = new Station( "Moscovskiy");
//
//
//	assert(human1->getName()=="Igor");
//	assert(human2->getName() == "Masha");
//	/*assert(human2->getBeginStation()=="Sportyvna")
//	assert(human2->getEndStation() == "Armiyska");*/
//
//	assert(station1->getName() == "Sportyvna");
//	assert(station1->getCapacity() == 100);
//
//	assert( station1->getHumansCount()==0) ;
//	station1->addHuman(human1);
//	station2->addHuman(human2);
//
//
//	assert(station1->getHumansCount() == 1);
//	assert(station1->findHuman(*human1)==0);
//	station1->removeHuman(*human1);
//	assert(station1->getHumansCount()==0);
// 
//	
//
//	Carriage * carriage1 = new Carriage(1,1);
//	Carriage * carriage2 = new Carriage(2,1);
//
//	//carriage1->addHuman(*human1);
//	//std::cout << carriage1->findHuman(*human2)<<'\n';
//	//carriage1->removeHuman(*human1);
//	//std::cout << carriage1->getHumansCount() << '\n';
//
//	
//	
//	Train *train1 = new Train(1);
//	train1->addCarriage(carriage1);
//	assert(train1->getNCarriages() == 1);
//	assert(train1->findCarriage(*carriage1)==0);
//	assert(train1->findCarriage(*carriage2)==-1);
//	train1->addCarriage(carriage2);
//	assert(train1->getNCarriages() == 2);
//	train1->removeCarriage(1);
//	assert(train1->getNCarriages() == 1);
//
//
//	train1->addHuman(*human1, 1);
//	train1->addCarriage(carriage1);
//	train1->addHuman(*human2);
//	
//	assert(carriage1->getHumansCount()==1);
//	assert(carriage2->getHumansCount()==1);
//
//	station1->arrivedLeft(*train1);
//	assert(station1->hasArrivedLeft()==true);
//	assert(station1->getComeLeft() == 1);
//    station1->departureLeft();
//	assert(station1->hasArrivedLeft()==false);
//	
//	assert(train1->getHumansCount() == 2);
////	train1->removeHuman(*human1);
////	assert(train1->getHumansCount() == 1);
//
//
//	Depot * depot1 = new Depot(1);
//	depot1->addTrain(1, 2);
//	assert(depot1->findTrain(1) == 0);
//	depot1->addCarriage(1, 2);
//	assert(depot1->findCarriage(1) == 0);
//	assert(depot1->getCarriagesCount() == 1);
//	assert(depot1->getTrainsCount() == 1);
//	depot1->addCarriageToTrain(1, 1);
//	assert(depot1->findCarriage(1) == -1);
//	assert(depot1->findTrain(1) == 0);
//	assert(depot1->getCarriagesCount() == 0);
//	assert(depot1->getNCarriages(1) == 1);
//	depot1->unfastenCarriage(1, 1);
//	assert(depot1->findCarriage(1) == 0);
//	assert(depot1->getCarriagesCount() == 1);
//	assert(depot1->getNCarriages(1) == 0);
//	depot1->addCarriageToTrain(1, 1);
//
//
//
//
//	SubwayBranch *branch1 =new SubwayBranch("1") ;
//
//	assert(branch1->hasDepot() == false);
//	branch1->addStation(station1);
//	assert (branch1->getStationsCount()==1);
//	branch1->addStationIntoPos(station2, 1);
//	assert(branch1->getStation(1).getName()==station2->getName());
//	assert( branch1->getStation(2).getName()==station1->getName());
//	assert( branch1->getStationsCount()==2);
//	std::string a="Traktornyy";
//	std::string b = "Sportyvna";
//	branch1->addStationIntoPos(a, 10, 1);
//	assert(branch1->getStation(1).getName() == a);
//	assert(branch1->getStation(2).getName() == station2->getName());
//	assert(branch1->getStation(3).getName() == station1->getName());
//	assert(branch1->findStation(a) == 0);
//	branch1->addDepot(*depot1);
//	assert(branch1->hasDepot() == true);
//
//
//	depot1->addTrain(2);
//	depot1->addCarriage(2);
//	depot1->addCarriageToTrain(2, 2);
//	assert(depot1->getTrainsCount()==2);
//	branch1->addTrainToBranch(2, b);
//	station1->addHuman(human1);
//	std::string Name = "Igor";
//	std::string Platform = "Left";
//	station1->moveHumanToTrain(Name, Platform);
//	assert(station1->getHumansCount() == 0);
//	Train * _ptrain = station1->getTrain(2);
//	assert(_ptrain->getHumansCount()==1);
//	std::string c = "Armiyska";
//	branch1->MoveTrain(2, c);
//	Train * _ptrain1 = station2->getTrain(2);
//	assert(_ptrain1->getNumber()==2);
//	branch1->MoveTrain(2, a);
//	branch1->moveHumanFromTrainToStation(Name, a);
//	branch1->removeTrainIntoDepot(2);
//	
//	/*branch1->removeDepot();
//	assert(branch1->hasDepot()==false);*/
//	
//		
//	delete depot1;
//	delete branch1;
//	delete train1;
//	delete human1;
//	delete human2;
////	delete station1;
////	delete station2;
//	delete carriage1;
//






	Undeground * undeground = new Undeground();
	undeground->createBranch("Feline");
	undeground->createBranch("Addict", 2);	
	//undeground->createBranch("Feline", 1);
	//undeground->createBranch("Biaka", 11);
	assert(undeground->getBranchesCount() == 2);
	assert(undeground->findBranch("Feline") == 0);
	assert(undeground->findBranch("Addict") == 1);
	assert(undeground->getBranchName(0) == "Feline");
	assert(undeground->getBranchName(1) == "Addict");
	assert(undeground->getBranchMaxStations("Feline") == 10);
	//undeground->removeBranch("Feline");
	//undeground->removeBranch("Felinee");
	
	
	undeground->addStationToBranch("Mmr", "Feline");
	undeground->addStationToBranch("Paws", "Feline");
	undeground->addStationToBranch("Tail", "Feline");
	assert(undeground->getStationCount("Feline") == 3);
	
	//undeground->removeBranch("Feline");
		
	undeground->createDepot(1);
	undeground->addDepotToBranch(1, "Feline");
	//	undeground->addDepotToBranch(1, "Felinse");
	//undeground->addDepotToBranch(1, "Feline");
	//	undeground->createDepot(1);
	undeground->createDepot(2);
	//	undeground->addDepotToBranch(2, "Feline");
	//undeground->removeDepot(1);
	undeground->removeDepotFromBranch(1, "Feline");
	undeground->removeDepot(1);
	//	undeground->removeDepot(3);

	undeground->addCarriageToDepot(1, 2);	
	undeground->addCarriageToDepot(2, 2);
	//undeground->addCarriageToTrain(1, 1);
	//	undeground->addCarriageToDepot(1, 2);
	//undeground->addCarriageToDepot(1,1);
	undeground->addTrainToDepot(1, 2);
	//undeground->addTrainToDepot(1, 2);
	undeground->addTrainToDepot(2, 2);

	//undeground->addCarriageToTrain(3, 1);
	//undeground->addCarriageToTrain(1, 1);
	undeground->addCarriageToTrain(2, 2);
	undeground->removeCarriageFromTrain(2,2);
	//undeground->removeCarriageFromTrain(1, 2);
	//undeground->removeCarriageFromTrain(2, 1);
	//	undeground->addTrainToBranch(1, "Feline", "Mmr");
	undeground->addDepotToBranch(2, "Feline");
	undeground->addCarriageToTrain(1, 1);
	undeground->addTrainToBranch(1, "Feline", "Mmr");
	//undeground->addCarriageToTrain(1, 1);
	//undeground->removeDepotFromBranch(1, "Feline");
	//undeground->removeDepotFromBranch(2, "Feline");
	//undeground->removeCarriageFromTrain(1, 1);


	//undeground->addHumanToTrain("Divchata", "right");
	//undeground->addHumanToStation("Hloptci", "Mrr");

	undeground->createHuman("Murchyk");
	undeground->createHuman("Pushok");
	undeground->addHumanToStation("Murchyk", "Mmr");
	//undeground->addHumanToStation("Murchyk", "Mmr");
	//undeground->addHumanToStation("Murchyk", "Mrr");
	//undeground->addHumanToTrain("Murchyk", "left");
	undeground->addHumanToTrain("Murchyk", "right");
	undeground->addTrainToStation(1, "Paws");
	/*try 
	{
		undeground->addHumanToTrain("Pushok", "right", 1);
		assert(false);
	}
	catch (std::logic_error &_e)
	{
		assert(strcmp(_e.what(), "This operation is impossible"));
	}*/
	
	undeground->addHumanToStation("Pushok", "Paws");
	undeground->addHumanToTrain("Pushok", "right", 1);
	undeground->moveHumanFromTrainToStation("Murchyk","Paws");

	undeground->addTrainToStation(1, "Tail");
	//try
	//{
	//	undeground->addTrainToDepot(1,1);

	//	assert(false);
	//}
	//catch (std::logic_error & _e)
	//{
	//	assert( strcmp( _e.what(), "" ) );
	//}
	undeground->moveHumanFromTrainToStation("Pushok", "Tail");
	undeground->removeHumanFromStation("Pushok");
	undeground->removeTrainFromBranch(1, "Feline");
	
	

	delete undeground;

}

