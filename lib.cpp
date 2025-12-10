// Include the custom library header that declares these functions
#include "lib.h"

// Include necessary C++ standard library headers
#include <fstream>     // For file input/output operations
#include <sstream>     // For string stream operations (not used in this code but commonly included)
#include <algorithm>   // For various algorithms (sort, reverse, swap)
#include <iostream>    // For console input/output (not directly used here but good practice)

// Use the standard namespace to avoid typing std:: before standard functions
using namespace std;

// Define the TextLibrary namespace to organize our functions
namespace TextLibrary
{
    /**
     * Reads an array of integers from a file (maximum 100 numbers).
     *
     * @param filename The name of the file to read from
     * @return A vector containing the read integers, or empty vector if file cannot be read
     *
     * Explanation: This function opens a file, reads integers one by one,
     * and stores them in a vector until either the end of file is reached
     * or 100 numbers have been read.
     */
    std::vector<int> ReadNumbersFromFile(const std::string& filename)
    {
        std::vector<int> numbers;    // Create an empty vector to store numbers
        std::ifstream file(filename); // Create an input file stream and open the file

        int number;  // Temporary variable to hold each number as it's read

        // Read numbers from the file until:
        // 1. The file extraction fails (end of file or non-integer data)
        // 2. We've read 100 numbers (numbers.size() < 100)
        while (file >> number && numbers.size() < 100)
        {
            // Add the successfully read number to the end of the vector
            numbers.push_back(number);
        }

        // Return the vector containing the read numbers
        return numbers;
    }

    /**
     * Writes an array of integers to a file.
     *
     * @param filename The name of the file to write to
     * @param numbers The vector of integers to write to the file
     *
     * Explanation: This function creates or overwrites a file and writes
     * all integers from the vector to it, separated by spaces.
     */
    void WriteNumbersToFile(const std::string& filename, const std::vector<int>& numbers)
    {
        std::ofstream file(filename); // Create an output file stream and open the file

        // Range-based for loop: iterate through each element in the vector
        // 'const auto& number' means: for each constant reference to an element (efficient)
        for (const auto& number : numbers)
        {
            // Write the number followed by a space to the file
            file << number << " ";
        }
        // File is automatically closed when 'file' goes out of scope (destructor)
    }

    /**
     * Sorts an array of integers in ascending order.
     *
     * @param numbers The original vector of integers
     * @return A new sorted vector (original vector is not modified)
     *
     * Explanation: This function creates a copy of the input vector,
     * sorts it using the standard sort algorithm, and returns the sorted copy.
     */
    std::vector<int> SortNumbers(const std::vector<int>& numbers)
    {
        // Create a copy of the original vector to avoid modifying the input
        std::vector<int> sorted = numbers;

        // Use std::sort to sort the entire vector in ascending order
        // begin() returns an iterator to the first element
        // end() returns an iterator just past the last element
        std::sort(sorted.begin(), sorted.end());

        return sorted;
    }

    /**
     * Reverses the order of elements in an array.
     *
     * @param numbers The original vector of integers
     * @return A new reversed vector (original vector is not modified)
     *
     * Explanation: This function creates a copy of the input vector,
     * reverses the order of elements, and returns the reversed copy.
     */
    std::vector<int> ReverseNumbers(const std::vector<int>& numbers)
    {
        // Create a copy of the original vector
        std::vector<int> reversed = numbers;

        // Use std::reverse to reverse the order of elements in the vector
        std::reverse(reversed.begin(), reversed.end());

        return reversed;
    }

    /**
     * Swaps numbers at even and odd positions (0-indexed).
     *
     * @param numbers The original vector of integers
     * @return A new vector with swapped elements (original vector is not modified)
     *
     * Explanation: This function swaps each pair of elements:
     * - Position 0 (even) swaps with position 1 (odd)
     * - Position 2 (even) swaps with position 3 (odd)
     * - And so on...
     * If there's an odd number of elements, the last element stays in place.
     */
    std::vector<int> SwapEvenOdd(const std::vector<int>& numbers)
    {
        // Create a copy of the original vector
        std::vector<int> swapped = numbers;

        // Loop through the vector in steps of 2 (i increments by 2 each iteration)
        // Condition: i + 1 < swapped.size() ensures we don't go out of bounds
        // size_t is an unsigned integer type suitable for container sizes
        for (size_t i = 0; i + 1 < swapped.size(); i += 2)
        {
            // Swap the current element (even position) with the next element (odd position)
            std::swap(swapped[i], swapped[i + 1]);
        }

        return swapped;
    }
}
