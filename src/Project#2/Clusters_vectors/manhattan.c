#include <stdio.h>
#include "cluster.h"


double Manhattan_dist_single(double a,double b) //vriskei to manhattan distance dyo diastasewn mono!
{
	if((a-b) >= 0)
		return (a - b);
	else
	{
		return -(a - b);
	}


}


double Manhattan_dist(double *dim1, double *dim2,int diastaseis) //manhattan distance dyo shmeiwn (pernwntas ton pinaka diastasewn tous)
{
	int i;
	double Sum = 0.0;
	for(i = 0;i < diastaseis; i++)
	{
		Sum += Manhattan_dist_single(dim1[i],dim2[i]);
	}

	return Sum;


}
