#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>

struct MovieInfo {
    std::string movieName;
    std::string movieInfo;
    MovieInfo* next; // Pointer for linked list
};

std::vector<std::string> movieNames = {"Inception", "Titanic", "Avatar", "The Shawshank Redemption", "The Godfather"};

std::unordered_map<std::string, MovieInfo*> hashTables[4]; // Hash tables for Input1 to Input4

void map(int inputIndex, std::string line, std::string movie_name_input) {
    for(int i = 0; i < movieNames.size(); i++){
        if (line.find(movieNames[i]) != std::string::npos) {
            // Extract movie name and movie info
            std::string movieName, movieInfo;
            movieName = movieNames[i];
            movieInfo = line;

            // Create a new MovieInfo node
            MovieInfo* newNode = new MovieInfo{movieName, movieInfo, nullptr};

            // Insert into the corresponding hash table
            if (hashTables[inputIndex].find(movieName) == hashTables[inputIndex].end()) {
                // If movieName is not in the hash table, create a new entry
                hashTables[inputIndex][movieName] = newNode;
            } else {
                // If movieName is already in the hash table, add to the linked list
                newNode->next = hashTables[inputIndex][movieName];
                hashTables[inputIndex][movieName] = newNode;
            }
            break;
        }
    }
}


void shuffle() {
    // Use Hash1 as the major hash table
    for (int i = 1; i < 4; ++i) {
        for (auto& entry : hashTables[i]) {
            std::string movieName = entry.first;
            MovieInfo* currentNode = entry.second;

            while (currentNode != nullptr) {
                // Create a new MovieInfo node
                MovieInfo* newNode = new MovieInfo{currentNode->movieName, currentNode->movieInfo, nullptr};

                // Insert into the corresponding hash table (Hash1)
                if (hashTables[0].find(movieName) == hashTables[0].end()) {
                    // If movieName is not in Hash1, create a new entry
                    hashTables[0][movieName] = newNode;
                } else {
                    // If movieName is already in Hash1, add to the linked list
                    newNode->next = hashTables[0][movieName];
                    hashTables[0][movieName] = newNode;
                }

                currentNode = currentNode->next;
            }
        }
    }
}

std::unordered_map<std::string, int> reduce() {
    std::unordered_map<std::string, int> countHash;

    // Iterate through Hash1
    for (auto& entry : hashTables[0]) {
        std::string movieName = entry.first;
        MovieInfo* currentNode = entry.second;

        int nodeCount = 0;
        while (currentNode != nullptr) {
            ++nodeCount;
            currentNode = currentNode->next;
        }

        // Insert into the count hash table
        countHash[movieName] = nodeCount;
    }

    return countHash;
}

void processInputFile(int inputIndex, std::string filename, std::string movie_name_input) {
    std::ifstream inputFile(filename);
    std::string line;
    while (std::getline(inputFile, line)) {
        map(inputIndex, line, movie_name_input);
    }

    inputFile.close();
}

int main() {
    // Process each input file
    // std::cout << "Enter Movie Name\n";
    std::string movie_name_input;
    // getline(std::cin, movie_name_input);
    for (int i = 0; i < 4; ++i) {
        std::string filename = "random_movie_text_" + std::to_string(i + 1) + ".txt";
        processInputFile(i, filename, movie_name_input);
    }

    // print after map

    // for (const auto& entry : hashTables[0]) {
    //     std::cout << "Movie Name: " << entry.first << std::endl;
    //     MovieInfo* currentNode = entry.second;
    //     while (currentNode != nullptr) {
    //         std::cout << "  Movie Info: " << currentNode->movieInfo << std::endl;
    //         currentNode = currentNode->next;
    //     }
    // }

    // Merge other hash tables into the major hash table (Hash1)
    shuffle();

    // print after shuffle

    // for (const auto& entry : hashTables[0]) {
    //     std::cout << "Movie Name: " << entry.first << std::endl;
    //     MovieInfo* currentNode = entry.second;
    //     while (currentNode != nullptr) {
    //         std::cout << "  Movie Info: " << currentNode->movieInfo << std::endl;
    //         currentNode = currentNode->next;
    //     }
    // }

    std::unordered_map<std::string, int> countHash = reduce();

    for (const auto& entry : countHash) {
        std::cout << "Movie Name: " << entry.first << ", Count: " << entry.second << std::endl;
    }

    return 0;
}