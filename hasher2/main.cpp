#include <iomanip>
#include <sstream>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstring>

#include "openssl/sha.h"
#include <openssl/md5.h>

#include "readcsv.cpp"
using namespace std;


void md5(const std::string& srcStr, std::string& encodedStr,
         std::string& encodedHexStr)
{
    // call md5 hash
    unsigned char mdStr[33] = {0};
    MD5((const unsigned char*)srcStr.c_str(), srcStr.length(), mdStr);

    // hashed string
    encodedStr = std::string((const char*)mdStr);
    // The hashed hexadecimal string 32 bytes
    char buf[65] = {0};
    char tmp[3] = {0};
    for (int i = 0; i < 32; i++)
    {
        sprintf(tmp, "%02x", mdStr[i]);
        strcat(buf, tmp);
    }
    buf[32] = '\0'; // followed by 0, truncated from 32 bytes
    encodedHexStr = std::string(buf);
}

string output = "";

string to_hex(unsigned char s)
{
    stringstream ss;
    ss << hex << (int) s;
    return ss.str();
}

string sha256(string line)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, line.c_str(), line.length());
    SHA256_Final(hash, &sha256);

    string output = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        output += to_hex(hash[i]);
    }
    return output;
}


int main()
{

    vector<string> emailsFirst;
    std::vector<struct Record> my_records;
    readCsvToVec("../TestHash.csv", my_records);

    for (const auto i : my_records)
    {
        cout << i.email << " " << endl;
    }

    std::string srcText = "Data from the user profiles";


    std::string encryptText;
    std::string encryptHexText;
    // md5
    md5(srcText, encryptText, encryptHexText);
    //  std::cout << "Summary character: " << encryptText << std::endl;
    //std::cout << "Summary string: " << encryptHexText << std::endl;


    //sha 256
    cout << "SHA256" << endl ;
    string strHash{};
    string key{"1863"};
    vector<std::pair <std::string, string>> emailHashPairs;
    for (const auto& i : my_records)
    {
        strHash = sha256(i.email.append(key)) ;
        cout << i.email << " " << strHash << endl;
        emailHashPairs.push_back(std::make_pair(i.email, strHash));

    }

    writeCSV("../lastmatches.csv", emailHashPairs);
    return 0;
}
