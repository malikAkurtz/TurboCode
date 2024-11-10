#include <vector>
#include <iostream>

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

void printRegisters(std::vector<std::vector<bool>> registers, int timeStep) {
    std::cout << "Registers at TimeStep " << timeStep << std::endl;
    std::cout << "[";
    for (int i = 0; i < registers.size(); i++) {
        std::cout << "[";
        for (bool b : registers[i]) {
            std::cout << b;
        } std::cout << "]";
    }std::cout << "]" << std::endl;
}

void printInterleaved(std::vector<bool> interleaver) {
    std::cout << "Interleaved: " << std::endl;
    std::cout << "[";
    for (bool b : interleaver) {
        std::cout << b;
    } std::cout << "]" << std::endl;
}

std::vector<bool> interleave(std::vector<bool> input, int burst_protection) {
    // input = <1,0,1,0>
    // burst_protection = 3
    int N = burst_protection;
    auto iterator = input.begin();
    int timeStep = 0;
    

    // auto pointerToNextDataBitToProcess = input.begin();

    // pad with zeroes at the end
    while (input.size() % N != 0) {
        input.push_back(0);
    }



    auto pointerToEnd = input.end();

    std::vector<bool> interleaved = {};

    // the index of the register indicates its delay

    // <0,0,0>
    // we need N, N bit registers
    std::vector<std::vector<bool>> registers(N, std::vector<bool>(N));


    // while we have not yet processed each bit in input
    while (iterator != pointerToEnd) {
        // Start Shift the registers
        for (int i = 0; i < N-1; i++) {
                // First register will be equal to the second register etc
                for (int j = 0; j < N; j++) {
                    registers[i][j] = registers[i+1][j];
                }
            }
        // set the last register to the N new input bits incoming
        for (int i = 0; i < N; i++) {
            registers[N-1][i] = *iterator;
            iterator++;
        }

        
        printRegisters(registers, timeStep);

        // End Shift the registers


        // Grab each appropriate bit from each shift register according to its delay
        if (timeStep >= (N-1)) {
            for (int i = 0; i < registers.size(); i++) {
                interleaved.push_back(registers[i][N - 1 - i]);
            }
        }
        else {
            //timeStep = 2

            for (int i = (N-1) - timeStep; i <= (N-1); i++) {
                interleaved.push_back(registers[i][(N-1) - i]);
            }
        }
        

        
        printInterleaved(interleaved);
        timeStep++;



    }
        

    return interleaved;
}   

int main(){
    std::string message = "Hello World!";
    std::vector<bool> toInterleave = stringToVecBool(message);

    toInterleave = {1,1,0,0,1,1,0,0,1,1};
    // toInterleave = {1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1};
    std::vector<bool> interleaved = interleave(toInterleave, 3);

    // std::cout << "After Interleaving: " << vecBoolToString(interleaved) << std::endl;


    return 0;
}