#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

class CommandParsing
{
public:
    std::vector<std::string> tokenize(const std::string &command);
    int check_command_syntax(const std::string &command, const std::vector<std::string> commands);
    void commandsyntax_errormsg(const std::string &command, const std::vector<std::string> commands);
    void excute_command(std::vector<std::string> tokens, std::unordered_map<std::string, std::function<void(const std::string)>> command_map);
};

#endif