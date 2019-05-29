// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include <iostream>
#include <fstream>

Net::Net(){}

Net::~Net(){
  // release all layer pointer
  for(size_t i = 0;i < num_layers();++i){
    delete m_layers[i];
  }
}

void
Net::init(const std::string & model_path, const std::string & weights_path){
  load_model(model_path);
  load_weights(weights_path);
}

Eigen::MatrixXd
Net::forward(const Eigen::MatrixXd & input){
  std::vector<Eigen::MatrixXd> inputVec = {input};
  // pass input to the first layer
  m_layers[0]->forward(inputVec);

  // use the previous layer's output as next layer's input
  for(int i = 1;i < num_layers();++i){
    m_layers[i]->forward(m_layers[i-1]->output());
  }
  
  // store the output of the last layer
  m_output = m_layers[num_layers() - 1]->output()[0];
  return m_output;
}

void
Net::add_layer(Layer * layer){
  m_layers.push_back(layer);
}

void
Net::load_model(const std::string & path){
  using neb::CJsonObject;
  std::ifstream fin(path);
  std::string buffer;
  fin>>buffer;
  CJsonObject json(buffer);

  // layer message in json
  auto jsonLayers = json["layers"];

  // set input size of the net
  int cur_input_row;
  int cur_input_col;
  jsonLayers[0]["config"]["batch_input_shape"].Get(1, cur_input_row);
  jsonLayers[0]["config"]["batch_input_shape"].Get(2, cur_input_col);
  int cur_input_num = 1;

  // parse each layer message in json
  for(int i = 0;i < jsonLayers.GetArraySize();++i){
    Layer * layer = nullptr;
    std::string classname;
    jsonLayers[i].Get("class_name", classname);
    // determine layer type
    if(classname.c_str() == "Conv2D"){
      layer = new Convolutional();
      int arg1,arg2,arg3,arg4,arg5;
      std::string arg6, arg7;

      jsonLayers[i]["config"].Get("filters", arg1);
      jsonLayers[i]["config"]["kernel_size"].Get(0, arg2);
      jsonLayers[i]["config"]["kernel_size"].Get(1, arg3);
      jsonLayers[i]["config"]["strides"].Get(0, arg4);
      jsonLayers[i]["config"]["strides"].Get(1, arg5);
      jsonLayers[i]["config"].Get("padding", arg6);
      jsonLayers[i]["config"].Get("name", arg7);

      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  arg1,
                  arg2,
                  arg3,
                  arg4,
                  arg5,
                  arg6,
                  arg7);
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();

      add_layer(layer);

      // create activation layer
      Layer * act;
      std::string actname;
      jsonLayers[i]["config"].Get("activation", actname);
      if(actname.c_str() == "relu"){
        act = new Relu();
      } else if(actname.c_str() == "softmax"){
        act = new Softmax();
      } else if(actname.c_str() == "sigmoid"){
        act = new Sigmoid();
      }
      // initialize activation layer and add it to the net
      act->init(0,0,0,0,0,0,0,0,"","");
      add_layer(act);

    } else if(classname.c_str() == "MaxPooling2D"){
      layer = new MaxPooling();
      int arg1, arg2;
      std::string arg3, arg4;
      jsonLayers[i]["config"]["pool_size"].Get(0, arg1);
      jsonLayers[i]["config"]["pool_size"].Get(1, arg2);
      jsonLayers[i]["config"].Get("padding", arg3);
      jsonLayers[i]["config"].Get("name", arg4);
      
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  0,
                  arg1,
                  arg2,
                  0,
                  0,
                  arg3,
                  arg4);
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();
      
      add_layer(layer);
    } else if(classname.c_str() == "Dense"){
      layer = new Dense();
      int arg1;
      std::string arg2;
      jsonLayers[i]["config"].Get("units", arg1);
      jsonLayers[i]["config"].Get("name", arg2);
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  arg1,
                  0,
                  0,
                  0,
                  0,
                  "", 
                  arg2);
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();

      add_layer(layer);

      // create activation layer
      Layer * act;
      std::string actname;
      jsonLayers[i]["config"].Get("activation", actname);
      if(actname.c_str() == "relu"){
        act = new Relu();
      } else if(actname.c_str() == "softmax"){
        act = new Softmax();
      } else if(actname.c_str() == "sigmoid"){
        act = new Sigmoid();
      }
      // initialize activation layer and add it to the net
      act->init(0,0,0,0,0,0,0,0,"","");
      add_layer(act);

    } else if(classname.c_str() == "Flatten"){
      layer = new Flatten();
      std::string arg1;
      jsonLayers[i]["config"].Get("name", arg1);
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  0,
                  0,
                  0,
                  0,
                  0,
                  "",
                  arg1);
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();
      
      add_layer(layer);
    }
  }
}

void
Net::load_weights(const std::string & path){
  using neb::CJsonObject;
  std::ifstream fin(path);
  std::string buffer;
  fin>>buffer;
  CJsonObject json(buffer);


  for(auto it = m_layers.begin();it != m_layers.end();++it){
    // get weights and bias array in json
    auto layerWeights = json[(*it)->get_name()]["weights"];
    auto layerBias = json[(*it)->get_name()]["bias"];

    // determine layer type
    switch((*it)->get_type()){
      case Layer::Conv:{
        Convolutional* convLayer = (Convolutional*)(*it);
        // parameters to initialize
        std::vector<std::vector<Eigen::MatrixXd>> kernel((*it)->node_num(), std::vector<Eigen::MatrixXd>((*it)->in_size(), Eigen::MatrixXd(convLayer->kernel_row(), convLayer->kernel_row())));
        std::vector<double> bias((*it)->node_num());
        // construct kernel from json
        for(int i = 0;i < (*it)->node_num();++i){
          for(int j = 0;j < (*it)->node_num();++j){
            for(int k = 0;k < convLayer->kernel_row();++k){
              for(int l = 0;l < convLayer->kernel_col();++l){
                layerWeights[i][j][k].Get(l, kernel[i][j](k,l));
              }
            }
          }
        }
        // construct bias from json
        for(int i = 0;i < (*it)->node_num();++i){
          layerBias.Get(i, bias[i]);
        }

        convLayer->init(kernel, bias);

        break;
      }
      case Layer::Dense:{
        // parameters to initialize
        Eigen::MatrixXd weights((*it)->node_num(), (*it)->input_row());
        Eigen::MatrixXd bias((*it)->node_num(), 1);
        Dense* denseLayer = (Dense*)(*it);

        for(size_t i = 0;i < (*it)->node_num();++i){
          // set weights
          for(size_t j = 0;j < (*it)->input_row();++j){
            layerWeights[i].Get(j, weights(i,j));
          }
          // set bias
          layerBias.Get(i, bias(i));
        }
        denseLayer->init(weights, bias);
        break;
      }
    }
  }
}

Eigen::MatrixXd
Net::output() const{
  return m_output;
}

size_t
Net::num_layers() const{
  return m_layers.size();
}

#endif // CS133_NET_IMPL_HPP