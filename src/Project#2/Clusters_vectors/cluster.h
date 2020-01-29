

typedef struct cluster
{
	char key[10];
	double *dim;
	int size;
}cluster;

typedef struct cluster *cluster_ptr;


typedef struct shmeio 
{
	char key[12]; //to id tou shmeiou. Gia eukoleia einai statikos pinakas tha borouse na einai pointer
	double *dim;
	cluster_ptr centroid;
}shmeio;

typedef struct shmeio *shmeio_ptr;

typedef struct Space
{
	shmeio_ptr array;
}Space;

typedef struct Space *Space_ptr;





