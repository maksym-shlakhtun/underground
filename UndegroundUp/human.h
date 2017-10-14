#ifndef		HUMAN_H
#define		HUMAN_H

#include <string>

//уникальность
//указатель на станцию, на вагон. методы ссоответственно

class Human
{
public:
	Human(std::string const &_Name);
	Human(std::string const & _Name, std::string const & _beginStation, std::string const &_endStation);
	Human(const Human & _human) = delete;
	Human operator = (const Human & _human) = delete;
	
	std::string const & getName();
	std::string const & getBeginStation();
	std::string const & getEndStation();


private:
	std::string const & m_Name;
	std::string const & m_beginStation;
	std::string const & m_endStation;
	
};

#endif