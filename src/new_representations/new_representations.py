import sys
import keras
import numpy as np 
import pandas as pd
from keras import layers, optimizers, losses, metrics
from keras.models import load_model
from keras.models import Model

#elegxos arguments
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
#kateuthian me th Model
interm_layer_model = Model(inputs=model.input, outputs=model.get_layer(layer_name).output)
interm_output = interm_layer_model.predict(data.values)


#write to output file
outname='new_representations.csv'
with open(outname, 'w') as filehandle:
    for i in range(len(data.index)):
        y_str=data.index[i]
        for j in range(len(interm_output[i])):
            y_str=y_str+','+str(interm_output[i][j])
        filehandle.write('%s\n' %(y_str))
print(outname,'  written')

