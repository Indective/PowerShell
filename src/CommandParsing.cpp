#include "CommandParsing.h"
#include <iostream>
#include <vector>
#include <iomanip> // for std::quoted
#include <sstream>

std::vector<std::string> CommandParsing::tokenize(const std::string &command)
{
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;

    while (iss >> std::quoted(token)) {
        tokens.push_back(token);
    }

    return tokens;
}

int CommandParsing::check_command_syntax(const std::string &command, const std::vector<std::string> commands)
{
    // 0 : no error, correct command syntax
    // 1 : unkown command
    // 2 : no positional argument

    std::vector<std::string> tokens = tokenize(command);
    bool command_found = false;

    for (auto commmand : commands)
    {
        if(tokens[0] == command) // Validate command : tokens[0] must match a known command
        {
            command_found = true;
        }
    }
    if(command_found && !tokens[2].empty())
    {
        return 0;
    }
    else if (!command_found)
    {
        return 1;
    }
    else if(tokens[2].empty())
    {
        return 2;
    }
    
}

void CommandParsing::commandsyntax_errormsg(const std::string &command, const std::vector<std::string> commands)
{
    int error_type = check_command_syntax(command,commands);
    if (error_type == 1)
    {
        std::cerr << "Unkown command" << std::endl;
    }
    else if (error_type == 2)
    {
        std::cerr << "Command Does Not Contain a Postional Argument." << std::endl;
    }
}
