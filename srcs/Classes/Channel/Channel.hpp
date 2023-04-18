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
	void setTopic(const std::string& topic);
	void setTopicProtection();
	bool isTopicProtected() const;
	void unsetTopicProtection();
	void invite(const std::string& user);
	void uninvite(const std::string& user);
	void setInviteOnly();
	void unsetInviteOnly();
	bool isInviteOnly() const;
	bool isInvited(const std::string& user) const;
	const std::string& getTopic() const;
	const std::set<std::string>& getUsers() const;
	const std::set<std::string>& getOperators() const;

private:
	std::string _name;
	std::string _key;
	std::string _topic;
	int _limit;
	bool _isKeyProtected;
	bool _isTopicProtected;
	bool _isInviteOnly;
	std::set<std::string> _invitedUsers;
	std::set<std::string> _users;
	std::set<std::string> _operators;
};

#endif /* ********************************************************* CHANNEL_H */