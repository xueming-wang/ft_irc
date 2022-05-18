#include "ping.hpp"
#include "select.hpp"

namespace irc {

Ping::Ping() { _name = "PING";}
Ping::~Ping() {}

std::string	Ping::execute(std::string line, User * user, Select &select) {
    std::string msg;
    (void)user;
    (void)select;

    std::vector<std::string> v_cmd = ft_split(line, " ");
    if (v_cmd.size() < 2) {
        msg = ERR_NOORIGIN;
        msg += delimiter;
        return msg;
    }
    msg = "PONG :" + v_cmd[1] + delimiter;
    // select.sendReply(msg, (*user));
	int ret = -1;

	ret = send(user->getUserFd(), msg.c_str(), msg.length(), 0);
	std::cout<<"ret :"<<ret<<"\nmsg :"<<msg<<std::endl;
	if (ret == SYSCALL_ERR) {
		std::cout << "[Send response failed]" << std::endl;
		select.clientDisconn(user->getUserFd());
		return NULL;
	}
    return msg;
}

} 