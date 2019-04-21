# cs133-project


**Generic implementation of a neural network**

-----
1. Build a C++ library that

   * can load a pre-trained network definition file
   * contains an abstract definition of common layers and the composing elements
     + Linear transformation, convolutions
     + Response functions, output layers
     + Fully connected layers
   * initializes concrete layers of the network with a suitable programming technique(e.g. factory method)
   * applies it to some data

2. Examples should include common application scenario given by a simple image classifier
     * Character recognition (see MNIST)
3. Free to add alternative classification tasks
     * Stick to simple cases with "standard" networks