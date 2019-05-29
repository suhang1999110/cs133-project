#include <iostream>
#include <fstream>
#include <sstream>

#include "utils/parsers.cpp"

namespace toy_json {

JsonNode::JsonNode(const JsonNode &rhs) {
  release_union();
  type_ = rhs.type();
  switch (rhs.type()) {
    case JSON_NULL:
      break;
    case JSON_BOOL:
      v_bool_ = rhs.get_bool();
      break;
    case JSON_NUMBER:
      v_number_ = rhs.get_number();
      break;
    case JSON_STRING:
      new(&v_string_) std::unique_ptr<std::string>(new std::string{*rhs.v_string_});
      break;
    case JSON_ARRAY:
      new(&v_array_) std::unique_ptr<array>(new array{*rhs.v_array_});
      break;
    case JSON_OBJECT:
      new(&v_object_) std::unique_ptr<object>(new object{*rhs.v_object_});
      break;
  }
}

JsonNode::JsonNode(JsonNode &&rhs) noexcept {
  release_union();
  type_ = rhs.type();
  switch (rhs.type()) {
    case JSON_NULL:
      break;
    case JSON_BOOL:
      v_bool_ = rhs.get_bool();
      break;
    case JSON_NUMBER:
      v_number_ = rhs.get_number();
      break;
    case JSON_STRING:
      new(&v_string_) std::unique_ptr<std::string>(std::move(rhs.v_string_));
      break;
    case JSON_ARRAY:
      new(&v_array_) std::unique_ptr<array>(std::move(rhs.v_array_));
      break;
    case JSON_OBJECT:
      new(&v_object_) std::unique_ptr<object>(std::move(rhs.v_object_));
      break;
  }
}

void JsonNode::release_union() {
  switch (type_) {
    case JSON_STRING:
      v_string_.~unique_ptr<std::string>();
      break;
    case JSON_ARRAY:
      v_array_.~unique_ptr<array>();
      break;
    case JSON_OBJECT:
      v_object_.~unique_ptr<object>();
      break;
    default:
      break;
  }
}

std::string Json::error_info_;

std::unique_ptr<JsonNode> Json::parse(const std::string &fin) noexcept {
  // TODO: Implement main parsing procedure here, some notices:
  //   1. You may find helper functions in `utils/parsers.hpp` useful. Note that
  //      we did not provide `parse_null`, why?
  //   2. Note that actual data that larger than 4 bytes is hold by `shared_ptr`
  //      you should construct `string`, `array` and `object` types by passing
  //      r-valued `unique_ptr`s;
  //   3. DO NOT throw exceptions out of this function. If an internal exception
  //      occurs, e.g. get invalid input, just catch that exception, modify the
  //      `error_info_` and return a `nullptr`;
  //   4. Expected `error_info` for each kind of parsing errors: (these
  //      messages, without surrounding "`", will be examined in unit tests,
  //      make sure you throw the correct internal errors)
  //      - fail parsing `null`:    `parsing null type failed`
  //      - fail parsing `bool`:    `parsing bool type failed`
  //      - fail parsing `number`:  `parsing number type failed`
  //      - fail parsing `string`:  `parsing string type failed`
  //      - fail parsing `array`:   `parsing array type failed`
  //      - fail parsing `object`:  `parsing object type failed`
  std::ifstream jsonfile(fin);
  std::stringstream buffer;
  // cannot open file
  if(!jsonfile.is_open()){
    exit(1);
  }
  // read json file string for once
  buffer << jsonfile.rdbuf();
  std::string contents(buffer.str());
  jsonfile.close();
  // strip meaningless control character
  std::string::iterator it = contents.begin();
  bool flag = false;
    while(*it){
        switch(*it){
            case '\"':
            // meet a string and flip flag
                flag = !flag;
                it++;
                break;
            case '\t':
            case '\n':
            case '\r':
            case ' ':
                if(flag){ // inside a string now
                    it++;
                }
                else{ // outside a string now
                // replace escape character with whitespace
                    *it = ' ';
                    it++;
                }
                break;
            default:
                it++;
        }
    }
  //parse the contents
  std::string::const_iterator str_it = contents.cbegin();
  try{
    return std::unique_ptr<JsonNode>(new JsonNode(std::unique_ptr<JsonNode::object>(new JsonNode::object(parse_object(str_it)))));
  }
  catch(std::runtime_error err){
    // set error message
    Json::error_info_ = err.what();
    // std::cout<<"hehe\n";
    return nullptr;
  }
  // shouldn't reach here!
  return nullptr;
}

}
