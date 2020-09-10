
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>
#define SIZE 100


void disp(int [], int);
void quick_sort(int [], int, int);

int main()
{

	int arr[SIZE],n,i,choice;
	pid_t newpid;
	char buffer[25];

	printf("\n\t\t*****MAIN PROCESS*****\n");
	printf("Process id:- %d\n", getpid());
	printf("Parent id:- %d\n", getppid());

	printf("Enter the size of array:- ");
	scanf("%d",&n);

	printf("\nInsert the elements in the array:- \n");
	for(int i=0;i<n;i++)
	{
		printf("Enter element no. [%d]:- ", i + 1);
		scanf("%d", &arr[i]);
	}
	printf("\nUnsorted array is:- ");
	disp(arr,n);

	printf("\n\n\t\t*****Orphan and Zombie process*****\n\n");
	printf("1)Zombie\n2)Orphan\n3)Exit\n");
	printf("Enter your choice:- ");
	scanf("%d",&choice);

	printf("\nForking the process");
	newpid = fork();

	switch(choice)
	{
		case 1:			
			if(newpid == -1)
				printf("\nChild was not born\n");
			else if(newpid == 0)
			{
				printf("\nNow in the child process!\n");
				printf("Child process id is %d\n", getpid());
				printf("Parent process id is %d\n", getppid());		
				printf("Sorted Array :- ");
				quick_sort(arr,0,n-1);
				disp(arr,n);
				printf("\nChild executed successfull!\n");
				printf("\n\t\t*****Child is now in zombie state*****\n\n");
			}
			else
			{
				sleep(10);
				printf("\nNow in parent process!\n");
				printf("My id is %d\n", getpid());
				printf("Sorted Array :- \n");
				quick_sort(arr,0,n-1);
				disp(arr,n);
				printf("\nParent executed successfully!\n");
				 system("ps -al | grep ass2a");
				exit(0);
			}
			break;
		case 2:
			if(newpid == -1)
				printf("\nChild was not born\n");
			else if(newpid == 0)
			{
				printf("\nNow in the child process!\n");
				printf("Child process id is %d\n", getpid());
				printf("My parent before sleep is %d\n", getppid());
				printf("Sorted Array :- ");
				quick_sort(arr,0,n-1);
				disp(arr,n);
				sleep(10);
				printf("\nMy parent after sleep() is %d\n", getppid());	
				printf("\n\t\t*****Child executed successfully*****\n");
			}
			else
			{
				printf("\nNow in parent process!\n");
				printf("My id is %d\n", getpid());
				printf("Sorted Array :-  ");
				quick_sort(arr,0,n-1);
				disp(arr,n);
				printf("\nParent executed successfully\n");
				printf("\n\t\t*****Parent died, child is now orphan*****\n");				
				exit(0);
			}
			break;
		case 3:
			return 0;
		default:
			printf("\nInvalid choice, please try again\n");
	}
	return 0;
}

void disp(int arr[], int n)
{
	int i;
	printf("[");
 
	for(i=0;i<n-1;i++)
		printf(" %d, ", arr[i]);

	printf(" %d ]",arr[i]);
}

void quick_sort(int arr[],int first,int last)
{

    int i,j,k,pivot,cmp=0,swap=0,temp;

    if(first<last)
    {
        pivot=first;
        i=first;
        j=last;

        while(i<j)
        {
            while(arr[i] <= arr[pivot] && i<last)
                i++;

            while(arr[j] > arr[pivot])
                j--;

            cmp++;
            if(i<j)
            {
                swap++;
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }

        temp=arr[pivot];
        arr[pivot]=arr[j];
        arr[j]=temp;

        quick_sort(arr,first,j-1);
        quick_sort(arr,j+1,last);
    }
}

