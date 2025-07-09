#include<iostream>
#include <vector>

#ifndef POWERSHELL_H
#define POWERSHELL_H

// Declare the FileOrganizer class and its functions here
class powershell {
public:

    void createDirectory(const std::string dirName);
    void changeDirectory(const std::string path);
    void newfile(const std::string filename);
    void editfile(const std::string filename);
    void removeFile(const std::string filename);
    void removeDirectory(const std::string dirname);
    void showDirectory(const std::string dirname);
    void searchfile(const std::string filename);
    void showfilesize(const std::string filename);
    int showdirsize(const std::string dirname);
    void dupfile(const std::string filename);
    void renamefile(const std::string filename);
    void dupdir(const std::string dirname);
    void exit();
    void showDate();
    void cls();
    void showHelp(std::vector<std::string> &commands, std::vector<std::string> &descriptions);

};

#endif
