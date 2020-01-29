



import sys
import numpy as np 
import pandas as pd
from sklearn.cluster import KMeans
from sklearn import metrics
from sklearn.metrics import silhouette_samples, silhouette_score

#elegxos arguments
if len(sys.argv) != 5:
	print("Wrong number of arguments!")
	sys.exit()
else:
	if (sys.argv[1] != "-i"):
		print("Wrong arguments!")
		sys.exit()
	else:
		filename = sys.argv[2]

	if (sys.argv[3] != "-n"):
		print("Wrong arguments!")
	else:
		n_clusters = int(sys.argv[4])


new_data = pd.read_csv(filename, index_col=0, header=None)
new_data.index=[pd.to_datetime(d) for d in new_data.index ]


# ### calculate day averages



new_data_av=(new_data.resample('D').sum())/24
len(new_data_av.index)






# ## Clustering 



kmeans = KMeans(n_clusters=n_clusters, random_state=0).fit(new_data.values)
centers=kmeans.cluster_centers_
labels = kmeans.labels_
silh = metrics.silhouette_score(new_data.values, labels, metric='cityblock')
print('average silhouette score for',n_clusters,'clusters:',silh)







#  clustering gia day_averaged vectors
kmeans = KMeans(n_clusters=n_clusters, random_state=1).fit(new_data_av.values)
centers=kmeans.cluster_centers_
labels = kmeans.labels_
silh = metrics.silhouette_score(new_data_av.values, labels, metric='cityblock')
print('average silhouette score for averaged days and for',n_clusters,'clusters:',silh)



# ### statistics



lbls=pd.Series(map(int,labels),index=new_data_av.index)
cluster_frame=pd.DataFrame({'labels':lbls})
cluster_frame.index.name='Date'


stat=np.zeros((n_clusters,12),dtype=int)
for i in range(12):
    cl1 = cluster_frame.loc[cluster_frame.index.month==i+1]
    for j in range(n_clusters):
        cl2 = cl1.loc[cl1.loc[:,'labels']==j,:]  # get the members of cluster 1
        stat[j,i]=len(cl2.index)




# Kathe stili antiproswpeuei thn katanomi twn omadopoihmenwn dianysmatwn (labels) ana mhna
print("Katanomi ana mina (stili) :")
print(stat)  







