#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cluster.h"
#include "init.h"
#include "manhattan.h"
#include "update.h"



void set_cluster(cluster_ptr temp,cluster_ptr setter,int k,int diastaseis) //thetoume ena temp_cluster pinaka iso me ta clusters ta opoia tha allaksoun sto epomeno update!!!
{
	int i;
	for(i = 0;i < k; i++)
	{
		memcpy(temp[i].dim,setter[i].dim,sizeof(double) * diastaseis);

	}



}




int is_same(cluster_ptr cluster_temp,cluster_ptr clusters,int k,int diastaseis) //elegxoume an 2 pinakes me clusters einai idioi!
{
	int i,j;
	int flag = 0;
	for(i = 0;i < k; i++)
	{
		for(j = 0;j < diastaseis; j++)
		{
			if(cluster_temp[i].dim[j] != clusters[i].dim[j])
			{
				flag = 1;
				break;
			}

		}
		if(flag) break;

	}

	if(flag) return 0;
	else
	{
		return 1;

	}
	

}



int main(int argc, char **argv)
{
	char *inputfile;
	char *outputfile;
	char *configfile;

	/*----------------------------------------elegxos arguments-------------------------------------------*/

	if (argc == 7) //ginontai oi aparaithtoi elegxoi gia thn egkyrothta twn arguments!!!
	{
		if(strcmp(argv[1],"-i") == 0)
		{
			inputfile = argv[2];	
		}
		else
		{
			printf(" You need to type: ./cluster -i <inputfile> -c <configfile> -o <outputfile>\n");
			return -1;
		}
		if(strcmp(argv[3],"-c") == 0)
		{
			configfile = argv[4];	
		}
		else
		{
			printf(" You need to type: ./cluster -i <inputfile> -c <configfile> -o <outputfile>\n");
			return -1;
		}
		if(strcmp(argv[5],"-o") == 0)
		{
			outputfile = argv[6];	
		}
		else
		{
			printf(" You need to type: ./cluster -i <inputfile> -c <configfile> -o <outputfile>\n");
			return -1;
		}

	}
	else
	{
		printf(" Wrong number of arguments! Type: ./cluster -i <inputfile> -c <configfile> -o <outputfile>\n");
		return -1;
	}
	
	/*--------------------------------------------------------------------------------------------------------------*/

	/*------------------------------------diavasma tou config file gia tis parametrous------------------------------*/

	int k;
	int hash_tables;
	int hash_functions;
	int grids;

	FILE *cf;
	cf = fopen(configfile,"r");
	if(cf == NULL)
	{
		perror("Lathos inputfile onoma..\n");
      		return(-1);
	}

	char cffile_line[100];
	const char s2[2] = " ";
	char *cf_tok;
	int cfi;
	for(cfi = 0;cfi < 4; cfi++)
	{
		fgets(cffile_line,100,cf);
		cf_tok = strtok(cffile_line,s2);
		cf_tok = strtok(NULL,s2);
		switch(cfi)
		{
			case 0:
				k = atoi(cf_tok);
				break;
			case 1:
				grids = atoi(cf_tok);
				break;
			case 2:
				hash_tables = atoi(cf_tok);
				break;
			case 3:
				hash_functions = atoi(cf_tok);
				break;
		}
	}

	
	

	printf("k: %d, grids: %d, hash_tables: %d, hash_functions: %d\n",k,grids,hash_tables,hash_functions);



	/*--------------------------------------------------------------------------------------------------------------*/

	/*------------------------------------diavasma tou arxeiou gia euresi diastasewn kai apothikeusi tous--------------*/


	/*----------------------------apo to onoma tou arxeiou pairnoume ton arithmo twn dianysmatwn!!!--------------------*/

	FILE *fp; // gia na diavasoume thn eisodo
	char file_line[2500];
	const char s3[2] = "	"; //gia thn strtok
	char *tok_file;
	int arithmos_simeiwn = 0;
	int arithmos_diastasewn = 0;


	fp = fopen(inputfile,"r");
	if(fp == NULL)
	{
		perror("Lathos inputfile onoma..\n");
      		return(-1);
	}

	fgets(file_line,2500,fp);
	fgets(file_line,2500,fp);
	tok_file = strtok(file_line,s3);
	while(tok_file != NULL)
	{
		tok_file = strtok(NULL,s3);
		if((tok_file != NULL) && (strcmp(tok_file,"\n") != 0)) arithmos_diastasewn++;
	}
	fclose(fp);

	fp = fopen(inputfile,"r");
	fgets(file_line,2500,fp);
	while(fgets(file_line,2500,fp))
	{
		arithmos_simeiwn++;
	} 
	fclose(fp);

	printf("NUMOFRECORDS: %d NUMOFDIMENSIONS: %d\n",arithmos_simeiwn,arithmos_diastasewn);


	/*------------------------------------------------------------------------------------------------------------------*/


	Space_ptr p = (Space_ptr)malloc(sizeof(Space)); //ftiaxnoume to xwro!!!
	p->array = (shmeio_ptr)malloc(arithmos_simeiwn * sizeof(shmeio));

	fp = fopen(inputfile,"r");
	int i,j;

	char *tok_temp;
	fgets(file_line,2500,fp); // h prwth leksi vectors..den th xreiazomaste
	i = 0;
	while(fgets(file_line,2500,fp))
	{
		j = 0;
		tok_temp = strtok(file_line,s3);
		strcpy(p->array[i].key,tok_temp); //pername to id tou shmeiou
		p->array[i].dim = (double *)malloc(arithmos_diastasewn * sizeof(double));  //desmeuoume xwro gia tis diastaseis tou kathe simeiou!!!	
		char temporary[20];
		while((tok_temp = strtok(NULL,s3)) != NULL)
		{
			strcpy(temporary,tok_temp);
			double dd;
			sscanf(temporary, "%lf", &dd);
			if(strcmp(temporary,"\n") != 0) p->array[i].dim[j] = dd; //pername tin timi tis kathe diastasis!
			j++;

		}
		i++;
	}
	fclose(fp);




	/* ----------------------------------kalw oles tis parallages------------------------------------*/

	int threshold; // = 0;
	int total_sum = 0;
	int flag_is_same; // = 0;
	cluster_ptr clusters;
	//cluster_ptr clusters = init2(p,k,arithmos_simeiwn,arithmos_diastasewn);
	cluster_ptr cluster_temp;
	cluster_temp = (cluster_ptr)malloc(k * sizeof(cluster));
	for(i = 0;i < k; i++) //ftiaxnoume kai arxikopoioume to cluster_temp, pou einai enas pinakas pou tha krataei ta prohgoumena kentra prin to kainourio update kai assignment
	{
		cluster_temp[i].dim = (double *)malloc(arithmos_diastasewn * sizeof(double));
	} 

	FILE *wf;
	wf = fopen(outputfile,"w"); //anoigoume to outputfile gia ta apotelesmata kai ta statistika!!!

	int z,v,n;

	for(n = 0;n < 1; n++)
	{

		for(v = 0;v < 2; v++)
		{
	
			for(z = 0; z < 2; z++)
			{
				threshold = 0;
				flag_is_same = 0;

				if(z == 0) clusters = init1(p,k,arithmos_simeiwn,arithmos_diastasewn);
				else
				{
					clusters = init2(p,k,arithmos_simeiwn,arithmos_diastasewn);
				}

	
				while((!flag_is_same) && (threshold <= 10)) //oso ta kentra einai diaforetika kai den exoume kseperasei 10 epanalipseis
				{
					printf("comb: n: %d, v: %d, z: %d\n",n,v,z);
					total_sum = 0;
					if(v == 0) assignment1(p,k,clusters,arithmos_simeiwn,arithmos_diastasewn);
					else
					{
 						assignment1(p,k,clusters,arithmos_simeiwn,arithmos_diastasewn); //edw assignment2 kanonika!!!
					}	
					set_cluster(cluster_temp,clusters,k,arithmos_diastasewn);
					if(n == 0) update1(p,k,clusters,arithmos_simeiwn,arithmos_diastasewn);
					else
					{
						update2(p,k,clusters,arithmos_simeiwn,arithmos_diastasewn);
					}
					if(is_same(cluster_temp,clusters,k,arithmos_diastasewn)) flag_is_same = 1;
					threshold++;
					printf("threshold: %d\n",threshold);
				}
				for(i = 0;i < arithmos_simeiwn; i++)
				{
		
					total_sum += Manhattan_dist(p->array[i].dim,(p->array[i].centroid)->dim,arithmos_diastasewn);
				}
				fprintf(wf,"ALGORITHM: I%dA%dU%d :\n",z + 1,v + 1,n + 1); //ektypwnoume sto outputfile
				for(i = 0;i < k; i++)
				{
					if(n == 0)
					{
						fprintf(wf,"cluster%d: key:%s \n",i,clusters[i].key);
						for(j = 0;j < arithmos_diastasewn; j++)
						{
							fprintf(wf, "%lf ",clusters[i].dim[j]);

						}
						fprintf(wf,"\n");

					}
					else
					{
						fprintf(wf,"cluster%d: key:%s\n",i,clusters[i].key);
					}
				}
				fprintf(wf,"TOTAL SUM: %d\n\n",total_sum);
			}
		}
	}


	fclose(wf);


/*---------------------------------free tin mnimi pou desmeusame gia Space shmeiwn kai clusters/cluster_temp--------------*/
	for(i = 0;i < k; i++)
	{
		free(cluster_temp[i].dim);
		free(clusters[i].dim);

	}
	free(cluster_temp);
	free(clusters);
	total_sum = 0;

	for(i = 0;i < arithmos_simeiwn; i++)
	{
		free(p->array[i].dim);
	}
	free(p->array);
	free(p);



/*-------------------------------------------------------------------------------------------------------------------------*/

	/*for(i = 0;i < arithmos_simeiwn; i++)
	{
		total_sum += Manhattan_dist(p->array[i].dim,(p->array[i].centroid)->dim,arithmos_diastasewn);
	}*/


}
