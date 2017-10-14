
#include <string>
#include "Human.h"

Human::Human(std::string _Name)
	:m_Name(_Name), m_beginStation("indefined"), m_endStation("indefined") {}

Human::Human(std::string _Name, std::string _beginStation, std::string _endStation)
	: m_Name(_Name), m_beginStation(_beginStation), m_endStation(_endStation) {}

std::string Human::getName()
{
	return m_Name;
}

std::string Human::getBeginStation()
{
	return m_beginStation;
}

std::string Human::getEndStation()
{
	return m_endStation;
}
