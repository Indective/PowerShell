// make cls cross platform
// showdir = dir
// removedir = rmd
// newfile = nf
// removefile = rmf
// newfile = nf
// complete command parsing
// complete missing commands (cls, dirsize, help)

#include "PowerShell.h"
#include "CommandParsing.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <functional>

namespace fs = std::filesystem;

int main() 
{
    powershell organizer;
    CommandParsing parser;
    std::string command; 
    std::string filename;
    std::string new_filename;
    std::string dirname;
    std::string path;

    std::vector<std::string> commands = {"cd","mkdir","nf","rmf","editfile","dir","rmdir",
    "searchfile","dirsize","exit","date","cls","filesize","dupfile","renamefile","dupdir","help"};

    std::vector<std::string> commands_exp = {"chnages directory","creates a new directory"
    ,"creates a new .t'xt file","removes a pre-existing .txt file",
    "edits a pre-existing .txt file","changes foreground and background color",
    "lists all files or subdirectories in directory","deletes a directory",
    "searches for file in directory."
    ,"Show the size of all files in a directory and the size of the directory itself."
    ,"Terminate programm."
    ,"shows the size of a file.","clears the screen.","shows the current date and time."
    ,"dups a file.","renames a file."
    ,"lists all running processes.","kills a running process."
    ,"shows information about a running process.","dups a directory."
    ,"lists all commands with explantions"};

    std::unordered_map<std::string, std::function<void(const std::string)>> command_map = {
        {"cd",         [&](const std::string arg) { organizer.changeDirectory(arg); }},
        {"mkdir",      [&](const std::string arg) { organizer.createDirectory(arg); }},
        {"nf",         [&](const std::string arg) { organizer.newfile(arg); }},
        {"rmf",        [&](const std::string arg) { organizer.removeFile(arg); }},
        {"editfile",   [&](const std::string arg) { organizer.editfile(arg); }},
        {"dir",        [&](const std::string arg) { organizer.showDirectory(arg); }},
        {"rmdir",      [&](const std::string arg) { organizer.removeDirectory(arg); }},
        {"searchfile", [&](const std::string arg) { organizer.searchfile(arg); }},
        {"date",       [&](const std::string)     { organizer.showDate(); }},
        {"filesize",   [&](const std::string arg) { organizer.showfilesize(arg); }},
        {"dupfile",    [&](const std::string arg) { organizer.dupfile(arg); }},
        {"renamefile", [&](const std::string arg) { organizer.renamefile(arg); }},
        {"dupdir",     [&](const std::string arg) { organizer.dupdir(arg); }},
        {"exit",       [&](const std::string)     { organizer.exit(); }},
        {"cls",        [&](const std::string)     { organizer.cls(); }},
    };

    std::cout << "Welcome to the PowerShell-like shell!\n";
    std::vector<std::string> tokens;
    int command_code = -1;
    while (true) 
    {

        std::cout << "\n" <<  fs::current_path() <<  "> ";
        std::getline(std::cin, command);

        tokens = parser.tokenize(command);
        if (!tokens.empty() && parser.check_command_syntax(command, commands) == 0) {
            parser.excute_command(tokens, command_map);
        } else {
            parser.commandsyntax_errormsg(command, commands);
        }
    }
    
    return 0;
}
