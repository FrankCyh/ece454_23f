#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

std::vector<std::string> movieNames = {"Inception", "Titanic", "Avatar", "The Shawshank Redemption", "The Godfather"};

std::vector<std::string> sentences = {
    "I recently watched Inception, and it blew my mind!",
    "What are your thoughts on Titanic? I found it captivating.",
    "A classic movie night with friends - we decided to rewatch Avatar.",
    "Can you believe The Shawshank Redemption was released over two decades ago?",
    "The Godfather remains one of my all-time favorite films.",
};

std::vector<std::string> randomLines = {
    "The weather is beautiful today.",
    "I went to the park and saw a rainbow.",
    "Learning new programming languages is exciting.",
    "Cooking is a great way to relax after a long day.",
    "I can't believe it's already the end of the month.",
};

std::string getRandomSentence(const std::string& movieName) {
    return sentences[rand() % sentences.size()];
}

std::string getRandomLine() {
    return randomLines[rand() % randomLines.size()];
}

void generateRandomTextFiles(int numFiles = 4, int linesPerFile = 1000) {
    for (int fileIndex = 1; fileIndex <= numFiles; ++fileIndex) {
        std::string filename = "random_movie_text_" + std::to_string(fileIndex) + ".txt";
        std::ofstream outputFile(filename);

        if (!outputFile.is_open()) {
            std::cerr << "Error opening file " << filename << " for writing." << std::endl;
            return;
        }

        for (int lineIndex = 0; lineIndex < linesPerFile; ++lineIndex) {
            if (rand() % 2 == 0) {
                std::string movieName = movieNames[rand() % movieNames.size()];
                std::string sentence = getRandomSentence(movieName);
                outputFile << sentence << std::endl;
            } else {
                std::string randomLine = getRandomLine();
                outputFile << randomLine << std::endl;
            }
        }

        outputFile.close();
        std::cout << "File " << filename << " generated successfully." << std::endl;
    }
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random text files
    generateRandomTextFiles();

    return 0;
}