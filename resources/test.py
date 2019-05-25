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
# x_train = x_train.reshape(60000, 784)
# x_test = x_test.reshape(10000, 784)
x_train = x_train.reshape(-1, 28, 28, 1)
x_test = x_test.reshape(-1, 28, 28, 1)
x_train = x_train / 255
x_test = x_test / 255
y_train = utils.to_categorical(y_train, 10)
y_test = utils.to_categorical(y_test, 10)

# x_train = np.zeros(60000 * 32 * 32).reshape(60000, 32, 32)
# x_test = np.zeros(10000 * 32 * 32).reshape(10000, 32, 32)
# x_train[:,2:-2,2:-2] = x_train_raw
# x_test[:,2:-2,2:-2] = x_test_raw

# build model
model = Sequential()
# model.add(Conv2D(6, (5, 5), activation='relu', padding='same', strides=(1, 1), input_shape=(60000, 28, 28), data_format='channels_first'))
# model.add(AveragePooling2D((2, 2), strides=(2, 2), padding='valid'))
# model.add(Conv2D(16, (5, 5), activation='relu', padding='same', strides=(1, 1)))
# model.add(AveragePooling2D((2, 2), strides=(2, 2), padding='valid'))
# model.add(Dense(120, activation='relu'))
# model.add(Dense(84, activation='relu'))
# model.add(Dense(10, activation='softmax'))

model.add(Conv2D(20, (5, 5), activation='relu', input_shape=(28, 28, 1)))
model.add(MaxPooling2D((2, 2), strides=2, padding='same'))
model.add(Conv2D(50, (5, 5), activation='relu', padding='same'))
model.add(MaxPooling2D((2, 2), strides=2, padding='same'))
model.add(Flatten())
model.add(Dense(500, activation='relu'))
model.add(Dense(10, activation='softmax'))

model.compile(optimizer=SGD(), loss='categorical_crossentropy', metrics=['accuracy'])

# train model
model.fit(x_train, y_train, batch_size=64, epochs=5, validation_data=(x_test,y_test))

# save model
# model.save('model.h5')
model.save_weights('weights.h5')
with open('model.json', 'w') as json:
    json.write(model.to_json())

# evaluate test
score = model.evaluate(x_test, y_test)
print('loss: ', score[0])
print('accu: ', score[1])
