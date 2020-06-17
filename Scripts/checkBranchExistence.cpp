#include<iostream>
#include<fstream>
#include<dirent.h>

vector<string> get_files(const char *path) {
    // Recursively list all files in a folder, and return in a vector of strings.
    vector<string> files = {};
    DIR *dir = opendir(path);
    while (dirent *pdir = readdir(dir)) {
        if ((strcmp(pdir->d_name, ".")==0) || (strcmp(pdir->d_name, "..")==0) ||
                (strcmp(pdir->d_name, "merged")==0)) continue;
        char dir_name[300];
        strcpy(dir_name, path);
        strcat(dir_name, "/");
        strcat(dir_name, pdir->d_name);
        string string_name = string(dir_name);
        if (pdir->d_type == DT_DIR) {
            vector<string> child_files = get_files(dir_name);
            files.insert(end(files), begin(child_files), end(child_files));
        }
        else if (string_name.compare(string_name.size()-5,5,".root") == 0) {
            files.push_back(string_name);
        }
    }
    return files;
}

void write_files(vector<string> filenames) {
    // Write all found files to an output file.
    ofstream out_file;
    out_file.open("files.txt");
    for (auto file : filenames)
        out_file << file << endl; 
    out_file.close();
}

void checkBranchExistence() {
    const char *path = "/eos/user/m/mazhang/Temp/LHE/";
    vector<string> files = get_files(path);
    write_files(files);
    ofstream has_branch_file, no_branch_file;
    has_branch_file.open("has_branch.txt");
    no_branch_file.open("no_branch.txt");
    for (auto file : files) {
        cout << file << endl;
        TFile *new_file = new TFile(file.c_str());
        TTree *new_tree = (TTree*)new_file->Get("tree_NoSys");
        if (new_tree->GetBranch("LHE3Weight_MUR2_MUF1_PDF261000") != 0)
            has_branch_file << file << endl;
        else
            no_branch_file << file << endl;
    }
    has_branch_file.close();
    no_branch_file.close();
}
