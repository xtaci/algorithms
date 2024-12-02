//Actvity Selection problem
#include<stdio.h>
int main()
{
	int n,i;
	//Taking the no. of desired activities as input
	printf("Enter the no. of activities desired to be performed by the person: ");
	scanf("%d",&n);
	//one row to store the starting times and other to store their original position as inputted by user
	int s[2][n];
	//list of finishing times
	int f[n];
	printf("Enter the start time of each activity: ");
	for(i=0;i<n;i++){
		scanf("%d",&s[0][i]);
		s[1][i]=i; }
	printf("Enter the finish time of each activity(in same order): ");
	for(i=0;i<n;i++)
		scanf("%d",&f[i]);
	//sorting by finish times
	for(i=0;i<n-1;i++)
	{
		int j=i+1;
		int min=i;
		while(j<n)
		{
			if(f[j]<f[min])
				min=j;
			j++;
		}
		if(f[min]<f[i])
		{
			int temp=f[min];
			f[min]=f[i];
			f[i]=temp;
			temp=s[0][min];
			s[0][min]=s[0][i];
			s[0][i]=temp;
			temp=s[1][min];
			s[1][min]=s[1][i];
			s[1][i]=temp;
		}
	}
	printf("Maximum set of activities that can be performed by person (in order same as in input list): ");
	//printing first activtity in sorted list, since it finishes earliest (A GREEDY CHOICE)
	printf("%d ",s[1][0]+1);
	int k=0;
	for(i=1;i<n;i++)
	{
		if(s[0][i]>=f[k])
		{
			printf("%d ",s[1][i]+1);
			k=i;	
		}	
	}
	return 0;	
}
