#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct MemoryBlock {
    int block_id;
    int size;
    int process_id; // Process ID currently occupying the block, -1 if unoccupied
};

void firstFit(vector<MemoryBlock>& memory, int process_id, int process_size) {
    for (auto& block : memory) {
        if (block.process_id == -1 && block.size >= process_size) {
            block.process_id = process_id;
            cout << "Process " << process_id << " allocated to Memory Block " << block.block_id << " (First Fit)" << endl;
            return;
        }
    }
    cout << "Process " << process_id << " cannot be allocated (First Fit)" << endl;
}

void bestFit(vector<MemoryBlock>& memory, int process_id, int process_size) {
    auto best_fit_block = min_element(memory.begin(), memory.end(), [&](const MemoryBlock& a, const MemoryBlock& b) {
        return (a.process_id == -1 && a.size >= process_size) &&
               (b.process_id == -1 && b.size >= process_size) &&
               (a.size < b.size);
    });

    if (best_fit_block != memory.end()) {
        best_fit_block->process_id = process_id;
        cout << "Process " << process_id << " allocated to Memory Block " << best_fit_block->block_id << " (Best Fit)" << endl;
    } else {
        cout << "Process " << process_id << " cannot be allocated (Best Fit)" << endl;
    }
}

void worstFit(vector<MemoryBlock>& memory, int process_id, int process_size) {
    auto worst_fit_block = max_element(memory.begin(), memory.end(), [&](const MemoryBlock& a, const MemoryBlock& b) {
        return (a.process_id == -1 && a.size >= process_size) &&
               (b.process_id == -1 && b.size >= process_size) &&
               (a.size < b.size);
    });

    if (worst_fit_block != memory.end()) {
        worst_fit_block->process_id = process_id;
        cout << "Process " << process_id << " allocated to Memory Block " << worst_fit_block->block_id << " (Worst Fit)" << endl;
    } else {
        cout << "Process " << process_id << " cannot be allocated (Worst Fit)" << endl;
    }
}

int main() {
    int num_blocks;
    cout << "Enter the number of memory blocks: ";
    cin >> num_blocks;

    vector<MemoryBlock> memory(num_blocks);
    for (int i = 0; i < num_blocks; ++i) {
        memory[i].block_id = i + 1;
        cout << "Enter the size of Memory Block " << i + 1 << ": ";
        cin >> memory[i].size;
        memory[i].process_id = -1; // -1 indicates unoccupied
    }

    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    for (int i = 0; i < num_processes; ++i) {
        int process_id, process_size;
        cout << "Enter the size of Process " << i + 1 << ": ";
        cin >> process_size;

        // First Fit
        firstFit(memory, i + 1, process_size);

        // Best Fit
        bestFit(memory, i + 1, process_size);

        // Worst Fit
        worstFit(memory, i + 1, process_size);
    }

    return 0;
}
