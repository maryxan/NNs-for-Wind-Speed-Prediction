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

weights = model.layers[0].get_weights()



#ftiaxnw to neo neurwniko, sto opoio tha valw ta varh tou dwsmenou
new_model = keras.Sequential()
new_model.add(layers.Dense(64, activation = 'relu',input_shape=(128,))) #prosthetw layer

new_model.compile(optimizer=optimizers.RMSprop(0.01),loss=losses.CategoricalCrossentropy(),metrics=[metrics.CategoricalAccuracy()])

new_model.summary()


new_model.layers[0].set_weights(weights) #vazw ta weights

interm_output = new_model.predict(data,batch_size=32)


outname='new_representations2.csv'
with open(outname, 'w') as filehandle:
    for i in range(len(data.index)):
        y_str=data.index[i]
        for j in range(len(interm_output[i])):
            y_str=y_str+','+str(interm_output[i][j])
        filehandle.write('%s\n' %(y_str))
print(outname,'  written')
#write sto outputfile
