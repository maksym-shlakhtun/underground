
#include <string>
#include "Human.h"

Human::Human(std::string const & _Name)
	:m_Name(_Name), m_beginStation("indefined"), m_endStation("indefined") {}

Human::Human(std::string const & _Name, std::string const & _beginStation, std::string const & _endStation)
	: m_Name(_Name), m_beginStation(_beginStation), m_endStation(_endStation) {}

std::string const & Human::getName()
{
	return m_Name;
}

std::string const & Human::getBeginStation()
{
	return m_beginStation;
}

std::string const & Human::getEndStation()
{
	return m_endStation;
}
