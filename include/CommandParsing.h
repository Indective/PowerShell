#include <iostream>
#include <vector>

#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

class CommandParsing
{
public:
    std::vector<std::string> tokenize(const std::string &command);
    int check_command_syntax(const std::string &command, const std::vector<std::string> commands);
    void commandsyntax_errormsg(const std::string &command, const std::vector<std::string> commands);
};

#endif