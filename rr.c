#include<stdio.h>
struct process
{
    int at,bt,rem,tat,rt,wt,tt,terminated,remslice,token;
}pr[10];
int token=0;
int allprocessesTerminated(int n ,struct process pr[10])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(!pr[i].terminated)
        {
            return 0;
        }
    }
    return 1;
}
void enqueue(int n,struct process pr[10],int x)
{
    if(x>(n-1))
    return;
    pr[x].token=token++;
}
int dequeue(int n,struct process pr[10])
{
    int min_val=1000,x=-1;
    for(int i=0;i<n;i++)
    {
        if(pr[i].token<min_val)
        {
        min_val=pr[i].token;
        x=i;
        }
    }
    pr[x].token=1000;
    return x;
}
int nextprocessTorun(int n , struct process pr[10] , int ct,int q)
{
    int x=-1;
    for(int i=0;i<n;i++)
    {
        if(pr[i].remslice>0)
        return i;
    }
    x=dequeue(n,pr);
    if(x!=-1)
    pr[x].remslice=q;
    return x;
}
int main()
{
    int i,j,n,q;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    printf("Enter time quantum: ");
    scanf("%d",&q);
    for(i=0;i<n;i++)
    {
        printf("PROCESS P(%d)\n",i);
        printf("Enter the arrival time ( AT ) : ");
        scanf("%d",&pr[i].at);
        printf("Enter the burst time ( BT ) : ");
        scanf("%d",&pr[i].bt);
        pr[i].rem=pr[i].bt;
        pr[i].wt=0;
        pr[i].terminated=0;
        pr[i].remslice=0;
        pr[i].token=1000;
    }
    int x=-1;
    int ct=0;
    while(!allprocessesTerminated(n,pr))
    {
        for(i=0;i<n;i++)
        {
        if(pr[i].at==ct)
        enqueue(n,pr,i);
    }
    if(x!=-1 && !pr[x].terminated && pr[x].remslice==0)
    {
        enqueue(n,pr,x);
    }
    x=nextprocessTorun(n,pr,ct,q);
    if(x==-1)
    {
        printf("t=%d IDLE \n",ct);
        ++ct;
        continue;
    }
    //set Response Time
    if(pr[x].rem == pr[x].bt)
        {
            pr[x].rt = ct - pr[x].at;
        }
    --pr[x].rem;
    --pr[x].remslice;
    if(pr[x].rem==0)
    {
        pr[x].tat=(ct+1)-pr[x].at;
        pr[x].terminated=1;
        pr[x].remslice=0;
    }
    for(i=0;i<n;i++)
        {
            if(x == i)
            {
                continue;
            }
            if(pr[i].at<=ct && !pr[i].terminated)
            {
                ++pr[i].wt;
            }
        }
        printf("t=%d p%d\n",ct,x);
        ++ct;
    }
    //waiting time
    //print
    for(i=0;i<n;i++)
    {
        printf("PROCESS p%d\n",i+1);
        printf("RT : %d\n",pr[i].rt);
        printf("WT : %d\n",pr[i].wt);
        printf("TT : %d\n\n",pr[i].tt);
    }
    return 0;
}
// #include<stdio.h>
 
// int main()
// {
 
//   int cnt,j,n,t,remain,flag=0,tq;
//   int wt=0,tat=0,at[10],bt[10],rt[10];
//   printf("Enter Total Process:\t ");
//   scanf("%d",&n);
//   remain=n;
//   for(cnt=0;cnt<n;cnt++)
//   {
//     printf("Enter Arrival Time and Burst Time for Process Process Number %d :",cnt+1);
//     scanf("%d",&at[cnt]);
//     scanf("%d",&bt[cnt]);
//     rt[cnt]=bt[cnt];
//   }
//   printf("Enter Time Quantum:\t");
//   scanf("%d",&tq);
//   printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
//   for(t=0,cnt=0;remain!=0;)
//   {
//     if(rt[cnt]<=tq && rt[cnt]>0)
//     {
//       t+=rt[cnt];
//       rt[cnt]=0;
//       flag=1;
//     }
//     else if(rt[cnt]>0)
//     {
//       rt[cnt]-=tq;
//       t+=tq;
//     }
//     if(rt[cnt]==0 && flag==1)
//     {
//       remain--;
//       printf("P[%d]\t|\t%d\t|\t%d\n",cnt+1,t-at[cnt],t-at[cnt]-bt[cnt]);
//       wt+=t-at[cnt]-bt[cnt];
//       tat+=t-at[cnt];
//       flag=0;
//     }
//     if(cnt==n-1)
//       cnt=0;
//     else if(at[cnt+1]<=t)
//       cnt++;
//     else
//       cnt=0;
//   }
//   printf("\nAverage Waiting Time= %f\n",wt*1.0/n);
//   printf("Avg Turnaround Time = %f",tat*1.0/n);
  
//   return 0;
// }

