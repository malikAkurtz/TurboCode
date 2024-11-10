#include <vector>
#include <iostream>
#include "utility.h"


std::vector<bool> interleave(std::vector<bool> input, int numRows) { // numRows = numCharacters in input string
    std::vector<bool> interleaved = {};

    // a char is 8 bits
    std::vector<std::vector<bool>> inputAsMatrix(numRows, std::vector<bool>(8));


    // put them in the block_interleaver
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < 8; j++) {
            inputAsMatrix[i][j] = (input[(i*8) + j]);
        }
    }

    // Take the transpose of the input matrix to create the actual block interleaver

    std::cout << "Input Matrix: " << std::endl;
    printMatrix(inputAsMatrix);
    
    std::vector<std::vector<bool>> block_interleaver = takeTranspose(inputAsMatrix);
    std::cout << "Transposed: " << std::endl;
    printMatrix(block_interleaver);

    // read the values back out row by row to get the interleaved output

    for (int i = 0; i < block_interleaver.size(); i++) {
        for (int j = 0; j < block_interleaver[0].size(); j++) {
            interleaved.push_back(block_interleaver[i][j]);
        }
    }

    return interleaved;
}   

int main(){
    std::string message = "Hell";
    std::vector<bool> toInterleave = stringToVecBool(message);

    // toInterleave = {1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1};
    std::vector<bool> interleaved = interleave(toInterleave, message.length());
    
    std::cout << "After Interleaving: " << std::endl;

    printVecBool(interleaved);

    return 0;
}