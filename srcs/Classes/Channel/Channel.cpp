#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Channel::Channel() {}

Channel::Channel(const Channel& src)
{
	*this = src;
}

Channel::Channel(const std::string& name): _name(name) {}



/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel& Channel::operator=(Channel const& rhs)
{
	if (this != &rhs)
	{
		std::set<std::string> usersCopy(rhs.getUsers());
		std::set<std::string> operatorsCopy(rhs.getOperators());
		this->_name = rhs._name;
		this->_users = usersCopy;
		this->_operators = operatorsCopy;
	}
	return *this;
}



/*
** --------------------------------- METHODS ----------------------------------
*/

////// REGULAR USERS FUNCTIONS ///////

const std::string& Channel::getName() const {
	return _name;
}

void Channel::join(const std::string& user) {
	_users.insert(user);
}

void Channel::leave(const std::string& user, const bool isOperator) {
	_users.erase(user);
	if (isOperator)
		_operators.erase(user);
}

bool Channel::hasUser(const std::string& user) const {
	return _users.find(user) != _users.end();
}

const std::set<std::string>& Channel::getUsers() const {
	return _users;
}

/////// OPERATORS ///////

void Channel::setOperator(const std::string& user) {
	_operators.insert(user);
}

void Channel::unsetOperator(const std::string& user) {
	_operators.erase(user);
}

bool Channel::isOperator(const std::string& user) const {
	return _operators.find(user) != _operators.end();
}

size_t Channel::operatorCount() const {
	return _operators.size();
}

const std::set<std::string>& Channel::getOperators() const {
	return _operators;
}


////// KICK USERS //////

void Channel::clearUsers()
{
	_users.clear();
}

void Channel::kickUser(const std::string& user) {
	_users.erase(user);
}


/* ************************************************************************** */