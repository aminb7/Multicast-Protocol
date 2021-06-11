#include "../include/Utilities.h"

using namespace std;

vector<string> split(const string& s, char delimiter) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
      tokens.push_back(token);
   return tokens;
}

std::vector<std::pair<string, string>> store_csv_as_map(string filename) {
    std::ifstream fin(filename);

    std::vector<std::pair<string, string>> table;

    if (!fin) { 
        std::cout << "Error, could not open file." << std::endl; 
        return table;
    }

    std::string first, second;
    string comma = ",";
    while (fin >> first >> comma >> second) {
        table.push_back(make_pair(first, second));
    }

    fin.close();

    for (auto & row : table) {
        std::cout << row.first << " " << row.second << std::endl;
    }

    return table;
}

std::string read_file_to_string(std::string file_path) {
    std::ifstream t(file_path);
    std::string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}
