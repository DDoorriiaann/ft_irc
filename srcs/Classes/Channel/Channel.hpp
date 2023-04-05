#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <set>


class Channel
{

public:
	Channel(const std::string& name);
	Channel();
	Channel(const Channel& src);
	~Channel();
	Channel& operator=(Channel const& rhs);

	const std::string& getName() const;
	void join(const std::string& user);
	void leave(const std::string& user);
	bool hasUser(const std::string& user) const;
	void setOperator(const std::string& user);
	bool isOperator(const std::string& user) const;
	size_t operatorCount() const;

	const std::set<std::string>& getUsers() const;

private:
	std::string _name;
	std::set<std::string> _users;
	std::set<std::string> _operators;
};

#endif /* ********************************************************* CHANNEL_H */