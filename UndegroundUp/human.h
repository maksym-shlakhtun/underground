#ifndef		HUMAN_H
#define		HUMAN_H

#include <string>

//уникальность
//указатель на станцию, на вагон. методы ссоответственно

class Human
{
public:
	Human(std::string _Name);
	Human(std::string _Name, std::string _beginStation, std::string _endStation);
	Human(const Human & _human) = delete;
	Human operator = (const Human & _human) = delete;
	~Human() {};
	//void comeStation(Station _station);
	//void uncomeStation(Station _station);
	//void comeTrain(Train _train);
	//void uncomeTrain(Train _train);
	std::string getName();
	std::string getBeginStation();
	std::string getEndStation();


private:
	std::string m_Name;
	std::string m_beginStation;
	std::string m_endStation;
	
};

#endif