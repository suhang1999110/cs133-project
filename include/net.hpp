// implement of Net class
#ifndef CS133_NET_IMPL_HPP
#define CS133_NET_IMPL_HPP

#include <iostream>
#include <fstream>

using namespace rapidjson;

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
  std::vector<Eigen::MatrixXd> inputVec;
  inputVec.push_back(input);
  // pass input to the first layer
  m_layers[0]->forward(inputVec);

  // use the previous layer's output as next layer's input
  for(int i = 1;i < num_layers();++i){
    m_layers[i]->forward(m_layers[i - 1]->output());
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
  Document doc;
  std::ifstream fin(path);
  std::string str( (std::istreambuf_iterator<char>(fin) ),
                   (std::istreambuf_iterator<char>()    ) );
  const char* json = str.data();
  doc.Parse(json);
  
  // layer message in json
  Value& jsonLayers = doc["config"]["layers"];
  // set input size of the net
  int cur_input_num = 1;
  int cur_input_row = jsonLayers[0]["config"]["batch_input_shape"][1].GetInt();
  int cur_input_col = jsonLayers[0]["config"]["batch_input_shape"][2].GetInt();

  // parse each layer message in json
  for(int i = 0;i < jsonLayers.Size();++i){
    Layer * layer = nullptr;
    // determine layer type
    if(jsonLayers[i]["class_name"].GetString() == std::string("Conv2D")) {
      layer = new Convolutional();
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  jsonLayers[i]["config"]["filters"].GetInt(),
                  jsonLayers[i]["config"]["kernel_size"][0].GetInt(),
                  jsonLayers[i]["config"]["kernel_size"][1].GetInt(),
                  jsonLayers[i]["config"]["strides"][0].GetInt(),
                  jsonLayers[i]["config"]["strides"][1].GetInt(),
                  jsonLayers[i]["config"]["padding"].GetString(),
                  jsonLayers[i]["config"]["name"].GetString());
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();

      add_layer(layer);

      // create activation layer
      Layer * act;
      std::string name;
      if(jsonLayers[i]["config"]["activation"].GetString() == std::string("relu")) {
        act = new ReLU();
        name = "relu" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if(jsonLayers[i]["config"]["activation"].GetString() == std::string("softmax")) {
        act = new Softmax();
        name = "softmax" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if(jsonLayers[i]["config"]["activation"].GetString() == std::string("sigmoid")) {
        act = new Sigmoid();
        name = "sigmoid" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if (jsonLayers[i]["config"]["activation"].GetString() == std::string("identity")) {
        act = new Identity();
        name = "identity" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      }

      // add activation layer to the net
      add_layer(act);

    } else if(jsonLayers[i]["class_name"].GetString() == std::string("MaxPooling2D")) {
      layer = new MaxPooling();
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  0,
                  jsonLayers[i]["config"]["pool_size"][0].GetInt(),
                  jsonLayers[i]["config"]["pool_size"][1].GetInt(),
                  0, 0,
                  jsonLayers[i]["config"]["padding"].GetString(),
                  jsonLayers[i]["config"]["name"].GetString());
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();
      
      add_layer(layer);
    } else if(jsonLayers[i]["class_name"].GetString() == std::string("Dense")) {
      layer = new Dense();
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  jsonLayers[i]["config"]["units"].GetInt(),
                  0, 0, 0, 0, "", 
                  jsonLayers[i]["config"]["name"].GetString());
      // update input size
      cur_input_num = layer->out_size();
      cur_input_row = layer->output_row();
      cur_input_col = layer->output_col();

      add_layer(layer);

      // create activation layer
      Layer * act;
      std::string name;
      if(jsonLayers[i]["config"]["activation"].GetString() == std::string("relu")) {
        act = new ReLU();
        name = "relu" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if(jsonLayers[i]["config"]["activation"].GetString() == std::string("softmax")) {
        act = new Softmax();
        name = "softmax" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if(jsonLayers[i]["config"]["activation"].GetString() == std::string("sigmoid")) {
        act = new Sigmoid();
        name = "sigmoid" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      } else if (jsonLayers[i]["config"]["activation"].GetString() == std::string("identity")) {
        act = new Identity();
        name = "identity" + layer->get_name();
        act->init(cur_input_num, cur_input_row, cur_input_col, 0, 0, 0, 0, 0, "", name);
        // update input size
        cur_input_num = act->out_size();
        cur_input_row = act->output_row();
        cur_input_col = act->output_col();
      }

      // add activation layer to the net
      add_layer(act);

    } else if(jsonLayers[i]["class_name"].GetString() == std::string("Flatten")) {
      layer = new Flatten();
      layer->init(cur_input_num,
                  cur_input_row,
                  cur_input_col,
                  0, 0, 0, 0, 0, "",
                  jsonLayers[i]["config"]["name"].GetString());
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
  Document doc;
  std::ifstream fin(path);
  std::string str( (std::istreambuf_iterator<char>(fin) ),
                   (std::istreambuf_iterator<char>()    ) );
  const char* json = str.data();
  doc.Parse(json);
  

  for(auto it = m_layers.begin();it != m_layers.end();++it){
    // get weights and bias array in json
    if((*it)->get_type() != Layer::Conv && (*it)->get_type() != Layer::Dense){
      continue;
    }
    Value& layerWeights = doc[(*it)->get_name().c_str()]["weights"];
    Value& layerBias = doc[(*it)->get_name().c_str()]["bias"];

  // std::cout<<(*it)->get_name()<<"\n";
    // determine layer type
    switch((*it)->get_type()){
      case Layer::Conv:{
        Convolutional* convLayer = (Convolutional*)(*it);
        // parameters to initialize
        std::vector<std::vector<Eigen::MatrixXd>> kernel((*it)->node_num(), std::vector<Eigen::MatrixXd>((*it)->in_size(), Eigen::MatrixXd(convLayer->kernel_row(), convLayer->kernel_row())));
        std::vector<double> bias((*it)->node_num());
        // construct kernel from json
        
        for(int i = 0;i < (*it)->node_num();++i){
          for(int j = 0;j < (*it)->in_size();++j){
            for(int k = 0;k < convLayer->kernel_row();++k){
              for(int l = 0;l < convLayer->kernel_col();++l){
                kernel[i][j](k,l) = layerWeights[i][j][k][l].GetDouble();
              }
            }
          }
        }
        
        // construct bias from json
        for(int i = 0;i < (*it)->node_num();++i){
          bias[i] = layerBias[i].GetDouble();
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
            weights(i,j) = layerWeights[i][j].GetDouble(); 
          }
          // set bias
          bias(i) = layerBias[i].GetDouble();
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