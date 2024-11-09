#include <vector>
#include <iostream>

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
    

    auto pointerToNextDataBitToProcess = input.begin();

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
    while (iterator < pointerToEnd) {
        // Start Shift the registers
        for (int i = 0; i < N-1; i++) {
                // First register will be equal to the second register etc
                for (int j = 0; j < N; j++) {
                    registers[i][j] = registers[i+1][j];
                }
            }
        // set the last register to the N new input bits incoming
        for (int i = 0; i < N; i++) {
            registers[N-1][i] = *pointerToNextDataBitToProcess;
            pointerToNextDataBitToProcess++;
        }

        
        printRegisters(registers, timeStep);

        // End Shift the registers


        // Grab each appropriate bit from each shift register according to its delay
        for (int i = 0; i < registers.size(); i++) {
            interleaved.push_back(registers[i][N - 1 - i]);
            iterator++;
        }

        
        printInterleaved(interleaved);
        timeStep++;



    }
        

    return interleaved;
}   

int main(){

    std::vector<bool> inter = interleave({1,1,0,0,1,1,0,0,1,1}, 4);

    std::cout << "[";
    for (bool b : inter) {
        std::cout << b;
    } std::cout << "]" << std::endl;

    return 0;
}