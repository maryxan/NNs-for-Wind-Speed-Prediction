#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "manhattan.h"
#include "cluster.h"





cluster_ptr init1(Space_ptr p,int k,int size,int diastaseis) //k-means(simplest)
{
   	time_t t;
	srand((unsigned) time(&t));

	cluster_ptr centroids;
	centroids = (cluster_ptr)malloc(k * sizeof(cluster)); //desmeuoume mnimi gia ton pinaka kentrwn
	int i,j,index;
	char temp[4];
	
	for(i = 0; i < k; i++) 
	{
		sprintf(temp,"%d",i);
		centroids[i].dim = (double *)malloc(diastaseis * sizeof(double));
		index = rand() % size;  //dialegoume tyxaia ena index
		memcpy(centroids[i].dim,p->array[index].dim,sizeof(double) * diastaseis); 
		strcpy(centroids[i].key,temp);
		//printf("%s\n",centroids[i].key);
	}

	return centroids;


}





cluster_ptr init2(Space_ptr p,int k,int size,int diastaseis) //k-means++
{	
	time_t t;
	srand((unsigned) time(&t));

	cluster_ptr centroids;
	centroids = (cluster_ptr)malloc(k * sizeof(cluster));
	int i,j,z,index;
	double distance,x;
	double max,max_p;
	double *D, *P;
	char temp[4];

	D = (double*) malloc(size * sizeof(double));

	P = (double*) malloc(size * sizeof(double));

	if (D == NULL)
	{
		printf("Malloc: memory allocation error!\n");
		exit(3);
	}


	index = rand() % size; //vriskei ena tyxaio shmeio ston pinaka pou tha dialeksei to prwto centroid
	centroids[0].dim = (double *)malloc(diastaseis * sizeof(double));
	memcpy(centroids[0].dim,p->array[index].dim,sizeof(double) * diastaseis); //thetoume to prwto centroid
	strcpy(centroids[0].key,"0");

	for(i = 1;i < k; i++) //gia kathe centroid (pera apo to prwto pou dialeksame tyxaia!!!)
	{
		for(j = 0; j < size; j++) //arxikopoiw oles tis apostaseis twn shmeiwn se kati megalo gia na vrw meta thn mikroteri!!!
		{
			D[j] = 999999.999;
			P[j] = 0.0;
		}


		for(j = 0; j < size; j++) //gia kathe shmeio
		{
			for(z = 0 ; z < i ; z++) //mexri to twrino centroid
			{
				distance = Manhattan_dist(p->array[j].dim,centroids[z].dim,diastaseis);

				if(distance < D[j]) D[j] = distance; //kratame to minimum distance gia kathe shmeio!
			}
		}
		max = -999999.99;
		
		for(j = 0; j < size; j++) // vriskw to max twn min_distances
		{
			if (D[j] > max) max = D[j];
		}


		P[0] = pow((double)(D[0] / max),2);
		for(j = 1; j < size; j++) //xtizoume ton pinaka twn pithanotitwn!!!
 		{
				P[j] = P[j-1] + pow((double)(D[j]/max), 2);
		}



		max_p = P[size - 1];

		x = ((float)rand()/(float)(RAND_MAX)) * max_p;

		for(j = 0; j < size; j++)
		{
			if (x <= P[j])
			{
				centroids[i].dim = (double *)malloc(diastaseis * sizeof(double));
				memcpy(centroids[i].dim,p->array[j].dim,sizeof(double) * diastaseis); //to kanw iso me to shmeio sto index tis pithanotitas pou vrika!!! 
				sprintf(temp,"%d",i);
				strcpy(centroids[i].key,temp);
				break;
			}
		}
		


	}


	free(D);
	free(P);
	return centroids;




}


