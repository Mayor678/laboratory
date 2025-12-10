// Include necessary C++ standard library headers
#include <iostream>   // For console input/output (cin, cout)
#include <vector>     // For using dynamic arrays (vector container)
#include <string>     // For string manipulation
#include <locale>     // For locale settings (character encoding)
#include <windows.h>  // Windows-specific API functions

// Include our custom library header
#include "lib.h"      // Header file for our dynamic library functions

// Use the TextLibrary namespace to avoid typing TextLibrary:: before every function
using namespace TextLibrary;

/**
 * Sets the working directory to the location of the executable file.
 * This ensures files are read from/written to the same folder as the program.
 */
void SetWorkDir() {
    char path[MAX_PATH];  // Buffer to store the full path (MAX_PATH = 260 characters)

    // Get the full path of the current executable file
    // NULL = current process, path = buffer to store path, MAX_PATH = buffer size
    GetModuleFileNameA(NULL, path, MAX_PATH);

    // Convert the C-style string (char array) to a C++ string for easier manipulation
    std::string fullPath(path);

    // Find the last occurrence of backslash or forward slash (directory separator)
    std::string::size_type pos = fullPath.find_last_of("\\/");

    // Extract the directory portion (everything before the last separator)
    std::string directory = fullPath.substr(0, pos);

    // Change the current working directory to where the executable is located
    SetCurrentDirectoryA(directory.c_str());
}

/**
 * Clears any error flags and discards leftover input from the input buffer.
 * This prevents infinite loops when invalid input is entered.
 */
void ClearInput() {
    // Clear any error flags (like when cin receives unexpected input type)
    std::cin.clear();

    // Discard up to 10000 characters from the input buffer until newline
    // This removes any leftover input that could interfere with next operation
    std::cin.ignore(10000, '\n');
}

/**
 * Displays the main menu of the program with available operations.
 */
void PrintMenu() {
    std::cout << "Program for working with integer array (up to 100 numbers)\n";
    std::cout << "Choose operation:\n";
    std::cout << "1. Sort array\n";
    std::cout << "2. Reverse array (reverse order)\n";
    std::cout << "3. Swap numbers at even and odd positions\n";
    std::cout << "4. Exit program\n";
    std::cout << "Enter operation number or '--help' to show menu: ";
}

/**
 * Main function - program entry point.
 * Manages the main program loop and user interactions.
 */
int main() {
    // Configure console code pages for proper Cyrillic character display
    // These are Windows-specific functions for console encoding
    SetConsoleCP(1251);           // Set input code page to Windows-1251
    SetConsoleOutputCP(1251);     // Set output code page to Windows-1251

    // Set working directory to executable location
    SetWorkDir();

    // Display initial menu
    PrintMenu();

    // Main program loop - runs until user chooses to exit
    while (true) {
        std::string userInput;   // String to store user input
        std::cin >> userInput;   // Read user input (stops at whitespace)

        // Check if user requested help
        if (userInput == "--help") {
            PrintMenu();         // Re-display menu
            continue;            // Skip to next iteration of loop
        }

        int choice;  // Variable to store converted numeric choice

        // Try to convert string input to integer
        try {
            // std::stoi converts string to integer, throws exception if conversion fails
            choice = std::stoi(userInput);
        }
        // Catch exception if conversion fails (e.g., user entered letters)
        catch (std::invalid_argument&) {
            std::cout << "Invalid input. Enter number from 1 to 4 or '--help'.\n";
            ClearInput();   // Clear any problematic input from buffer
            continue;       // Restart loop
        }

        // Check if cin is in a failed state (additional safety check)
        if (std::cin.fail()) {
            std::cout << "Invalid input. Enter number from 1 to 4.\n";
            ClearInput();
            continue;
        }

        // Exit condition
        if (choice == 4) {
            std::cout << "Program termination.\n";
            break;  // Exit the while loop, ending the program
        }

        // Get input and output filenames from user
        std::string inputFile, outputFile;

        std::cout << "Enter input filename: ";
        std::cin >> inputFile;

        std::cout << "Enter output filename: ";
        std::cin >> outputFile;

        // Read numbers from input file using library function
        // Returns vector<int> - a dynamic array of integers
        std::vector<int> numbers = ReadNumbersFromFile(inputFile);

        // Check if reading was successful (vector not empty)
        if (numbers.empty()) {
            std::cout << "Input file is empty or numbers could not be read.\n";
            continue;  // Go back to menu
        }

        // Vector to store operation result
        std::vector<int> result;

        // Perform operation based on user choice
        switch (choice) {
            case 1:
                // Sort numbers in ascending order
                result = SortNumbers(numbers);
                break;
            case 2:
                // Reverse the order of elements
                result = ReverseNumbers(numbers);
                break;
            case 3:
                // Swap elements at even and odd positions
                result = SwapEvenOdd(numbers);
                break;
            default:
                // Handle invalid menu choice (shouldn't happen with previous checks)
                std::cout << "Invalid choice. Try again.\n";
                continue;  // Go back to menu
        }

        // Write result to output file using library function
        WriteNumbersToFile(outputFile, result);

        // Confirm completion to user
        std::cout << "Operation completed. Result written to file " << outputFile << ".\n";
    }

    // Return 0 indicating successful program execution
    return 0;
}
