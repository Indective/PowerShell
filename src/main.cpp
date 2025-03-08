#include "PowerShell.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <vector>
powershell organizer;
namespace fs = std::filesystem;

int main() 
{

    time_t timestamp;
    time(&timestamp);

    std::vector<std::string> commands = {"cd","mkdir","newfile","removefile","editfile","COLOR","showdir","removedir",
    "searchfile","dirsize","exit","date","cls","filesize","dupfile","renamefile","tasklist","taskkill","pininfo","dupdir","help"};

    std::vector<std::string> commands_exp = {"chnages directory","creates a new directory"
    ,"creates a new .txt file","removes a pre-existing .txt file",
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
    int textcolor;
    int bgcolor; 
    int command_code = -1;
    int total = 0;
    while (true) {

        std::cout << "\n" <<  fs::current_path() <<  "> ";
        std::getline(std::cin, command);

        if (command.substr(0,5) == "mkdir") command_code = 0;
        else if (command.substr(0,2) == "cd") command_code = 1;
        else if (command.substr(0,7) == "newfile") command_code = 2; 
        else if (command.substr(0,8) == "editfile") command_code = 3;
        else if (command.substr(0,10) == "removefile") command_code = 4;
        else if (command.substr(0,5) == "COLOR") command_code = 5;
        else if (command.substr(0,7) == "showdir") command_code = 6;
        else if (command.substr(0,9) == "removedir") command_code = 7;
        else if (command.substr(0,10) == "searchfile") command_code = 8;
        else if (command.substr(0,7) == "dirsize") command_code = 9;
        else if (command.substr(0,7) == "exit") command_code = 10;
        else if (command.substr(0,4) == "date") command_code = 11;
        else if (command.substr(0,3) == "cls") command_code = 12;
        else if (command.substr(0,8) == "filesize") command_code = 13;
        else if (command.substr(0,8) == "dupfile") command_code = 14;
        else if (command.substr(0,10) == "renamefile") command_code = 15;
        else if (command.substr(0,4) == "help") command_code = 16;
        else if (command.substr(0,8) == "tasklist") command_code = 17;
        else if (command.substr(0,8) == "taskkill") command_code = 18;
        else if (command.substr(0,8) == "pininfo") command_code = 19;
        else if(command.substr(0,6) == "dupdir") command_code = 20;
        else command_code = -1;

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
                filename = command.substr(11);
                organizer.removeFile(filename);
                break;
            case 5:
                std::cout << "List of colors (Foreground & Background) \n";
                std::cout << "0 = Black, 1 = Blue, 2 = Green, 3 = Aqua, 4 = Red, 5 = Purple, \n";
                std::cout << "// 6 = Yellow, 7 = White, 8 = Gray, 9 = Light Blue, 10 = Light Green, \n";
                std::cout << "// 11 = Light Aqua, 12 = Light Red, 13 = Light Purple, 14 = Light Yellow, 15 = Bright White \n";

                std::cout << "Enter text color : ";
                std::cin >> textcolor;

                std::cout << "\nEnter Background color : ";
                std::cin >> bgcolor;

                organizer.changeColor(textcolor, bgcolor);
                break;
            case 6:
                if (command.length() < 8) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                dirname = command.substr(8);
                organizer.showDirectory(dirname);
                break;
            case 7:
                if (command.length() < 10) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                dirname = command.substr(10);
                organizer.removeDirectory(dirname);
                break;
            case 8:
                if (command.length() < 11) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                dirname = command.substr(11);
                std::cout << "Enter file Name to search : ";
                std::getline(std::cin, filename);
                organizer.searchfile(dirname,filename);
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
                filename = command.substr(9);
                organizer.showfilesize(filename);
                break;
            case 14:
                if (command.length() < 9) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                filename = command.substr(9);
                organizer.dupfile(filename);
                break;
            case 15:
                if (command.length() < 11) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                filename = command.substr(11);
                organizer.renamefile(filename);
                break;
            case 16:
                for(int i = 0; i < commands.size(); i ++){
                    std::cout << commands[i] << " - " << commands_exp[i] << std::endl;
                }
                break;
            case 17:
                organizer.listProcesses();
                break;
            case 18:
                std::cout << "Enter the name of the process: ";
                std::cin >> filename;
                organizer.killProcess(filename);
                break;
            case 19:
                unsigned long pid;
                std::cout << "Enter PID : ";
                std::cin >> pid;
                organizer.printProcessInfo(pid);
                break;
            case 20:
                if (command.length() < 7) {
                    std::cout << "Error : Command syntax error \n";
                    break;
                }
                dirname = command.substr(7);
                organizer.dupdir(dirname);
                break;
            default:
                std::cout << "Unknown command.\n";
                break;
        }
    }


    return 0;
}
