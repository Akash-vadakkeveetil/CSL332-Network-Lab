//distance vector routing protocol
//the belliam ford algortihm    
#include<stdio.h>
struct node {
    unsigned dist[20];  // Array to store distances to other nodes
    unsigned nexthop[20];  // Array to store next hop information
} rt[10];  // Array of routing tables, one for each node

void main()
{
    int costmat[20][20];
    int nodes,i,j,k,count =0;
    printf("Enter the number of nodes\n: ");
    scanf("%d",&nodes);
    printf("Enter the cost matrix\n:");
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            scanf("%d",&costmat[i][j]);//the cost between i and j th nodes
            costmat[i][i] = 0;//cost from the node to itself is zero
            rt[i].dist[j] = costmat[i][j];//the distance of i to j is stored in routing table of i
            rt[i].nexthop[j] = j;//the node which corresponds to the paraticular distance
        }
    }

    do
    {
        count = 0;
        for(i=0;i<nodes;i++)
        {
            for(j=0;j<nodes;j++)
            {
                for(k=0;k<nodes;k++)
                {
                    if(rt[i].dist[j] > costmat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].nexthop[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);//do until no more updates are made
    for(i=0;i<nodes;i++)
    {
        printf("\n For router %d\n",i + 1);
        for(j=0;j<nodes;j++)
        {
            printf("\t\nnodes %d via %d Distance %d",j+1,rt[i].nexthop[j]+1,rt[i].dist[j]);
        }
    }
    printf("\n");
    
}