#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
    (void)av;
    (void)ac;

    // if (ac != 3)
    // {
    //     std::cout << "./ircserv <port> <password>" << std::endl;
    //     return (1);
    // }

    irc::Select select;
    select.serverStart();
    return (0);
}

//----users
//----#channel
//----commandes