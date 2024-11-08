#include <vector>
#include <iostream>

std::vector<bool> interleave(std::vector<bool> input, int burst_protection) {
    // input = <1,0,1,0>
    // burst_protection = 3
    
    // pad with zeroes at the end
    while (input.size() % burst_protection != 0) {
        input.push_back(0);
    }

    int t = 0;

    std::vector<bool> interleaved(input.size());

    // the index of the register indicates its delay

    // <0,0,0>
    std::vector<bool> registers(burst_protection);

    auto iterator = input.begin();

    // while we have not yet processed each bit in input
    while (iterator != input.end()) {
        // load the bits into their proper registers at this timestep
        for (int i = 0; i < burst_protection; i++) {
            std::cout << *iterator << std::endl;
            registers[i] = *iterator;
            iterator++;
        }

        // determine what is output at this timestep

        // whatever is in index 0 automatically gets output
        for (int i = 0; i < registers.size(); i++) {
            
        }

    }

    std::cout << "[";
    for (bool b : registers) {
        std::cout << b;
    } std::cout << "]";
    return {0};

}   

int main(){

    interleave({1,0,1, 0}, 3);

    return 0;
}