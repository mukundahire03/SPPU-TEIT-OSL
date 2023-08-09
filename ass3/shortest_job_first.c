#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time, remaining_time;
    bool is_completed;
};

void shortest_job_first(struct Process p[], int size)
{
    int current_time = 0, completed = 0, index, i, temp;
    while (completed != size)
    {
        temp = 9999;
        bool found = false;

        for (i = 0; i < size; i++)
        {
            if (!p[i].is_completed && p[i].arrival_time <= current_time && p[i].remaining_time < temp)
            {
                temp = p[i].remaining_time;
                index = i;
            }
        }
        p[index].remaining_time -= 1;
        if (p[index].remaining_time == 0)
        {
            printf("\nCompleted Process %d at time %d", p[index].pid, (current_time + 1));
            p[index].is_completed = true;
            p[index].completion_time = current_time + 1;
            p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
            completed += 1;
        }
        current_time += 1;
    }
}

int main()
{
    int i, n;
    float average_waiting_time, average_turnaround_time = 0;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct Process process_array[n];
    for (i = 0; i < n; i++)
    {
        printf("\nProcess ID : ");
        scanf("%d", &process_array[i].pid);
        printf("\nArrival Time : ");
        scanf("%d", &process_array[i].arrival_time);
        printf("\nBurst Time : ");
        scanf("%d", &process_array[i].burst_time);
        printf("\n");
        process_array[i].is_completed = false;
        process_array[i].remaining_time = process_array[i].burst_time;
    }


    shortest_job_first(process_array, n);

    printf("\n\nSr.No.\tPID\tAT\tBT\tCT\tTAT\tWT");

    for (i = 0; i < n; i++)
    {
        average_waiting_time += process_array[i].waiting_time;
        average_turnaround_time += process_array[i].turn_around_time;
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t", (i + 1), process_array[i].pid, process_array[i].arrival_time, process_array[i].burst_time, process_array[i].completion_time, process_array[i].turn_around_time, process_array[i].waiting_time);
    }
    average_waiting_time /= n;
    average_turnaround_time /= n;
    printf("\n\nAverage Waiting Time : %fms", average_waiting_time);
    printf("\n\nAverage Turn Around Time : %fms\n", average_turnaround_time);
    printf("\n");
    return (0);
}
