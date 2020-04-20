
#include<stdio.h>
#include<stdlib.h>
#define MINVAL -999
struct sparsematrix
{
	int row,col,data;
	struct sparsematrix* link;
};

typedef struct sparsematrix node;
typedef node* list;

list create(list,int,int);
list createnode();
int length(list);
list delete(list,int);
list merge(list,list,list);
list addition(list,list,list);
void display(list);
list insert(list,int,int,int);
void matrix_display(list,int,int);
list multiply(list mtx1,list mtx2,int row1,int row2,int col2);
list sortLL(list);
list insertAtBeg(list first, list sum);

							
int main()
{  
    list mtx1=NULL,mtx2=NULL,mtx=NULL,temp,flag1,flag2;   
    int m1,n1,m2,n2,optn,key;
    printf("Enter no. of Column for matrix 1:\n");
    scanf("%d",&n1);
    printf("Enter no. of Row for matrix 1:\n");
    scanf("%d",&m1);
    printf("Enter no. of Column for matrix 2:\n");
    scanf("%d",&n2);
    printf("Enter no. of Row for matrix 2:\n");
    scanf("%d",&m2);

     printf("Enter Elements in matrix 1: \n"); // Taking input in matrix via linklist
		         do
		         {  
		    	 	mtx1=create(mtx1,n1,m1);       //Matrix 1
		    	   	printf("To Stop enter -999....Press any key to continue:");
		         	scanf("%d",&key);
	   	         }while(key!=MINVAL);
		    	 display(mtx1);
		         key=0;
		         printf("Enter Elements in matrix 2:\n");
		 	     do
		 	     {  
		         	mtx2=create(mtx2,n2,m2);    //Matrix 2
	 	        	printf("To Stop enter -999....To Continue:");
		    	    scanf("%d",&key);
		    	 }while(key!=MINVAL);
		         display(mtx2);

		         flag1=mtx1;
		         flag2=mtx2;
  
   do
   {
     printf("1.ADDITION  2.MULTIPLICATION\n");
     printf("Enter Option: ");
     scanf("%d",&optn);
     switch(optn)
     {
        case 1: 
        	if(m1!=m2 || n1!=n2)    //condition check for matrix addition
        		printf("Addition not possible:\n");
            else 
            {
		        
		         mtx=addition(mtx1,mtx2,mtx);      // Calling Addition function
		         printf("Added List:- ");
		         display(mtx); 
		         matrix_display(mtx,n1,m1);  //Display of Result Matrix                   
		     }        	        	 
        	 break;
        case 2:
        	if(m2!=n1)
            	printf("MULTIPLICATION not possible:\n");
            else
            {
		        mtx1=flag1;
		        mtx2=flag2;

		           printf("\n");
		           	mtx1=sortLL(mtx1);
		           display(mtx1);
		           
		           mtx2=sortLL(mtx2);
		           display(mtx2);
		           printf("\n");


		    	 mtx=multiply(mtx1,mtx2,m1,m2,n2);
		    	 
		    	 display(mtx);
		    	 matrix_display(mtx,n1,m2);
        	}
        	break;
        }
	}while(optn!=0);
	return 0;
}
//Function to create node in linklist
list createnode()
{
	list neww;
	neww=(list)malloc(sizeof(node));
	if(neww==NULL)
		printf("\n Memory Underflow\n");
    neww->link=NULL;
    return neww;
}
//Function to insert element in linklist
list create(list mtx,int n,int m)
{
    list neww,temp;
    int flag;
	neww=createnode();    
	if(neww==NULL)
		return mtx;
    do
    {
        flag=0;  
        printf("Enter Column number: ");
        scanf("%d",&neww->col);
        if(neww->col >= n)
        {
            flag=1;
            printf("Invalid Column\n");   
        }
     }while(flag);
  	do
  	{
  	    flag=0;
        printf("Enter Row number: ");
        scanf("%d",&neww->row);
        if(neww->row >= m)
        {
            flag=1;
            printf("Invalid Column\n");
        }
    }while(flag);
    printf("Enter the element ");
    scanf("%d",&neww->data);
	neww->link=NULL;
	if(mtx==NULL)
		return neww;
	temp=mtx;
	while(temp->link!=NULL)
		temp=temp->link;        
	temp->link=neww;
	return mtx;
}
//Function to merge to list
list merge(list mtx,list mtx1,list mtx2)
{
    while(mtx1!=NULL)
    {
         mtx=insert(mtx,mtx1->data,mtx1->row,mtx1->col);
         mtx1=mtx1->link;
    }    
    while(mtx2!=NULL)
    {
         mtx=insert(mtx,mtx2->data,mtx2->row,mtx2->col);
         mtx2=mtx2->link;
    } 
    return mtx;
}
//Main Addition Function
list addition(list mtx1,list mtx2,list mtx)
{
    int x=0,a=0,b=0;
	list temp,m;
    mtx=merge(mtx,mtx1,mtx2);        //Mergeing both matrix
    //temperory list variables
    m=mtx;
    temp=mtx2;     
    while(mtx!=NULL && a!=length(mtx1))
    { 
        x=0;
        temp=mtx2;
        while(temp!=NULL)
        {  
           x++;
           if(mtx->row==temp->row && mtx->col==temp->col)
        	 {   
        		  mtx->data=mtx->data+temp->data;  //Addition of data which has column and row same in both matrix
        		  m=delete(m,length(mtx1)+x-b);     //Deleting one of the node from above added
                  b++;
                  temp=temp->link;
        	      break;
        	}
          temp=temp->link;
        }
        mtx=mtx->link;
        a++;
    }
   return m;
}
//Used in merging two list in to otner new linklist
list insert(list mtx,int sum,int c,int r)
{
	list neww,temp;
	neww=createnode();
	if(neww==NULL)
		return mtx;
	neww->data=sum;
	neww->row=c;
	neww->col=r;
	neww->link=NULL;
	if(mtx==NULL)
	{
	   mtx=neww;
		return mtx;
    }
	temp=mtx;
	while(temp->link!=NULL)
		temp=temp->link;
	temp->link=neww;
	return mtx;
}

//Displaying in linklist form
void display(list matrix)
{
    	while(matrix!=NULL)
    	{
    		printf("%d-%d-%d--->",matrix->row,matrix->col,matrix->data);
    		matrix=matrix->link;
        }
    	printf("NULL\n");
}
//Length  of list
int length(list mtx)
{
	int len=0;
	if(mtx==NULL)
		return 0;
    while(mtx!=NULL)
    {
    	mtx=mtx->link;
    	len++;
    }
    return len;
}
//Deleteing a node in list
list delete(list mtx,int pos)
{
	int idx=1,len=length(mtx);
    list temp,temp2; 
     if(pos<0 || pos>len)
	{
		printf("Wrong position\n");
		return mtx;
	}
    temp=mtx;
    if(pos==1)
    {
    	mtx=mtx->link;
    	free(temp);
    	return mtx;
    }
    while(idx<pos-1)
    {
    	idx++;
    	temp=temp->link;
    }
    temp2=temp->link;
    temp->link=temp2->link;
    free(temp2);
    return mtx;
}
//Displaying in Matrix Form
void matrix_display(list mtx,int n,int m)
{   
    list temp;
    int a,b,count=0;
    for(a=0;a<n;a++)
    { //temp=mtx;
        for(b=0;b<m;b++)
        { 
          count=0;
          temp=mtx;
          while(temp!=NULL)
          { 
             if(temp->row==a && temp->col==b)
             { 
                printf("%d ",temp->data);
                count=1;
                 break;
             }
             temp=temp->link;
          }
             if(count!=1)
                 printf("0 ");
         }
         printf("\n");
     }
}

list multiply(list mtx1,list mtx2,int row1,int row2,int col2)
{
    list temp1,temp2,mtx3=NULL,sum=NULL;
    int i,j,k;
	display(mtx1);
	display(mtx2);
	temp1=mtx1;

	temp2=mtx2;
    
    sum=createnode();
	for(i=0;i<col2;i++)
	{   
	    for(j=0;j<row1;j++)
	    {   
	        sum->data=0;
	        
	        

	        for(k=0;k<row2;k++)
	        {  temp1=mtx1;
	         while(temp1!=NULL)
	        	{
	        	  if(temp1->row==j && temp1->col==k)
	        	  {  temp2=mtx2;
                      while(temp2!=NULL)
                      {
                      	if(temp2->row==k && temp2->col==i)
                      	{   sum->row=j;
	                        sum->col=i;
	                        
                      		sum->data=sum->data+(temp1->data*temp2->data);
                      		
                      		break;
                      	}
                      	temp2=temp2->link;
                      }
                      break;
	        	  }
	        	  temp1=temp1->link;
	           
	            }   
	             
	        }
	        
	        if(sum->data!=0)
	        mtx3=insertAtBeg(mtx3,sum);
	    }
	   
     } 
     return mtx3;     
}

list sortLL(list mtx)
{
	list i,j;
	int key,k2,k3;
	if(mtx==NULL || mtx->link==NULL)
		return mtx;
	key=0;
	i=mtx;
	//display(mtx);
	for(i=mtx;(i->link)!=NULL;i=(i->link))
	{
		for(j=(i->link);j!=NULL;j=(j->link))
		{
			if((i->row)>(j->row))
			{
				key=i->row;
				k2=i->col;
				k3=i->data;

				i->row=j->row;
				i->col=j->row;
				i->data=j->data;

				j->row=key;
				j->col=k2;
				j->data=k3;

			}
			
		}
	}
key=0;
i=mtx;
	for(i=mtx;(i->link)!=NULL;i=(i->link))
	{
		for(j=(i->link);j!=NULL;j=(j->link))
		{
			if((i->col)>(j->col))
			{
				key=i->col;
				k2=i->row;
				k3=i->data;

				i->col=j->col;
				i->row=j->row;
				i->data=j->data;

				j->col=key;
				j->row=k2;
				j->data=k3;

			}
		}
	}
	//display(mtx);
	return mtx;
}


list insertAtBeg(list first, list sum)
{
    list neww;
    neww=createnode();
    neww->data=sum->data;
    neww->link=first;
    neww->row=sum->row;
    neww->col=sum->col;
    return neww;
}
