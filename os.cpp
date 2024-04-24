// MULTILEVEL QUEUE SCHEDULING
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
};

void multilevelQueueScheduling(vector<Process>& processes, vector<int>& turnaround_times, vector<int>& waiting_times) {
    int n = processes.size();

    // Separate processes into high priority and low priority queues
    queue<Process> high_priority_queue, low_priority_queue;

    for (int i = 0; i < n; ++i) {
        if (processes[i].priority == 1) {
            high_priority_queue.push(processes[i]);
        } else {
            low_priority_queue.push(processes[i]);
        }
    }

    int current_time = 0;
    int completed_processes = 0;

    // Schedule high priority queue first
    while (!high_priority_queue.empty()) {
        Process current_process = high_priority_queue.front();
        high_priority_queue.pop();

        if (current_process.arrival_time > current_time) {
            current_time = current_process.arrival_time;
        }

        turnaround_times[current_process.process_id - 1] = current_time + current_process.burst_time - current_process.arrival_time;
        waiting_times[current_process.process_id - 1] = turnaround_times[current_process.process_id - 1] - current_process.burst_time;

        current_time += current_process.burst_time;
        completed_processes++;
    }

    // Schedule low priority queue
    while (!low_priority_queue.empty()) {
        Process current_process = low_priority_queue.front();
        low_priority_queue.pop();

        if (current_process.arrival_time > current_time) {
            current_time = current_process.arrival_time;
        }

        turnaround_times[current_process.process_id - 1] = current_time + current_process.burst_time - current_process.arrival_time;
        waiting_times[current_process.process_id - 1] = turnaround_times[current_process.process_id - 1] - current_process.burst_time;

        current_time += current_process.burst_time;
        completed_processes++;
    }
}

void displayResults(const vector<Process>& processes, const vector<int>& turnaround_times, const vector<int>& waiting_times) {
    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tTurnaround Time\t\tWaiting Time\n";

    for (size_t i = 0; i < processes.size(); ++i) {
        cout << processes[i].process_id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t"
             << turnaround_times[i] << "\t\t\t" << waiting_times[i] << "\n";
    }
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);
    vector<int> turnaround_times(num_processes, 0);
    vector<int> waiting_times(num_processes, 0);

    for (int i = 0; i < num_processes; ++i) {
        processes[i].process_id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority (1 for high, 2 for low) for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    multilevelQueueScheduling(processes, turnaround_times, waiting_times);
    displayResults(processes, turnaround_times, waiting_times);

    return 0;
}
// ROUND ROBIN SCHEDULING
#include<iostream>
using namespace std;

// Shortest Job First

void CompletionTime(int completion_time[], int burst_time[], int arrival_time[], int n) {
    for (int i = 0; i < n; i++) {
        completion_time[i] = burst_time[i] + arrival_time[i];
        for (int j = i + 1; j < n; j++) {
            if (burst_time[j] < burst_time[i]) {
                completion_time[i] = completion_time[i] + burst_time[j];
            }
        }
    }
}

void TurnaroundWaitingTime(int turnaround_time[], int waiting_time[], int completion_time[], int arrival_time[], int n) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }
}

int main() {
    int processes[4];
    int n = sizeof processes / sizeof processes[0];
    cout << "Enter the process IDs: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i];
    }

    int arrival_time[4];
    int p = sizeof arrival_time / sizeof arrival_time[0];
    cout << "\nEnter the Arrival Times: ";
    for (int i = 0; i < p; i++) {
        cin >> arrival_time[i];
    }

    int burst_time[4];
    int m = sizeof burst_time / sizeof burst_time[0];
    cout << "\nEnter the Burst Times: ";
    for (int i = 0; i < m; i++) {
        cin >> burst_time[i];
    }

    int completion_time[4], turnaround_time[4], waiting_time[4];
    CompletionTime(completion_time, burst_time, arrival_time, n);
    TurnaroundWaitingTime(turnaround_time, waiting_time, completion_time, arrival_time, n);

    float avg_TATime = 0.0, avg_WTime = 0.0;
    cout << " Processes" << " Arrival_Time" << "  Burst_Time" << "  Completion_Time" << "  Turnaround_Time" << "  Waiting_Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\t" << processes[i] << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << completion_time[i]
             << "\t\t" << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;

        avg_TATime += turnaround_time[i];
        avg_WTime += waiting_time[i];
    }

    avg_TATime /= n;
    avg_WTime /= n;

    cout << "\nAverage Turnaround Time: " << avg_TATime << endl;
    cout << "Average Waiting Time: " << avg_WTime << endl;

    return 0;
}
// SHORTEST JOB FIRST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateTimes(vector<Process>& processes, vector<int>& turnaround_times, vector<int>& waiting_times) {
    int n = processes.size();

    turnaround_times[0] = processes[0].burst_time;
    waiting_times[0] = 0;

    for (int i = 1; i < n; ++i) {
        turnaround_times[i] = turnaround_times[i - 1] + processes[i].burst_time;
        waiting_times[i] = turnaround_times[i - 1];
    }
}

void displayResults(const vector<Process>& processes, const vector<int>& turnaround_times, const vector<int>& waiting_times) {
    cout << "\nProcess\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time\n";

    for (size_t i = 0; i < processes.size(); ++i) {
        cout << processes[i].process_id << "\t\t" << processes[i].arrival_time << "\t\t"
                  << processes[i].burst_time << "\t\t" << turnaround_times[i] << "\t\t\t" << waiting_times[i] << "\n";
    }
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);
    vector<int> turnaround_times(num_processes, 0);
    vector<int> waiting_times(num_processes, 0);

    for (int i = 0; i < num_processes; ++i) {
        processes[i].process_id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Sort processes based on burst time (Shortest Job First)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burst_time < b.burst_time;
    });

    calculateTimes(processes, turnaround_times, waiting_times);
    displayResults(processes, turnaround_times, waiting_times);

    return 0;
}
// FIRST COME FIRST SERVE
#include <iostream>
#include <vector>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateTimes(std::vector<Process>& processes, std::vector<int>& turnaround_times, std::vector<int>& waiting_times) {
    int n = processes.size();

    turnaround_times[0] = processes[0].burst_time;
    waiting_times[0] = 0;

    for (int i = 1; i < n; ++i) {
        turnaround_times[i] = turnaround_times[i - 1] + processes[i].burst_time;
        waiting_times[i] = turnaround_times[i - 1];
    }
}

void displayResults(const std::vector<Process>& processes, const std::vector<int>& turnaround_times, const std::vector<int>& waiting_times) {
    std::cout << "\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";

    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].process_id << "\t\t" << processes[i].arrival_time << "\t\t"
                  << processes[i].burst_time << "\t\t" << turnaround_times[i] << "\t\t\t" << waiting_times[i] << "\n";
    }
}

int main() {
    int num_processes;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_processes;

    std::vector<Process> processes(num_processes);
    std::vector<int> turnaround_times(num_processes, 0);
    std::vector<int> waiting_times(num_processes, 0);

    for (int i = 0; i < num_processes; ++i) {
        processes[i].process_id = i + 1;
        std::cout << "Enter arrival time for Process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time;
        std::cout << "Enter burst time for Process " << i + 1 << ": ";
        std::cin >> processes[i].burst_time;
    }

    // Sort processes based on arrival time (assuming processes arrive in order)
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    calculateTimes(processes, turnaround_times, waiting_times);
    displayResults(processes, turnaround_times, waiting_times);

    return 0;
}
// SHORTEST SEEK TIME FIRST DISK SCHEDULING 
#include <iostream>
#include <vector>
#include <algorithm>

void sstf_disk_scheduling(std::vector<int>& request_sequence, int initial_head_position) {
    int total_head_movement = 0;
    int current_head_position = initial_head_position;

    std::cout << "Disk Scheduling Sequence (SSTF):" << std::endl;
    if (std::all_of(request_sequence.begin(), request_sequence.end(), [](int element) { return element < 199; })) {
        while (!request_sequence.empty()) {
            auto closest_request = std::min_element(request_sequence.begin(), request_sequence.end(),
                                                    [current_head_position](int a, int b) {
                                                        return std::abs(a - current_head_position) < std::abs(b - current_head_position);
                                                    });
            int head_movement = std::abs(current_head_position - *closest_request);
            total_head_movement += head_movement;
            current_head_position = *closest_request;

            std::cout << "Moving to " << current_head_position << " with head movement " << head_movement << std::endl;
            request_sequence.erase(closest_request);
        }
    } else {
        std::cout << "Movement exceeding the disk length i.e. 199." << std::endl;
    }

    std::cout << "\nTotal Head Movement: " << total_head_movement << std::endl;
}

int main() {
    std::vector<int> request_sequence;
    
    std::cout << "Enter the number of requests: ";
    int num_requests;
    std::cin >> num_requests;

    std::cout << "Enter the address sequence for SSTF:" << std::endl;
    for (int i = 0; i < num_requests; ++i) {
        int value;
        std::cin >> value;
        request_sequence.push_back(value);
    }

    int initial_head_position;
    std::cout << "Enter the initial head position: ";
    std::cin >> initial_head_position;

    sstf_disk_scheduling(request_sequence, initial_head_position);

    return 0;
}
// FIRST COME FIRST SERVE DISK SCHEDULING 
#include <iostream>
#include <vector>

void Firstcome_Firstserve(std::vector<int>& request_sequence, int initial_head_position) {
    int total_head_movement = 0;
    int current_head_position = initial_head_position;

    std::cout << "Disk Scheduling Sequence (FCFS):" << std::endl;
    for (int request : request_sequence) {
        if (request <= 199) {
            int head_movement = abs(current_head_position - request);
            total_head_movement += head_movement;
            current_head_position = request;
            std::cout << "Moving to " << current_head_position << " with head movement " << head_movement << std::endl;
        } else {
            std::cout << "\nHead position exceeding 199. Current head position " << current_head_position << std::endl;
        }
    }
    std::cout << "\nTotal Head Movement: " << total_head_movement << std::endl;
}

int main() {
    std::vector<int> request_sequence;
    int num_values;
    
    std::cout << "Enter the number of values for the FIRST COME FIRST SERVE order: ";
    std::cin >> num_values;

    std::cout << "Enter the address sequence for the FIRST COME FIRST SERVE order:" << std::endl;
    for (int i = 0; i < num_values; ++i) {
        int value;
        std::cin >> value;
        request_sequence.push_back(value);
    }

    int initial_head_position;
    std::cout << "Enter the initial head position: ";
    std::cin >> initial_head_position;

    Firstcome_Firstserve(request_sequence, initial_head_position);

    return 0;
}
