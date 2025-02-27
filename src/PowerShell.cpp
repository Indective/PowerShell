#include "PowerShell.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <windows.h>

namespace fs = std::filesystem;


void powershell::createDirectory(const std::string& dirName) {
    try {
        if (fs::create_directory(dirName)) {
            std::cout << "Directory created: " << dirName << "\n";
        } else {
            std::cout << "Directory already exists or failed to create.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::changeDirectory(const std::string& path) {
    try {
        fs::current_path(path);
        std::cout << "Changed directory to: " << fs::current_path() << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::newfile(std::string filename) 
{   
    std::string text;
    std::ofstream outfile(filename);
    
    std::cout << "Enter your text in the new file: \n";
    std::getline(std::cin , text);
    
    outfile << text << std::endl;
    outfile.close();

}

void powershell::editfile(const std::string filename){
    std::fstream file;

    file.open(filename, std::ios::in | std::ios::out);

    if (!file) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    std::cout << "Current content of the file:\n";
    
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.clear();
    file.seekp(0, std::ios::beg);

    std::cout << "\nEnter new content (type END on a new line to finish):\n";
    std::string newContent;
    file.clear();  
    file.seekp(0, std::ios::beg); 

    while (true) {
        getline(std::cin, newContent);
        if (newContent == "END") break;
        file << newContent << std::endl;
    }

    file.close();
}
   
void powershell::removeFile(std::string filename)
{
  if( remove((filename).c_str()) != 0 )
     perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
}

void powershell::changeColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    int colorAttribute = (bgColor << 4) | textColor;

    SetConsoleTextAttribute(hConsole, colorAttribute);
}

void powershell::removeDirectory(const std::string dirname)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dirname)) {
        std::filesystem::remove(entry);
    }
    std::filesystem::remove(dirname);
}

void powershell::showDirectory(const std::string dirname)
{
    try{
        for (auto const& dir_entry : fs::directory_iterator{dirname})
        {
            std::cout << dir_entry.path() << '\n';
        }
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::searchfile(const std::string dirname)
{
    std::string filename = "";
    std::cout << "\nEnter file name : ";
    std::getline(std::cin, filename);
    try{
        for (auto const& dir_entry : std::filesystem::directory_iterator{dirname})
        {
            if (dir_entry.exists())
            {
                std::cout << "File found in : " << dirname;
            }
        }
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::showfilesize(const std::string filename)
{
    try{
        std::cout << "File size : " << fs::file_size(filename) << " bytes.";
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::showdirsize(const std::string dirname)
{
    int total = 0;
    std::cout << dirname;
    try{
        for (auto const& dir_entry : std::filesystem::directory_iterator{dirname})
        {
            total = total + dir_entry.file_size();
            std::cout << "\n" << dir_entry << " size : " << dir_entry.file_size() << " bytes.";
        }
        std::cout << "\n" << "Total folder size : " << total;
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::copyfile(const std::string filename)
{
    std::string new_filenmae = "";
    std::cout << "Enter the directory to copy the file to : ";
    std::getline(std::cin, new_filenmae);
    try{
        fs::copy(filename, new_filenmae);
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::renamefile(const std::string filename)
{
    std::string new_filenmae = "";
    std::cout << "Enter the new name for the file : ";
    std::getline(std::cin, new_filenmae);
    try{
        fs::rename(filename, new_filenmae);
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

