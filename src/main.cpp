// make cls cross platform
// showdir = dir
// removedir = rmd
// newfile = nf
// removefile = rmf
// newfile = nf
// complete command parsing

#include "PowerShell.h"
#include "CommandParsing.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <vector>

namespace fs = std::filesystem;

int main() 
{

    time_t timestamp;
    time(&timestamp);
    powershell organizer;
    CommandParsing parser;

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

    std::cout << "\n" << "Indective Windows [Version 10.0.19045.4894]" << std::endl;
    std::cout << "(c) Indective Corporation. All rights reserved." << "\n"; 
    std::string command; 
    std::string filename;
    std::string new_filename;
    std::string dirname;
    std::vector<std::string> tokens;
    int command_code = -1;
    while (true) {

        std::cout << "\n" <<  fs::current_path() <<  "> ";
        std::getline(std::cin, command);

        tokens = parser.tokenize(command);
        if(parser.check_command_syntax(command,commands) == 0)
        {
            //Handle commands
        }
        else
        {
            parser.commandsyntax_errormsg(command,commands);
        }

        std::string path;
        std::string dirName;
        switch(command_code){
            case 0:
                if (command.length() < 6) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                dirName = command.substr(6); 
                if (!dirName.empty()) {
                    organizer.createDirectory(dirName);
                } else {
                    std::cout << "Error: No directory name provided.\n";
                }
                break;
            case 1:
                if (command.length() < 3) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                path = command.substr(3); 
                if (!path.empty()) {
                    organizer.changeDirectory(path);
                } else {
                    std::cout << "Error: No path provided.\n";
                }
                break;
            case 2:
                if (command.length() < 8) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                filename = command.substr(8);
                organizer.newfile(filename);
                break;
            case 3:
                if (command.length() < 9) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                filename = command.substr(9);
                organizer.editfile(filename);
                break;
            case 4:
                if (command.length() < 11) {
                    std::cout << "Error : Command syntax error \n";
                    break;
		        }
                else
                {
                    filename = command.substr(11);
                    organizer.removeFile(filename);
                }   
                break;
            case 6:
                if (command.length() < 8) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    dirname = command.substr(8);
                    organizer.showDirectory(dirname);
                }
                break;
            case 7:
                if (command.length() < 10) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    dirname = command.substr(10);
                    organizer.removeDirectory(dirname); 
                }
                break;
            case 8:
                if (command.length() < 10) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    filename = command.substr(11);
                    organizer.searchfile(filename);
                }
                break;
            case 9:
                if (command.length() < 7) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else
                {
                    dirname = command.substr(8);
                    int size = organizer.showdirsize(dirname);
                    std::cout << "Total size of directory : " << size << " bytes.";
                }
                break;
            case 10:
                exit(0);
                break;
            case 11:
                std::cout << ctime(&timestamp);
                break;
            case 12:
                system("cls");
                break;
            case 13:
                if (command.length() < 9) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    filename = command.substr(9);
                    organizer.showfilesize(filename);
                }
                break;
            case 14:
                if (command.length() < 9) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    filename = command.substr(9);
                    organizer.dupfile(filename);
                }
                break;
            case 15:
                if (command.length() < 11) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    filename = command.substr(11);
                    organizer.renamefile(filename);
                }
                break;
            case 16:
                for(int i = 0; i < commands.size(); i ++){
                    std::cout << commands[i] << " - " << commands_exp[i] << std::endl;
                }
                break;
            case 20:
                if (command.length() < 7) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                else{
                    dirname = command.substr(7);
                    organizer.dupdir(dirname);
                }
                break;
            default:
                std::cout << "Unknown command.\n";
                break;
        }
    }


    return 0;
}
