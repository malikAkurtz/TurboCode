#include "utility.h"
#include <vector>
#include <string>
#include <bitset>
#include <iostream>


/**
 * Converts a string into a vector of booleans representing its binary form.
 */
std::vector<bool> stringToVecBool(const std::string& code) {

    std::vector<bool> toReturn = {};

    std::bitset<8> curCharacter;

    // for every character in the string
    for (char c : code) {
        curCharacter = c;
        // for every bit in the character
        for (int i = 7; i >= 0; i--) {
            toReturn.push_back(curCharacter[i]);
        }
    }

    return toReturn;
}


/**
 * Converts a vector of booleans into its corresponding string.
 */
std::string vecBoolToString(const std::vector<bool>& vector_code) {
    std::string toReturn = "";

    char c = 0;

    for (int i = 0; i < vector_code.size() ; i+=8) {
        for (int j = 0; j < 8 ; j++) {
            c = c << 1 | vector_code[i+j];
        }
        toReturn += c;
    }

    return toReturn;
}

std::vector<std::vector<bool>> takeTranspose(std::vector<std::vector<bool>> inputMatrix) {
    int numRows = inputMatrix.size();
    int numCols = inputMatrix[0].size();  // Get the number of columns from the first row

    // Initialize the transposed matrix with dimensions numCols x numRows
    std::vector<std::vector<bool>> transposed(numCols, std::vector<bool>(numRows));

    // Fill the transposed matrix
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            transposed[j][i] = inputMatrix[i][j];
        }
    }

    return transposed;
}


void printMatrix(std::vector<std::vector<bool>> matrix) {
    std::cout << "[";
    for (int i = 0; i < matrix.size(); i++) {
        std::cout << "[";
        for (bool b : matrix[i]) {
            std::cout << b;
        } std::cout << "]";
    } std::cout << "]" << std::endl;;
}

void printVecBool(std::vector<bool> vector) {
    std::cout << "[";
    for (bool b : vector) {
        std::cout << b;
    } std::cout << "]" << std::endl;
}