#include <iomanip>
#include <sstream>
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
struct Record
{
    std::string email;
    //    std::string place;
    //    int age;
    //    double x;
    //    double y;
};

// reads csv firs column, delimiter is comma ","
void readCsvToVec(std::string filename, std::vector<Record> &my_records)
{

    ifstream data(filename.c_str());
    if (!data.is_open())
    {
        exit(EXIT_FAILURE);
    }
    string str;

    while (getline(data, str))
    {
        Record record;
        istringstream iss(str);
        string token;

        getline(iss, record.email, ',');
        // getline(iss, record.place, ',');

        //    // use atoi(token.c_str()) if you don't have std::stoi from C++11
        //    getline(iss, token, ',');
        //    record.age = std::stoi(token);

        //    // use atof(token.c_str()) if you don't have std::stod from C++11
        //    getline(iss, token, ',');
        //    record.x = std::stod(token);

        //    getline(iss, token, ',');
        //    record.y = std::stod(token);

        my_records.push_back(record);
    }


}

void writeCSV( std::string filename, vector<std::pair <std::string, string>> &emailHashPairs)
{

    std::ofstream myFile(filename);

    for (const auto& i : emailHashPairs)
    {


    myFile << i.first << " " << i.second << endl;

    }
}

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<string>>> dataset){
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}
