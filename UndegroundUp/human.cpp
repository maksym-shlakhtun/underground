#include "Human.h"

#include <string>

Human::Human(std::string const & _Name)
	:m_Name(_Name) {}

std::string const & Human::getName() const
{
	return m_Name;
}

