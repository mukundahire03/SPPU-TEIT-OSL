#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time, remaining_time, queue_time;
    bool is_completed;
};

void sort_by_arrival(struct Process p[], int size)
{
    struct Process temp;
    bool swapped = false;
    int i;
    do
    {
        swapped = false;
        for (i = 0; i < size - 1; i++)
        {
            if (p[i].arrival_time > p[i + 1].arrival_time)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

void round_robin(struct Process p[], int time_quantum, int size)
{
    
    int completed = 0, i, temp, current_time = -1, index = 0;
    sort_by_arrival(p, size);

    current_time = p[0].arrival_time;
    while (completed != size)
    {
        temp = 9999;

        for (i = 0; i < size; i++)
        {
            if (!p[i].is_completed && p[i].queue_time <= current_time && p[i].queue_time < temp)
            {
                temp = p[i].queue_time;
                index = i;
            }
        }

        if (p[index].remaining_time >= time_quantum)
        {
            p[index].remaining_time -= time_quantum;
            current_time += time_quantum;
            p[index].queue_time = current_time;
        }
        else
        {
            current_time += p[index].remaining_time;
            p[index].remaining_time = 0;
        }

        if (p[index].remaining_time == 0)
        {
            printf("\nProcess at index %d completed", index);
            p[index].is_completed = true;
            p[index].completion_time = current_time;
            p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
            completed += 1;
        }
    }
}

int main()
{
    int i, time_quant, n;
    float average_waiting_time, average_turnaround_time = 0;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    printf("\nEnter time quantum : ");
    scanf("%d", &time_quant);
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
        process_array[i].queue_time = process_array[i].arrival_time;
        process_array[i].remaining_time = process_array[i].burst_time;
    }


    round_robin(process_array, time_quant, n);

    time_quant = process_array[0].arrival_time;

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
