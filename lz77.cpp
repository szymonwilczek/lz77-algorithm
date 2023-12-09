#include "lz77.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>

void printInstructions()
{
    std::cout << "Use instructions: lz77 -i input_file -o output_file -t [mode](c-compression/d-decompression) -n inputBufferSize -k historyBufferSize" << std::endl;
    std::cout << "Opcje:" << std::endl;
    std::cout << "  -i input_file: Input file for compression/decompression" << std::endl;
    std::cout << "  -o output_file: Output file for compression/decompression" << std::endl;
    std::cout << "  -t mode: c for compression, d for decompression" << std::endl;
    std::cout << "  -n inputBufferSize: Size of input buffer (max match length)" << std::endl;
    std::cout << "  -k  historyBufferSize: Size of history buffer (search buffer)" << std::endl;
}

int solve(int argc, char *argv[])
{
    std::string inputFileName, outputFileName, mode;
    int inputBufferSize = 0, historyBufferSize = 0;

    // Parsing parameters from command line
    // strcmp for comparing strings so we don't parse other options
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            inputFileName = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            outputFileName = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            mode = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
        {
            inputBufferSize = std::stoi(argv[i + 1]);
            ++i;
        }
        else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc)
        {
            historyBufferSize = std::stoi(argv[i + 1]);
            ++i;
        }
    }

    if (inputFileName.empty() || outputFileName.empty() || mode.empty() || inputBufferSize <= 0 || historyBufferSize <= 0)
    {
        std::cout << "Incorrect parameters. Please provide all required options." << std::endl;
        printInstructions();
        return 1;
    }

    // Opening file
    std::ifstream inputFile(inputFileName, std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Error occured while opening input file: " << inputFileName << std::endl;
        return 1;
    }

    // Reading file as binary
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // Allocating buffer for file content
    std::vector<char> fileContent(fileSize, '\0');

    // Parsing file to buffer
    inputFile.read(fileContent.data(), fileSize);

    // Delete non-printable characters
    std::basic_string<char> readData;
    for (char byte : fileContent) {
        if (std::isprint(static_cast<unsigned char>(byte))) {
            readData += byte;
        }
    }

    // Closing file
    inputFile.close();

    Token* arr = nullptr;
    if (mode == "c")
    {
        if (!fileContent.empty())
        {
            arr = compression_lz77(readData, inputBufferSize, historyBufferSize);

            std::ofstream outputFile(outputFileName);
            if (!outputFile.is_open())
            {
                std::cerr << "Error occured while opening output file: " << outputFileName << std::endl;
                return 1;
            }

            // Saving to file
            for(int i = 0; i < counter; i++)
            {
                outputFile << "(" << arr[i].offset << "," << arr[i].length_of_match << "," << arr[i].code_word << ")";
            }
            outputFile.close();

            // Calculating compression ratio
            double startingSize = static_cast<double>(fileContent.size());
            double compressedSize = static_cast<double>(counter) * (sizeof(Token) / sizeof(char));  // Count of tokens * average token length in bytes

            double ratio = (startingSize / compressedSize) * 100.0;

            std::cout << "Theoretical compression ratio: " << ratio << "%" << std::endl;
            std::cout << "Theoretical compression grade: " << (compressedSize / startingSize) << std::endl;
        }
    }
    else if (mode == "d")
    {
        std::ofstream outputFile(outputFileName, std::ios::binary);
        if (!outputFile.is_open()) {
            std::cerr << "Error occured while opening output file: " << outputFileName << std::endl;
            return 1;
        }

        // Stringify input
        std::string input(fileContent.begin(), fileContent.end());

        // Initializing vector that will store compressed data as a Token structure
        std::vector<Token> compressed_data;
        size_t pos = 0;
        // Iteration over input and parsing it to tokens
        while (pos < input.size()) {
            size_t nextPos = input.find(')', pos);
            if (nextPos == std::string::npos) {
                break;  // end of string = end of parsing
            }

            // Extracting token
            // +1 to extract also the bracket
            std::string tokenStr = input.substr(pos, nextPos - pos + 1);

            Token t{};
            // Parsing string to token structure components
            std::istringstream tokenStream(tokenStr);

            // Parsing arguments from string
            char dummy; // "eating" brackets and commas
            tokenStream >> dummy >> t.offset >> dummy >> t.length_of_match >> dummy >> t.code_word;
            // Adding token to vector
            compressed_data.push_back(t);

            // Update position
            pos = nextPos + 1;
        }

        std::string decompressed_output = decompression_lz77(compressed_data.data(), compressed_data.size());

        // Saving to file
        // c_str() to get a pointer to the character array to write()
        outputFile.write(decompressed_output.c_str(), decompressed_output.size());

        inputFile.close();
        outputFile.close();

        // Free memory
        delete[] arr;
    }
    else
    {
        std::cerr << "Incorrect mode. Please use 'c' for compression or 'd' for decompression." << std::endl;
        printInstructions();
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Parsing command line parameters
    if (argc < 2)
    {
        printInstructions();
        return 1;
    }

    solve(argc, argv);

    return 0;
}
