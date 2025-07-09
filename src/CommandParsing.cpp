#include "CommandParsing.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <functional>

std::vector<std::string> CommandParsing::tokenize(const std::string &command)
{
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int CommandParsing::check_command_syntax(const std::string &command, const std::vector<std::string> commands)
{
    // 0 : no error, correct command syntax
    // 1 : unknown command
    // 2 : no positional argument

    std::vector<std::string> tokens = tokenize(command);

    if (tokens.empty())
        return 1;

    std::string input_command = tokens[0];
    bool command_found = false;

    for (const auto& cmd : commands)
    {
        if (input_command == cmd)
        {
            command_found = true;
            break;
        }
    }

    if (!command_found)
        return 1;

    // Some commands don't need a second argument, so we can relax this check
    // But if you want to enforce an argument:
    if (tokens.size() < 2 || tokens[1].empty())
        return 2;

    return 0;
}

void CommandParsing::commandsyntax_errormsg(const std::string &command, const std::vector<std::string> commands)
{
    int error_type = check_command_syntax(command, commands);

    if (error_type == 1)
    {
        std::cerr << "Unknown command" << std::endl;
    }
    else if (error_type == 2)
    {
        std::cerr << "Command does not contain a positional argument." << std::endl;
    }
}

void CommandParsing::excute_command(std::vector<std::string> tokens, std::unordered_map<std::string, std::function<void(const std::string)>> command_map)
{
    if (tokens.empty()) return;

    std::string command = tokens[0];
    std::string arg = (tokens.size() > 1) ? tokens[1] : "";

    auto it = command_map.find(command);
    if (it != command_map.end())
    {
        it->second(arg);
    }
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}
