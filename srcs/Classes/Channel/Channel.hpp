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
	void leave(const std::string& user, const bool isOperator);
	bool hasUser(const std::string& user) const;
	void setOperator(const std::string& user);
	void unsetOperator(const std::string& user);
	bool isOperator(const std::string& user) const;
	void kickUser(const std::string& user);
	void clearUsers();
	size_t operatorCount() const;
	void setKey(const std::string& key);
	bool isKeyProtected() const;
	void unsetKey();
	std::string getKey() const;
	void setLimit(int limit);
	void unsetLimit();
	int getLimit() const;

	const std::set<std::string>& getUsers() const;
	const std::set<std::string>& getOperators() const;

private:
	std::string _name;
	std::string _key;
	int _limit;
	bool _isKeyProtected;
	std::set<std::string> _users;
	std::set<std::string> _operators;
	std::set<std::string> _kickedUsers;
};

#endif /* ********************************************************* CHANNEL_H */