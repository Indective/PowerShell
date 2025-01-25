#include<iostream>

#ifndef POWERSHELL_H
#define POWERSHELL_H

// Declare the FileOrganizer class and its functions here
class powershell {
public:

    void createDirectory(const std::string& dirName);
    void changeDirectory(const std::string& path);
    void newfile(const std::string filename);
    void editfile(const std::string filename);
    void removeFile(const std::string filename);
    void changeColor(int textColor, int bgColor);
    void removeDirectory(const std::string dirname);
    void dupFile(const std::string filename, const std::string dirname);
    void showDirectory(const std::string dirname);
    void searchfile(const std::string dirname);
    void showfilesize(const std::string filename);
    void showdirsize(const std::string dirname);

};

#endif
