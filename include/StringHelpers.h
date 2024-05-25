//
// Created by thevi on 5/25/2024.
//

#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <string>
#include <vector>


inline std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end;
    const size_t delim_len = delimiter.length();
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

inline size_t findLineStart(const size_t currentPosition, const std::string& text, const char& newLineCharacter) {
    if (currentPosition == 0) return 0;

    // Manually search backwards for the previous newline character
    for (size_t i = currentPosition - 1; i != size_t(-1); --i) {
        if (text[i] == newLineCharacter) {
            return i + 1;
        }
    }
    return 0;
}

inline size_t findLineEnd(const size_t currentPosition, const std::string& text, const char& newLineCharacter) {
    const size_t lineEnd = text.find(newLineCharacter, currentPosition);
    return lineEnd == std::string::npos ? text.size() : lineEnd;
}

#endif //STRINGHELPERS_H
