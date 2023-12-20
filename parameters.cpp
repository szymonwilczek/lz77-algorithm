#include "parameters.h"
#include <iostream>
#include <cstring>

void printInstructions()
{
    std::cout << "Usage: lz77 -i input_file -o output_file -t [mode](c-compression/d-decompression) -n input_buffer_size -k history_buffer_size" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i input_file: Input file for compression/decompression" << std::endl;
    std::cout << "  -o output_file: Output file for compression/decompression" << std::endl;
    std::cout << "  -t mode: c for compression, d for decompression" << std::endl;
    std::cout << "  -n input_buffer_size: Input buffer size (maximum match length)" << std::endl;
    std::cout << "  -k history_buffer_size: History buffer size (Search buffer)" << std::endl;
}

CompressionParams parseCommandLine(int argc, char *argv[])
{
    CompressionParams params;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            params.inputFileName = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            params.outputFileName = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            params.mode = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
        {
            params.inputBufferSize = std::stoi(argv[i + 1]);
            ++i;
        }
        else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc)
        {
            params.historyBufferSize = std::stoi(argv[i + 1]);
            ++i;
        }
    }

    return params;
}