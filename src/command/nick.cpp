#include "nick.hpp"

//英文字母，數字
namespace irc {

Nick::Nick() {
	_name = "NICK";
}
Nick::~Nick() {}

//ERR_NICKNAMEINUSE :aleardy use in user
bool	Nick::nickinUse(std::string name, std::vector<User *> users) {
	std::vector<User *>::iterator it = users.begin();
	for(; it != users.end(); it++)
		if ((*it)->getNickname() == name)
			return true;
	return false;
}


//ERR_ERRONEUSNICKNAME: erro nickname
bool	Nick::nameError(std::string name){
	if(name.length() > MAX_SIZE)
		return false;
		
	for(size_t i = 0; i < name.size(); i++){
		if (!isalnum(name[i]))
			return false;
	}
	return true;
}

std::string	Nick::execute(std::string line, User *user, Select &select) {
	std::string msg;
	std::vector<std::string> v_cmd = ft_split(line, " ");
	std::cout <<"command is: " << v_cmd[0] << std::endl;
	std::cout <<"command is: " << v_cmd[1] << std::endl;
	std::string newnick = v_cmd[1];
	

	//ERR_ERRONEUSNICKNAME: erro nickname
	if (nameError(newnick) == false) {
		 msg = ERR_ERRONEUSNICKNAME(newnick);
		 msg += delimiter;
		 return msg;
	}
	//RR_NONICKNAMEGIVEN: don t nickname given
	if (v_cmd.size() != 2 || newnick.length() == 0) {
		std::cout << v_cmd.size() << std::endl;
		msg = ERR_NONICKNAMEGIVEN;
		msg += delimiter;
		return msg;
	}
	//ERR_NICKNAMEINUSE :aleardy use in user
	if (nickinUse(newnick, select.getUsers()) == true) {
		msg = user->getHostname() + " 433 " + user->getNickname() + " " + newnick + " :Nickname is already in use" + "\r\n";
		return msg;
			// msg = ERR_NICKNAMEINUSE(newnick);
			// msg += delimiter;
	}

    msg = user->getPrefix() + " NICK " + newnick + delimiter;//tmd
	select.sendReply(msg, *user);
    user->setNickname(newnick);
	return msg;
}

}