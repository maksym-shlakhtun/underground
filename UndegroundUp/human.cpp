
#include <string>
#include "Human.h"

Human::Human(std::string const & _Name)
	:m_Name(_Name) {}

std::string const & Human::getName()
{
	return m_Name;
}

