#include "functions.h"
#include "lz77.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool validateParams(const CompressionParams &params) {
    return !(params.inputFileName.empty() || params.outputFileName.empty() || params.mode.empty() || params.inputBufferSize <= 0 || params.historyBufferSize <= 0);
}

std::vector<char> readFileContent(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return {};
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> content(fileSize);
    file.read(content.data(), fileSize);
    file.close();

    return content;
}

void writeCompressedData(const std::vector<Token> &compressedData, const std::string &outputFileName) {
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error writing file: " << outputFileName << std::endl;
        return;
    }

    for (const auto &token : compressedData) {
        if(static_cast<int>(token.code_word) != 0)
        {
            outputFile << "<" << token.offset << "," << token.length_of_match << "," << static_cast<int>(token.code_word) << ">";
        }
    }

    outputFile.close();
}

void performCompression(const std::vector<char> &fileContent, const CompressionParams &params) {
    std::string data(fileContent.begin(), fileContent.end());
    std::vector<Token> compressedData = compression_lz77(data, params.inputBufferSize, params.historyBufferSize);
    writeCompressedData(compressedData, params.outputFileName);

    auto startingSize = static_cast<double>(fileContent.size());
    double compressedSize = static_cast<double>(compressedData.size()) * (sizeof(Token) / sizeof(char));
    double compressionRatio = (startingSize / compressedSize) * 100.0;

    std::cout << "Theoretical compression ratio: " << compressionRatio << "%" << std::endl;
    std::cout << "Theoretical compression degree: " << (compressedSize / startingSize) << std::endl;
}

void performDecompression(const std::vector<char> &fileContent, const CompressionParams &params) {
    std::ofstream outputFile(params.outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error writing input file: " << params.outputFileName << std::endl;
        return;
    }

    // Convert the char vector to a string
    std::string input(fileContent.begin(), fileContent.end());
    // Vector to store compressed data
    std::vector<Token> compressedData;
    // Variable to store the current position in the string
    size_t pos = 0;

    // Loop parsing the string and creating tokens
    while (pos < input.size()) {
        // Find the occurrence of the '>' character in the string
        size_t nextPos = input.find('>', pos);
        // If not found, break the loop
        if (nextPos == std::string::npos) {
            break;
        }

        // Get the fragment containing the token
        std::string tokenStr = input.substr(pos, nextPos - pos + 1);

        // Create a new structure and initialize values
        Token t{};
        std::istringstream tokenStream(tokenStr);
        char dummy;
        int temp = 0;
        tokenStream >> dummy >> t.offset >> dummy >> t.length_of_match >> dummy >> temp;
        t.code_word = static_cast<char>(temp);
        compressedData.push_back(t);

        // Update the position
        pos = nextPos + 1;
    }

    std::string decompressedOutput = decompression_lz77(compressedData);
    outputFile.write(decompressedOutput.c_str(), decompressedOutput.size());
    outputFile.close();
}

int solve(const CompressionParams &params) {
    if (!validateParams(params)) {
        std::cout << "Invalid command line parameters. Please provide all required options." << std::endl;
        printInstructions();
        return 1;
    }

    std::vector<char> fileContent = readFileContent(params.inputFileName);

    if (params.mode == "c") {
        if (!fileContent.empty()) {
            performCompression(fileContent, params);
        }
    } else if (params.mode == "d") {
        performDecompression(fileContent, params);
    } else {
        std::cerr << "Invalid mode. Please use 'c' for compression or 'd' for decompression." << std::endl;
        printInstructions();
        return 1;
    }

    return 0;
}
