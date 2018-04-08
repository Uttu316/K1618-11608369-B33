
#include <stdio.h>
#include<conio.h>
struct process{
    int Arrival_Time,Burst_time,Priority,firstt,i,flag,rect,burl,compt,Waiting_time,TurnAround_Time;
}*run=NULL;
int n,tq,tburst=0;
struct node{
    struct process *q;
    struct node *next;
}*start=NULL,*last,*cn;
int main()
{
    printf("\nEnter total number of the processes you want to execute :");
    scanf("%d",&n);
    int pl=n; //process left
    printf("Enter the value of time quantum :");
    scanf("%d",&tq);  
    struct process p[n]; 
    for(int i=0;i<n;i++)
    {
        printf("\nEnter the details of process %d ",i+1);
        printf("\n\tArrival Time : ");
        scanf("%d",&p[i].Arrival_Time);
        printf("\tBurst Time : ");
        scanf("%d",&p[i].Burst_time);
        p[i].burl=p[i].Burst_time;
        tburst=tburst + p[i].Burst_time;
        printf("\tPriority : ");
        scanf("%d",&p[i].Priority);
        p[i].i=i+1;
        p[i].flag=0;
        p[i].rect=-1;
        p[i].firstt=-1;
    }
    printf("\n\n Details entered are following:");
    printf("\n _________________________________________________________________________________");
    printf("\n|\tPROCESS\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY |");
    printf("\n|_______________|_______________________|_______________________|________________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\tP%d\t|\t %d\t\t|\t\t%d\t|\t %d \t |",p[i].i,p[i].Arrival_Time,p[i].Burst_time,p[i].Priority);
        printf("\n|_______________|_______________________|_______________________|________________|");
    }
        for(int time=0;pl!=0;time++)
    {
        for(int i=0;i<n;i++)                                                                    //priority increment
        {
            if(p[i].rect==-1 && p[i].flag==1)
            {
                if((time)%10==(p[i].Arrival_Time)%10)
                {
                    p[i].Priority++;
                    printf("\n\tPriority of process P%d increasing by 1.",p[i].i);
                    node *x;
                    x=start;
                    while(x->next->q->i==i)
                        x=x->next;
                    cn=new node;
                    cn->q=x->next->q;
                    cn->next=NULL;
                    x->next=x->next->next;
                    if(start==NULL)
                    {
                        last=cn;
                        start=cn;
                    }
                    else{
                        node *x;
                        x=start;
                        if((start->q->Priority)<(cn->q->Priority))
                        {
                            cn->next=start;
                            start=cn;
                        }
                        else
                        {
                             while(x->next!=NULL && x->next->q->Priority > cn->q->Priority)
                            {
                                x=x->next;
                            }
                            cn->next=x->next;
                            x->next=cn;
                        }
                    }
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            if(p[i].Arrival_Time==time && p[i].flag==0)                                                //in the queue
            {
            
                if(start==NULL)
                {
                	
                    p[i].flag=1;
                    cn=new node;
                    cn->q=&p[i];
                    cn->next=NULL;
                    last=cn;
                    start=cn;
                }
                else{
                    p[i].flag=1;
                    cn=new node;
                    cn->q=&p[i];
                    node *x;
                    x=start;
                    if((start->q->Priority)<(cn->q->Priority))
                    {
                        cn->next=start;
                        start=cn;
                    }
                    else
                    {
                    	
                        while(x->next!=NULL && x->next->q->Priority>= cn->q->Priority)
                        {
                            x=x->next;
                        } 
                        cn->next=x->next;
                        x->next=cn;
                    }
                }
            }
        }
    back:
        if(run==NULL)   //running of process
        {
            if(start!=NULL)
            {
                run=start->q;
                start=start->next;
                if(run->firstt==-1)
                {
                    run->firstt=time;
                }
                run->rect=time;
                
            }
        }
        if(run!=NULL && (time)<((run->rect)+tq) && run->flag!=2)
        {
            if(start!=NULL)
            {
                if(run->Priority < start->q->Priority &&  start->q->Arrival_Time == time)   //if higher priority process com in existence
                {
                    printf("\nContext switching happening as priority of process P%d is greater than priority of process P%d",start->q->i,run->i);
                    cn=new node;
                    cn->q=run;
                    cn->next=NULL;
                    node *x;
                    x=start;
                    while (x->next!=NULL && x->next->q->Priority > cn->q->Priority)
                    {
                        x=x->next;
                    }
                    cn->next=x->next;
                    x->next=cn;
                    run=NULL;
                    goto back;
                }
            }
            run->burl--;
            fflush(stdin);
            printf("\n\tprocess %d running at time %d",run->i,time);
            if(run->burl==0)                                                    //when process got completed
            {
                run->flag=2;
                pl--;
                run->compt=(time+1);
                run->TurnAround_Time=((run->compt)-(run->Arrival_Time));
                run->Waiting_time=((run->TurnAround_Time)-(run->Burst_time));
                run=NULL;
            }
            else if((time+1)==((run->rect)+tq))
            {
                cn=new node;
                cn->q=run;
                cn->next=NULL;
                if(start==NULL)
                {
                    last=cn;
                    start=cn;
                }
                else
                {
                    node *x;
                    x=start;
                    if((start->q->Priority)<(cn->q->Priority))
                    {
                        cn->next=start;
                        start=cn;
                    }
                    else
                    {
                        while(x->next!=NULL && x->next->q->Priority >= cn->q->Priority)
                        {
                            x=x->next;
                        }
                        cn->next=x->next;
                        x->next=cn;
                    }
                    run=NULL;
                }
            }
        }
    }
     printf("\n\n\n Details after scheduling are :");
    printf("\n __________________________________________________________________________________________________________________________");
    printf("\n|\tPROCESS\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY\t| WAITING TIME\t| TURN AROUND TIME |");
    printf("\n|_______________|_______________________|_______________________|_______________________|_______________|__________________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\tP%d\t|\t%d\t\t|\t%d\t\t|\t%d\t\t|\t%d     \t|\t    %d      |",p[i].i,p[i].Arrival_Time,p[i].Burst_time,p[i].Priority,p[i].Waiting_time,p[i].TurnAround_Time);
        printf("\n|_______________|_______________________|_______________________|_______________________|_______________|__________________|");
    }
    float Avg_Arrival_Time=0,Avg_TurnAround_Time=0;
    for(int i=0;i<n;i++)
    {
        Avg_Arrival_Time=Avg_Arrival_Time+p[i].Waiting_time;
        Avg_TurnAround_Time=Avg_TurnAround_Time+p[i].TurnAround_Time;
    }
    Avg_Arrival_Time=Avg_Arrival_Time/n;
    Avg_TurnAround_Time=Avg_TurnAround_Time/n;
    printf("\nAverage  waiting time = %f ",Avg_Arrival_Time);
    printf("\nAverage Turn Around Time = %f \n",Avg_TurnAround_Time);
    getch();
}
