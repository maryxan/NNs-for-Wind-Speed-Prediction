
import sys
import keras
import numpy as np 
import pandas as pd
from keras import layers, optimizers, losses, metrics
from keras.models import load_model

#elegxos arguments gia filepath
if len(sys.argv) != 3:
	print("Wrong number of arguments!")
	sys.exit()
else:
	if (sys.argv[1] != "-i"):
		print("Wrong arguments!")
		sys.exit()
	else:
		filename = sys.argv[2]


#diavazoume to nn_representations kai to actual

data = pd.read_csv(filename,header=None,index_col=0)
actual_data = pd.read_csv("actual.csv",header=None,index_col=0) #diavazoume kai ta actual data
print(data.shape)







#=========================================================================#


#==============gia na kanoume load to pre-trained NN kai compile=====================#


model = load_model("WindDenseNN.h5")
model.compile(optimizer='rmsprop',loss='mse',metrics=['mae','mse'])
model.summary()
result = model.predict(data,batch_size=32)
print(result.shape)
print(actual_data.shape)
print(result)


scores = model.evaluate(data, actual_data,batch_size=32)
print(scores)
print('mae=%f, mse = %f' %(scores[0],scores[1])) 

#vriskw mae kai mse me thn evaluate alla to mape xwrista mono tou giati exei thema me tis diaireseis me to 0

#open file for output
f = open("output.txt","a")

rows = actual_data.shape[0]
columns = actual_data.shape[1]


#===================== ypologizw to mape ======================

rel_sum = 0
for i in range(rows - 1):
	Sum = 0
	actual_sum = 0
	for j in range(columns - 1):
		Sum += result[i,j]
		actual_sum += actual_data.iloc[i,j]
	Sum = Sum / columns #vriskw ta mesa twn grammwn pou den tha einai sigoura 0 gia na apofigw to provlima!
	actual_sum = actual_sum / columns
		
	rel_sum += (abs((actual_sum - Sum) / actual_sum))


rel_sum = ((rel_sum / rows) * 100)


#==============================================================



#ektypwsi twn MAE,MAPE kai SAPE sto arxeio
f.write('MAE : %f,	MSE: %f,	MAPE: %f\n' %(scores[1],scores[0],rel_sum))




#ektypwnw ta predicted
for i in range(rows):
	y_str=data.index[i]
	for j in range(columns):
		y_str=y_str+','+str(result[i][j])
	f.write('%s\n' %(y_str))
f.close() #close file

print("output file written in folder!")

		




