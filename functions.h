/**
 * @file functions.h
 * @brief Header file for auxiliary functions.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "parameters.h"
#include "lz77.h"

/**
 * @brief Function to check the correctness of compression/decompression parameters.
 */
bool validateParams(const CompressionParams &params);

/**
 * @brief Function to read the contents of a file into a vector.
 *
 * @param fileName File name.
 * @return Vector containing the contents of the file.
 */
std::vector<char> readFileContent(const std::string &fileName);

/**
 * @brief Function to write the contents of a vector to a file.
 *
 * @param compressedData Vector containing the contents of the file.
 * @param outputFileName File name.
 */
void writeCompressedData(const std::vector<Token> &compressedData, const std::string &outputFileName);

/**
 * @brief Function to perform compression.
 *
 * @param fileContent Vector containing the contents of the file.
 * @param params Compression parameters.
 */
void performCompression(const std::vector<char> &fileContent, const CompressionParams &params);

/**
 * @brief Function to perform decompression.
 *
 * @param fileContent Vector containing the contents of the file.
 * @param params Compression parameters.
 */
void performDecompression(const std::vector<char> &fileContent, const CompressionParams &params);

/**
 * @brief Coordinating function for compression/decompression.
 *
 * @param params Compression parameters.
 * @return Program exit code.
 */
int solve(const CompressionParams &params);
#endif // FUNCTIONS_H
