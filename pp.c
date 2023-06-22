#include <stdio.h>
#include <stdlib.h>
struct pcb
{
    int at, bt, ord, rem, rt, wt, tat, term;
};
void input(struct pcb *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nenter ARRIVAL TIME for P%d = ", i);
        scanf("%d", &arr[i].at);
        printf("\nenter BURST TIME for P%d = ", i);
        scanf("%d", &arr[i].bt);
        printf("\nenter ORDER for P%d = ", i);
        scanf("%d", &arr[i].ord);
        arr[i].rem = arr[i].bt;
        arr[i].term = arr[i].tat = arr[i].wt = arr[i].rt = 0;
    }
}
int allterminated(struct pcb *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!arr[i].term)
        {
            return 0;
        }
    }
    return 1;
}
int nextprocess(struct pcb *arr, int n, int ct)
{
    int min = 100, r = -1;
    for (int i = 0; i < n; i++)
    {
        if ((arr[i].at <= ct) && (arr[i].term != 1))
        {
            if (arr[i].ord <= min)
            {
                min = arr[i].ord;
                r = i;
            }
        }
    }
    return r;
}
void gantt(struct pcb *arr1, int n1, struct pcb *arr2, int n2)
{
    int ct = 0;
    while (!allterminated(arr1, n1) || !allterminated(arr2, n2))
    {
        int i = nextprocess(arr1, n1, ct);
        int j = nextprocess(arr2, n2, ct);
        if (i == -1 && j == -1)
        {
            printf("at T=%d idle\n", ct);
        }
        else if (j == -1 && i != -1)
        {
            if (arr1[i].bt == arr1[i].rem)
            {
                arr1[i].rt = ct - arr1[i].at;
            }
            arr1[i].rem--;
            if (arr1[i].rem == 0)
            {
                arr1[i].tat = (ct + 1) - arr1[i].at;
                arr1[i].term = 1;
            }
            for (int k = 0; k < n1; k++)
            {
                if ((arr1[k].at <= ct) && (arr1[k].term != 1) && (k != i))
                {
                    arr1[k].wt++;
                }
            }
            printf("at T=%d P_fcfs%d\n", ct, i);
        }
        else if (j != -1)
        {
            if (arr2[j].bt == arr2[j].rem)
            {
                arr2[j].rt = ct - arr2[j].at;
            }
            arr2[j].rem--;
            if (arr2[j].rem == 0)
            {
                arr2[j].tat = (ct + 1) - arr2[j].at;
                arr2[j].term = 1;
            }
            for (int k = 0; k < n2; k++)
            {
                if ((arr2[k].at <= ct) && (arr2[k].term != 1) && (k != j))
                {
                    arr2[k].wt++;
                }
            }
            for (int k = 0; k < n1; k++)
            {
                if ((arr1[k].at <= ct) && (arr1[k].term != 1))
                {
                    arr1[k].wt++;
                }
            }
            printf("at T=%d P_priority%d\n", ct, j);
        }
        ct++;
    }
}
void printdetailsfcfs(struct pcb *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("WATING TIME for P_fcfs%d = %d\n", i, arr[i].wt);
        printf("RESPONSE TIME for P_fcfs%d = %d\n", i, arr[i].rt);
        printf("TURN AROUND TIME for P_fcfs%d = %d\n", i, arr[i].tat);
    }
}
void printdetailspriority(struct pcb *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("WATING TIME for P_priority%d = %d\n", i, arr[i].wt);
        printf("RESPONSE TIME for P_priority%d = %d\n", i, arr[i].rt);
        printf("TURN AROUND TIME for P_priority%d = %d\n", i, arr[i].tat);
    }
}
int main()
{
    int n1, n2;
    struct pcb *arr1, *arr2;
    printf("enter number of process for fcfs : ");
    scanf("%d", &n1);
    arr1 = (struct pcb *)malloc(n1 * sizeof(struct pcb));
    input(arr1, n1);
    printf("enter number of process for priority : ");
    scanf("%d", &n2);
    arr2 = (struct pcb *)malloc(n2 * sizeof(struct pcb));
    input(arr2, n2);
    gantt(arr1, n1, arr2, n2);
    printdetailsfcfs(arr1, n1);
    printdetailspriority(arr2, n2);
    return 0;
}