//congestion control protocol leaky bucket
#include<stdio.h>
void main()
{
    int b_size,rate,n,inc,store= 0;
    printf("Enter the bucket size\n");
    scanf("%d",&b_size);
    printf("Enter the outgoing rate\n");
    scanf("%d",&rate);
    printf("Enter the number of inputs\n");
    scanf("%d",&n);
    while(n!=0)
    {
        printf("Enter the incoming packet size\n");
        scanf("%d",&inc);
        if(inc <= (b_size-store))
        {
            store += inc;//the packet is stored in memory
            //after allocating we have to show how much space is available
            printf("The bucket buffer size is %d out of %d\n",store,b_size);
        }
        else
        {
            printf("Dropped packets are %d\n",inc - (b_size-store));
            store = b_size;
            printf("The bucket buffer size is %d out of %d\n",store,b_size);
        }
        //the allocation part is now finished now the outgoing rate part 

        if(store >= rate)//the amount of buffer is greater than outgoing rate , like if there is enough quantity just update
        {
            store -= rate;
        }
        else{
            store = 0;//cause nothing will be there if its less than outgoing rate
        }
        printf("After outgoing , %d packets are left out of %d in buffer\n",store,b_size);
        n--;
    }
}
