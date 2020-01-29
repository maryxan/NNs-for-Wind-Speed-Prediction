#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment.h"
#include "manhattan.h"
//#include "cluster.h"




void assignment1(Space_ptr p, int k, cluster_ptr centroids,int size, int diastaseis)
{
	int i,j;
	double min_distance,temp;
	int deiktis;
	cluster_ptr temp_centroid;
	
	for(i = 0;i < k; i++)
	{
		centroids[i].size = 0;
		
	}
	
	for(i = 0;i < size; i++) //gia kathe shmeio sto xwro tha vrw to centroid tou
	{
		//p->array[i].centroid = (shmeio_ptr)malloc(sizeof(shmeio));
		min_distance = 999999.9999;
		deiktis = 0;
		for(j = 0;j < k; j++) 
		{
			temp = Manhattan_dist(p->array[i].dim,centroids[j].dim,diastaseis);
			if(temp < min_distance)
			{
				min_distance = temp;
				temp_centroid = &centroids[j];
				deiktis = j;
			}
		}
		p->array[i].centroid = temp_centroid;
		centroids[deiktis].size++; 


	}



}

