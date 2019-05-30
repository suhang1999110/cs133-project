from keras import utils
from keras.layers import Dense, Conv2D, AveragePooling2D, Flatten, MaxPooling2D
from keras.models import Sequential
from keras.datasets import mnist
from keras.optimizers import SGD
import numpy as np
import os

# GPU
os.environ["CUDA_VISIBLE_DEVICES"] = "2"

# import data
(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1)
x_test = x_test.reshape(-1, 28, 28, 1)
x_train = x_train / 255
x_test = x_test / 255
y_train = utils.to_categorical(y_train, 10)
y_test = utils.to_categorical(y_test, 10)

# build model
model = Sequential()
model.add(Conv2D(5, (5, 5), activation='relu', input_shape=(28, 28, 1), padding='valid'))
model.add(MaxPooling2D((2, 2), strides=2, padding='same'))
# model.add(Conv2D(1, (5, 5), activation='relu', padding='same'))
# model.add(MaxPooling2D((2, 2), strides=2, padding='same'))
model.add(Flatten())
# model.add(Dense(20, activation='relu'))
model.add(Dense(10, activation='softmax'))

model.compile(optimizer=SGD(), loss='categorical_crossentropy', metrics=['accuracy'])

# train model
model.fit(x_train, y_train, batch_size=64, epochs=3, validation_data=(x_test,y_test))

# save model
# model.save('model.h5')
model.save_weights('miniweights.h5')
with open('minimodel.json', 'w') as json:
    json.write(model.to_json())

# evaluate test
score = model.evaluate(x_test, y_test)
print('loss: ', score[0])
print('accu: ', score[1])
