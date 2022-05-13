#include "invoker.hpp"
#include "select.hpp"

#include "ping.hpp"
#include "nick.hpp"

namespace irc {


Invoker::Invoker() {
	_commands.push_back(new Ping());
	_commands.push_back(new Nick());
}

Invoker::~Invoker() {
	std::vector<Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++) {
		delete *it;
	}
}

std::string Invoker::parser(std::vector<std::string> Buff, User * user, Select *select)
{
    // commands["NICK"] = cmd_nick._nick;
    // std::vector<std::string>::iterator it = Buff.begin();
    // for(;it != Buff.end(); it++) {
    //     std::vector<std::string> cmd = irc::ft_split(*it, " ");
    //     if  (commands.find(cmd[0]) != commands.end())
    //     {
    //         //std::cout << "cmd:" << (commands[cmd[0]](*it, user))<<std::endl;
    //         return (commands[cmd[0]](*it, user, select));
    //     }
    // }
    // return ("invalid command");

    std::vector<std::string>::iterator it = Buff.begin();
    for(;it != Buff.end(); it++) {
        std::vector<std::string> cmd = irc::ft_split(*it, " ");
        for (std::vector<Command*>::iterator i = _commands.begin(); i != _commands.end(); i++)
        {
            if (cmd[0] == (*i)->getName())
                return((*i)->execute(*it, user, select));
        }
    }
        
    // }
    return ("command not found");
}

}