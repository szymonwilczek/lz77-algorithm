/**
 * @file lz77.h
 * @brief Header file for LZ77 compression-decompression algorithm.
 */
#ifndef LZ77_H
#define LZ77_H

#include <string>
#include <vector>

int counter = 0;

/**
 * @brief Structure Token representing single token in algorithm.
 */
struct Token
{
    int offset; /** @brief Backward offset in history buffer. Represents number of characters to go back to reach the beginning of the previous sequence. */
    int length_of_match; /** @brief Length of match. */
    char code_word; /** @brief Single byte dictionary code. */
};

/**
 * @brief Function performing compression using LZ77 algorithm.
 * @param input Input string.
 * @param searchBuffer Size of search buffer.
 * @param lookAheadBuffer Size of look ahead buffer.
 * @return Array of Token structures representing compressed text.
 */
Token *compression_lz77(const std::string &input, int searchBuffer, int lookAheadBuffer)
{
    // Variables and data buffer preparation
    int inputLength = input.length();
    int final_size = inputLength - lookAheadBuffer + 1;
    auto *data = new Token[final_size];
    int position = 0;

    while (position < inputLength)
    {
        // Preparing token and initializing default values
        Token token{};
        token.offset = 0;
        token.length_of_match = 0;
        token.code_word = input[position];

        // Setting maximum offset and maximum match length
        int max_offset = (position - searchBuffer) < 0 ? position : searchBuffer;
        int max_search_length = (position + lookAheadBuffer) > inputLength ? inputLength - position : lookAheadBuffer;

        // Szukanie dopasowania
        for (int offset = 1; offset <= max_offset; offset++)
        {
            int len = 0;
            // Comparing sequences of characters
            // Checking how many characters from current position is the same at distance offset
            while (len < max_search_length && input[position - offset + len] == input[position + len])
            {
                len++;
            }

            // If better match is found, it is saved in token
            if (len > token.length_of_match)
            {
                token.offset = offset;
                token.length_of_match = len;
                token.code_word = input[position + len];
            }
        }

        // Saving token in data buffer
        data[counter] = token;
        // Incrementing counter
        counter++;
        // Update position
        position += token.length_of_match + 1;
    }

    return data;
}
/**
 * @brief Function performing decompression using LZ77 algorithm.
 * @param compressed_data Array of Token structures representing compressed text.
 * @param size Size of compressed data array.
 * @return Decompressed string.
 */
std::string decompression_lz77(Token *compressed_data, int size) {
    // Initializating empty string
    std::string decompressed;

    for (int i = 0; i < size; i++) {
        // Iteration over all tokens to build string
        Token token = compressed_data[i];

        // Length = 0 -> single character
        if (token.length_of_match == 0) {
            decompressed += token.code_word;

            // Other way - there was a match in sequence of characters
            // Copying previous sequence and adding character from current token
        } else {
            int start_index = decompressed.length() - token.offset;
            for (int j = 0; j < token.length_of_match; j++) {
                decompressed += decompressed[start_index + j];
            }
            decompressed += token.code_word;
        }
    }

    return decompressed;
}
#endif // LZ77_H
