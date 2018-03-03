#ifndef		HUMAN_H
#define		HUMAN_H

#include <string>


class Human
{
public:
	Human(std::string const &_Name);
	Human(const Human & _human) = delete;
	Human operator = (const Human & _human) = delete;
	
	std::string const & getName();

private:
	std::string const  m_Name;

};

#endif