#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <vector>
#include <string>

namespace TextLibrary {
    std::vector<int> ReadNumbersFromFile(const std::string& filename);
    void WriteNumbersToFile(const std::string& filename, const std::vector<int>& numbers);
    std::vector<int> SortNumbers(const std::vector<int>& numbers);
    std::vector<int> ReverseNumbers(const std::vector<int>& numbers);
    std::vector<int> SwapEvenOdd(const std::vector<int>& numbers);
}

#endif // LIB_H_INCLUDED
