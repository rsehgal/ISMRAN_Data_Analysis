#include <iostream>
#include "TSystem.h"
#include "TString.h"

int main() {
    const char* directory_path = "/home/rsehgal/PS5_S2AB1006"; // Replace with the actual directory path.
    const char* file_pattern = ".*\\.root"; // Replace with the desired regular expression pattern.

    TSystemDirectory dir(directory_path, directory_path);
    TList* filesList = dir.GetListOfFiles();

    if (filesList) {
        TSystemFile* file;
        TString filename;
        TIter next(filesList);
        while ((file = (TSystemFile*)next())) {
            filename = file->GetName();
            if (filename.Contains(file_pattern)) {
                std::cout << filename.Data() << std::endl;
            }
        }
    }

    return 0;
}

