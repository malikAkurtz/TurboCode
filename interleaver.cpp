#include <vector>
#include <iostream>

void printRegisters(std::vector<std::vector<bool>> registers) {
    std::cout << "Registers: " << std::endl;
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

    // // add (n - 1) * n zeroes to the end
    // int zeroesToAdd = (N -1) * N;
    // for (int i = 0; i < zeroesToAdd; i++) {
    //     input.push_back(0);
    // }

    auto pointerToEnd = input.end();

    std::vector<bool> interleaved = {};

    // the index of the register indicates its delay

    // <0,0,0>
    // we need N, N bit registers
    std::vector<std::vector<bool>> registers(N, std::vector<bool>(N));

    // initalize our N, N bit registers with the first N * N input bits
    // for every register
    for (int i = 0; i < registers.size(); i++) {
        // for every index in this register
        // load the appropriate input bits
        for (int j = 0; j < N ; j++) {
            registers[i][j] = input[(i * N) + j];
            pointerToNextDataBitToProcess++;
        }
    }

    printRegisters(registers);
    // while we have not yet processed each bit in input
    while (iterator != pointerToEnd) {
        if (timeStep >= (N-1)) {
            std::cout << "Here" << std::endl;
            // At the beginning of every timestep,
            // Grab each appropriate bit from each shift register according to its delay
            for (int i = 0; i < registers.size(); i++) {
                interleaved.push_back(registers[i][N - 1 - i]);
                iterator++;
            }

            printInterleaved(interleaved);

            //Shift the register
            // shift every register except the 
            for (int i = 0; i < N-1; i++) {
                // First register will be equal to the second register etc
                for (int j = 0; j < N; j++) {
                    registers[i][j] = registers[i+1][j];
                }
                timeStep++;
            }

            // set the last register to the 3 new input bits incoming
            for (int i = 0; i < N; i++) {
                registers[N-1][i] = *pointerToNextDataBitToProcess;
                pointerToNextDataBitToProcess++;
            }
            timeStep++;
        }
        else {

            //i = 2
            for (int i = 0; i < (N-1); i++) {
                // j = 0
                int counter = 0;
                for (int j = 0; j <= i; j++) {
                    interleaved.push_back(registers[j][i-counter]);
                    counter++;
                    iterator++;
                }
                timeStep++;
                
            }
        }
    }
        

    return interleaved;
}   

int main(){

    std::vector<bool> inter = interleave({1,1,0,0,1,1,0,0,1,1}, 3);

    std::cout << "[";
    for (bool b : inter) {
        std::cout << b;
    } std::cout << "]" << std::endl;

    return 0;
}