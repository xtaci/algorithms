#include<stdio.h>
#include<conio.h>
int a[100][100],b[100][100],c[100][100],row,col;
void bestbride();
void selectgirl();
int identify_qualities(int ,int );
void maxattr();
void selectgirl()
{
  int i,j;
  for(i=0;i<row;i++)
  {
    if(i==0)
    {
      for(j=1;j<col;j++)
      {
        if(a[i][j]==1)
          b[i][j]=identify_qualities(i,j);
      }
    }
    else
    {
      for(j=0;j<col;j++)
      {
        if(a[i][j]==1)
          b[i][j]=identify_qualities(i,j);
      }
    }
  }
}
int identify_qualities(int i,int j)
{
  int count=0;
  count++;
  if(a[i+1][j] ==1 && i+1<row)
  {
    count++;
  }
  if(a[i][j+1] == 1 && j+1<col)
  {
    count++;
  }
  if(a[i-1][j] == 1 && i-1>=0)
  {
    count++;
  }
  if(a[i][j-1] == 1 && j-1>=0)
  {
    count++;
  }
  if(a[i+1][j+1] == 1 && i+1<row && j+1<col)
  {
    count++;
  }
  if(a[i-1][j-1] == 1 && i-1>=0 && j-1>=0)
  {
    count++;
  }
  if(a[i+1][j-1] == 1 && i+1>=0 && j-1>=0)
  {
    count++;
  }
  if(a[i-1][j+1] == 1 && i-1>=0 && j+1>=0)
  {
    count++;
  }
  return count;
}
void maxattr()
{
  int i,j,max=0;
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(max<b[i][j])
      {
        max=b[i][j];
      }
    }
  }
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(max==b[i][j])
      {
        c[i][j]=1;
      }
      else
      {
        c[i][j]=0;
      }
    }
  }
}
void bestbride()
{
  int i,j,max;
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(i==j)
      {
        if(c[i][j]==1)
        {
          c[i][j]=i;
        }
      }
      else
      {
        if(c[i][j]==1)
        {
          c[i][j]=i+j;
        }
      }
    }
  }
  max=-1;
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(max<c[i][j])
        max=c[i][j];
      if(max==c[i][j])
        printf("Polygamy not allowed");
    }
  }
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(max==c[i][j])
      {
        printf("%d:%d:%d",i+1,j+1,b[i][j]-1);
        break;
      }
    }
  }
}
int main()
{
  int i,j,flag=0;
  scanf("%d%d",&row,&col);
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      scanf("%d",&a[i][j]);
    }
  }
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(i==1 && j==1)
        continue;
      else if(a[i][j]==1)
        flag=1;
    }
  }
  if(flag=1)
    printf("No suitable girl found");
  else
  {
    selectgirl();
    maxattr();
    bestbride();
  }
  return 0;
}
