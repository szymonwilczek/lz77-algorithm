/**
 * @file lz77.h
 * @brief Header file for the LZ77 compression/decompression algorithm.
*/

#ifndef LZ77_LZ77_H
#define LZ77_LZ77_H

#include <vector>
#include <string>

/**
 * @brief Token structure representing a single token in the LZ77 algorithm.
 */
struct Token
{
    int offset; /** @brief Backward offset in the history buffer. Represents the number of characters to go back to reach the beginning of the previous sequence. */
    int length_of_match; /** @brief Length of the match. */
    char code_word; /** @brief Single-byte dictionary code. */
};

/**
 * @brief Function performing compression using the LZ77 algorithm.
 * @param input Input text to compress.
 * @param searchBuffer Size of the history buffer.
 * @param lookAheadBuffer Size of the look-ahead buffer.
 * @return Array of Token structures representing the compressed text.
 */
std::vector<Token> compression_lz77(const std::string &input, int searchBuffer, int lookAheadBuffer);

/**
 * @brief Function performing decompression using the LZ77 algorithm.
 * @param compressed_data Array of Token structures representing the compressed text.
 * @return Decompressed text.
 */
std::string decompression_lz77(const std::vector<Token> &compressed_data);

#endif // LZ77_LZ77_H
