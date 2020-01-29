import sys
import keras
import numpy as np 
import pandas as pd
from keras import layers, optimizers, losses, metrics
from keras.models import load_model
from keras.models import Model


if len(sys.argv) != 3:
	print("Wrong number of arguments!")
	sys.exit()
else:
	if (sys.argv[1] != "-i"):
		print("Wrong arguments!")
		sys.exit()
	else:
		filename = sys.argv[2]






model = load_model("WindDenseNN.h5")
model.summary()



#read input
data = pd.read_csv(filename,header=None,index_col=0)


#get new representations
layer_name = 'dense_1'


# =====================================#

interm_layer_model = Model(inputs=model.input, outputs=model.get_layer(layer_name).output)
interm_output = interm_layer_model.predict(data.values)


# grafoume sto outputfile se morfi gia na to treksoume sthn palia ergasia!!!
outname='cl_representations.csv'
temp_str = 'vectors'
with open(outname, 'w') as filehandle:
	filehandle.write('%s\n' %(temp_str))
	for i in range(len(data.index)):
		y_str = "item"
		y_str = y_str + str(i)
		y_str = y_str + "	"
		for j in range(len(interm_output[i])):
			y_str=y_str+str(interm_output[i][j])
			if(j != (len(interm_output[i]) - 1)):
				y_str = y_str + "	"
		filehandle.write('%s\n' %(y_str))
print(outname,'  written')

