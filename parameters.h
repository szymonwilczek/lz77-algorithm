/**
 * @file parameters.h
 * @brief Header file for parameter handling functions.
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

/**
 * @brief CompressionParams structure representing compression/decompression parameters.
 */

struct CompressionParams
{

    std::string inputFileName; /** @brief Input file name.*/
    std::string outputFileName; /** @brief Output file name.*/
    std::string mode; /** @brief Program mode (compression/decompression).*/
    int inputBufferSize{}; /** @brief Input buffer size.*/
    int historyBufferSize{}; /** @brief History buffer size.*/
};

/**
 * @brief Function printInstructions() prints program usage instructions.
*/
void printInstructions();

/**
 * @brief Function parseCommandLine() parses parameters from the command line.
 * @param argc Number of parameters.
 * @param argv Array of parameters.
 * @return Returns a CompressionParams structure with the parsed parameters.
 */
CompressionParams parseCommandLine(int argc, char *argv[]);

#endif // PARAMETERS_H
