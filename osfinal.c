#include <stdio.h>
#include <string.h>

struct process_Struct {
    char process_name[20];
    int arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

void processQueue(int no_of_process, int quantum_time, struct process_Struct processArray[]) {
    int total_query_time = 0;

    int remaining_time[no_of_process];
    for (int i = 0; i < no_of_process; i++) {
        remaining_time[i] = processArray[i].burst_time;
        processArray[i].completion_time = 0;
        processArray[i].turnaround_time = 0;
        processArray[i].waiting_time = 0;
    }

    int current_time = 0;
    int done = 0;

    while (!done) {
        done = 1;
        for (int i = 0; i < no_of_process; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > quantum_time) {
                    current_time += quantum_time;
                    remaining_time[i] -= quantum_time;
                } else {
                    current_time += remaining_time[i];
                    processArray[i].completion_time = current_time;
                    remaining_time[i] = 0;
                }
            }
        }
    }

    for (int i = 0; i < no_of_process; i++) {
        processArray[i].turnaround_time = processArray[i].completion_time - processArray[i].arrival_time;
        processArray[i].waiting_time = processArray[i].turnaround_time - processArray[i].burst_time;
        total_query_time += processArray[i].turnaround_time;
    }

    float avg_query_time = (float)total_query_time / no_of_process;

    printf("\n| Process Name | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |");
    for (int i = 0; i < no_of_process; i++) {
        printf("\n| %-12s | %-12d | %-10d | %-15d | %-16d | %-13d |",
               processArray[i].process_name, processArray[i].arrival_time,
               processArray[i].burst_time, processArray[i].completion_time,
               processArray[i].turnaround_time, processArray[i].waiting_time);
    }
    printf("\n\nTotal time spent on handling queries: %d", total_query_time);
    printf("\nAverage query time: %.2f\n", avg_query_time);
}

int main() {
    int faculty_processes, student_processes;
    printf("Enter the number of faculty processes: ");
    scanf("%d", &faculty_processes);
    struct process_Struct facultyProcesses[faculty_processes];

    for (int i = 0; i < faculty_processes; i++) {
        printf("Enter details for faculty process %d:\n", i + 1);
        printf("Process Name: ");
        scanf("%s", facultyProcesses[i].process_name);
        printf("Arrival Time: ");
        scanf("%d", &facultyProcesses[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &facultyProcesses[i].burst_time);
    }

    printf("Enter the number of student processes: ");
    scanf("%d", &student_processes);
    struct process_Struct studentProcesses[student_processes];

    for (int i = 0; i < student_processes; i++) {
        printf("Enter details for student process %d:\n", i + 1);
        printf("Process Name: ");
        scanf("%s", studentProcesses[i].process_name);
        printf("Arrival Time: ");
        scanf("%d", &studentProcesses[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &studentProcesses[i].burst_time);
    }

    int quantum_time;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum_time);

    printf("Faculty Queue:\n");
    processQueue(faculty_processes, quantum_time, facultyProcesses);

    printf("Student Queue:\n");
    processQueue(student_processes, quantum_time, studentProcesses);

    return 0;
}

