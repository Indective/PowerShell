// initializes pre-defined functions in PowerShell.h
// Handels all file logic

#include "PowerShell.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstdlib> // for std::getenv and system()

namespace fs = std::filesystem;

void powershell::createDirectory(const std::string dirName) {
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

void powershell::changeDirectory(const std::string path) {
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
            if (dir_entry.is_directory())
            {   
                std::cout << dir_entry.path() << " [DIR]" << '\n';
                showDirectory(dir_entry.path().string());
            }
            else
            {
                std::cout << dir_entry.path() << " [FILE]" << '\n';
            }
        }
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::searchfile(const std::string filename)
{
    try{
        for (auto const& dir_entry : fs::recursive_directory_iterator{fs::current_path()})
        {
            if (dir_entry.path().filename() == filename)
            {
                std::cout << "File found at : " << dir_entry.path() << std::endl;
                break;
            }
        }
        std::cout << "File not found." << std::endl;
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

int powershell::showdirsize(const std::string dirname)
{
    int total = 0;
    try{
        for (auto const& dir_entry : std::filesystem::directory_iterator{dirname})
        {
            if (dir_entry.is_directory())
            {
                total += showdirsize(dir_entry.path().string());
            }
            else
            {
                total += dir_entry.file_size();
                std::cout << std::endl << dir_entry.path() 
                          << " size : " << dir_entry.file_size() << " bytes." << std::endl;
                std::cout << "Total size : " << total << " bytes." << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    return total;
}

void powershell::dupfile(const std::string filename)
{
    std::string new_filename = "";
    std::cout << "Enter the new file name to copy the file to : ";
    std::getline(std::cin, new_filename);
    try{
        fs::copy_file(filename, new_filename);
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

void powershell::dupdir(const std::string dirname)
{
    std::string new_dirname = "";
    std::cout << "Enter the new directory name : ";
    std::getline(std::cin, new_dirname);
    try{
        fs::copy(dirname, new_dirname);
    }catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void powershell::cls()
{
    #ifdef _WIN32
        if (std::getenv("TERM")) {
            std::cout << "\033[2J\033[H" << std::flush;
        } else {
            system("cls");
        }
    #else
        std::cout << "\033[2J\033[H" << std::flush;
    #endif   
}

void powershell::exit()
{
    exit();
}

void powershell::showDate()
{
    time_t timestamp;
    time(&timestamp);
    
    std::cout << ctime(&timestamp);
}
