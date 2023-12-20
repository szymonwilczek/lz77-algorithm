#include "lz77.h"

std::vector<Token> compression_lz77(const std::string &input, int searchBuffer, int lookAheadBuffer)
{
    int inputLength = input.length();
    int position = 0;
    std::vector<Token> data;

    // Iteration over all input characters
    while (position < inputLength)
    {
        // Initialization and default settings for a new Token
        Token token{};
        token.offset = 0;
        token.length_of_match = 0;
        token.code_word = input[position];

        // Determine the maximum offset
        int max_offset = (position < searchBuffer) ? position : searchBuffer;
        // Determine the maximum match length
        int max_search_length = (position + lookAheadBuffer) > inputLength ? inputLength - position : lookAheadBuffer;

        // Loop to check for matches
        for (int offset = 1; offset <= max_offset; offset++)
        {
            int len = 0;
            // Checking the match length based on the maximum match length
            while (len < max_search_length && input[position - offset + len] == input[position + len])
            {
                len++;
            }

            // Update the token if a better match is found
            if (len > token.length_of_match)
            {
                token.offset = offset;
                token.length_of_match = len;
                token.code_word = input[position + len];
            }
        }

        // Add the token to the vector of compressed data and update the position
        data.push_back(token);
        position += token.length_of_match + 1;
    }

    return data;
}

std::string decompression_lz77(const std::vector<Token> &compressedData)
{
    std::string decompressed;

    // Loop iterating over each token in the vector of compressed data
    for (const Token &token : compressedData)
    {
        // If the offset is zero, add a single character (dictionary code)
        if (token.offset == 0)
        {
            decompressed += token.code_word;
        }
        else
        {
            // Otherwise, copy the previously occurring fragment and add a new character
            int startPos = decompressed.length() - token.offset;
            int endPos = startPos + token.length_of_match;

            for (int i = startPos; i < endPos; ++i)
            {
                decompressed += decompressed[i];
            }

            decompressed += token.code_word;
        }
    }

    return decompressed;
}
