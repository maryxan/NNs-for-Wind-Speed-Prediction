#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cluster.h"
#include "update.h"
#include "manhattan.h"


void update1(Space_ptr p, int k, cluster_ptr centroids,int size, int diastaseis) //simplest
{
	int i,j,l;
	double Sum,MO;
	
	for(i = 0;i < k ;i++) //gia kathe kentro
	{	
		for(l = 0;l < diastaseis; l++) //gia kathe diastasi
		{	
			Sum = 0;
			for(j = 0;j < size; j++) //gia kathe shmeio
			{	
				if(strcmp(centroids[i].key,p->array[j].centroid->key) == 0) //swsta dialegei ta antistoixa shmeia tou cluster
				{
					Sum += p->array[j].dim[l];
				}
			}
			MO = (double)(Sum / centroids[i].size); //vriskoume thn kainouria diastasi 
			centroids[i].dim[l] = MO;
		}


	}	




}



void update2(Space_ptr p, int k, cluster_ptr centroids,int size, int diastaseis) //PAM
{

	double *distances;
	double min; //gia na vroume to minimum MAX distance sum twn shmeiwn
	int i,j,z,min_thesi,metritis;
	for (i = 0 ; i < k; i++)
	{
		distances = (double *)malloc(centroids[i].size * sizeof(double));
		int index[centroids[i].size];
		metritis = 0;

		
		for(j = 0;j < size; j++)
		{
			if(strcmp(p->array[j].centroid->key, centroids[i].key) == 0) // gia kathe object mesa sto cluster
			{ 
				distances[metritis] = 0;
				for(z = 0;z < size; z++) //vriskw thn apostash tou apo kathe allo object mesa sto idio cluster
				{
					if(strcmp(p->array[z].centroid->key, centroids[i].key) == 0) //mpainei para polles fores
					{
						distances[metritis] += Manhattan_dist(p->array[j].dim,p->array[z].dim,diastaseis);
					}


				}
				index[metritis] = j;
				metritis++;


			}


		}
	
		min = 999999.999;
	
		for(j = 0;j < centroids[i].size; j++)
		{
			if(distances[j] < min) 
			{
				min = distances[j];
				min_thesi = j;
			}

		}

		memcpy(centroids[i].dim,p->array[index[min_thesi]].dim,diastaseis * sizeof(double)); //to vrika to lathos! to p->array[min_thesi] den einai swsto giati to index tou distances einai diaforetiko apo to index tou p->array giati to distances einai mono iso me to size tou cluster enw to p->array exei size iso me ton xwro twn shmeiwn!!!

		strcpy(centroids[i].key,p->array[index[min_thesi]].key);
		free(distances);
	}
	
		




}




