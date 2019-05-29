//
// Created by lirundong on 2019-03-25.
//
#include <stack>
#include <iomanip>
#include <limits>

#include "../../include/utils/parsers.hpp"

namespace toy_json {

// TODO: Implement parsing helpers in this file. If any parsing error occurs,
//   e.g., meet with invalid input string, just throw `std::runtime_error` with
//   bellowing error information (without surrounding ` ):
//   - fail parsing `bool`:    `parsing bool type failed`
//   - fail parsing `number`:  `parsing number type failed`
//   - fail parsing `string`:  `parsing string type failed`
//   - fail parsing `array`:   `parsing array type failed`
//   - fail parsing `object`:  `parsing object type failed`

bool parse_bool(std::string::const_iterator &str_it) {
  bool result = false;
  // TODO: implement parsing and advance iterator
  // Assume that the input string contains no space
  std::string buf;
  // put input string into buffer
  while(*str_it){
    //the character is not belong to the value
    if(*str_it == ' ' || *str_it == ',' || *str_it == '[' ||\
       *str_it == ']' || *str_it == '{' || *str_it == '}'){
      break;
    }
    buf.push_back(*str_it);
    str_it++;
  }
  // set return value and error
  if(buf == "true"){
    result = true;
  }
  else if(buf == "false"){
    result = false;
  }
  else{
    throw std::runtime_error("parsing bool type failed");
  }
  return result;
}

double parse_number(std::string::const_iterator &str_it) {
  double result = 0.0;
  // TODO: implement parsing and advance iterator
  std::string buf;
  std::string::size_type sz;
  // put input string into buffer
  while(*str_it){
    //the character is not belong to the value
    if(*str_it == ' ' || *str_it == ',' || *str_it == '[' ||\
       *str_it == ']' || *str_it == '{' || *str_it == '}'){
      break;
    }
    buf.push_back(*str_it);
    str_it++;
  }
  // wrong input handling
  try{
    result = stod(buf,&sz);
    if(buf[0] == '+'){
      throw std::runtime_error("parsing number type failed");      
    }
  }
  catch(std::exception err){
    throw std::runtime_error("parsing number type failed");
  }
  // wrong input like 1.23.45
  // for these cases, the size of buf is incompatible with sz
  if(sz != buf.size()){
    throw std::runtime_error("parsing number type failed");
  }
  return result;
}

std::string parse_string(std::string::const_iterator &str_it) {
  std::string result;
  // TODO: implement parsing and advance iterator
  // NOTE: you are required to store unicode code-points in UTF-8 encoding
  while(*str_it){
    str_it++;
    switch(*str_it){
      case '\"':
        // the end of string
        str_it++;
        return result;
        break;
      case '\\':
        str_it++;
        switch(*str_it){
          // escape character
          case '\"':
            result.push_back('\"');
            break;
          case '\\':
            result.push_back('\\');
            break;
          case '/':
            result.push_back('/');
            break;
          case 'b':
            result.push_back('\b');
            break;
          case 'f':
            result.push_back('\f');
            break;
          case 'n':
            result.push_back('\n');
            break;
          case 'r':
            result.push_back('\r');
            break;
          case 't':
            result.push_back('\t');
            break;
          // unicode character
          case 'u':{
            // store 4-bits hexdecimal in unicodeHex
            std::string unicodeHex;
            long int codepoint, lohex4;
            // get hexdecimal string
            for(auto i = 0;i < 4;i++){
              str_it++;
              unicodeHex.push_back(*str_it);
            }
            // convert into hexdecimal
            codepoint = strtol(unicodeHex.c_str(), NULL, 16);
            // invalid hex string
            if(unicodeHex != "0000" && codepoint == 0){
              throw std::runtime_error("parsing string type failed");
            }
            // expect surrogate pair
            if(codepoint >= 0xD800 && codepoint <= 0xDBFF){
              // invalid surrogate pair
              str_it++;
              if(*str_it != '\\'){
                throw std::runtime_error("parsing string type failed");
              }
              str_it++;
              // invalid surrogate pair
              if(*str_it != 'u'){
                throw std::runtime_error("parsing string type failed");
              }
              unicodeHex.clear();
              // get low hex4
              for(auto i = 0;i < 4;i++){
                str_it++;
                unicodeHex.push_back(*str_it);
              }
              // convert into hexdecimal
              lohex4 = strtol(unicodeHex.c_str(), NULL, 16);
              // invalid hex string
              if(unicodeHex != "0000" && lohex4 == 0){
                throw std::runtime_error("parsing string type failed");
              }
              // no low surrogate
              if(lohex4 < 0xDC00 || lohex4 > 0xDFFF){
                throw std::runtime_error("parsing string type failed");
              }
              codepoint = (((codepoint - 0xD800) << 10) | (lohex4 - 0xDC00)) + 0x10000;  
            }
            // encode into UTF-8
            if(codepoint <= 0x7F){
              result.push_back(codepoint & 0xFF);
            }
            else if(codepoint <= 0x7FF){
              result.push_back(0xC0 | ((codepoint >> 6) & 0xFF));
              result.push_back(0x80 | (codepoint & 0x3F));
            }
            else if(codepoint <= 0xFFFF){
              result.push_back(0xE0 | ((codepoint >> 12) & 0xFF));
              result.push_back(0x80 | ((codepoint >> 6) & 0x3F));
              result.push_back(0x80 | (codepoint & 0x3F));
            }
            else if(codepoint <= 0x10FFFF){
              result.push_back(0xF0 | ((codepoint >> 18) & 0xFF));
              result.push_back(0x80 | ((codepoint >> 12) & 0x3F));
              result.push_back(0x80 | ((codepoint >> 6) & 0x3F));
              result.push_back(0x80 | (codepoint & 0x3F));
            }
            else{
              // invalid codepoint
              throw std::runtime_error("parsing string type failed");  
            }
            break;
          }
          default:
          // escape character invalid
            throw std::runtime_error("parsing string type failed");
        }
        break;
    
      default:
        result.push_back(*str_it);
        break;
    }
  }
  // shouldn't reach here
    throw std::runtime_error("parsing string type failed");
}

JsonNode::array parse_array(std::string::const_iterator &str_it) {
  JsonNode::array result;
  // TODO: implement parsing and advance iterator
  // NOTE: we did not provide `parse_null` above, however `null` is one of the
  //   valid array values
  bool expectComma = false;
  // the first character must be [
  str_it++;
  // parse the array
  while(*str_it){
    switch(*str_it){
      case ' ':
        // skip whitespace
        str_it++;
        break;
      case '\"':
        // expect a string
        try{
          if(!expectComma){
            std::unique_ptr<std::string> s(new std::string(parse_string(str_it)));
            JsonNode newNode(std::move(s));
            result.push_back(newNode);
            expectComma = true;
          }
          else{
            throw std::runtime_error("parsing array type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case '-': case '+':
        // expect a number
        try{
          if(!expectComma){
            JsonNode newNode(parse_number(str_it));
            result.push_back(newNode);
            expectComma = true;
          }
          else{
            throw std::runtime_error("parsing array type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case 'T': case 't':
      case 'F': case 'f':
        // expect a boolean
        try{
          if(!expectComma){
            JsonNode newNode(parse_bool(str_it));
            result.push_back(newNode);
            expectComma = true;
          }
          else{
            throw std::runtime_error("parsing array type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case 'n': case 'N':{
        // expect null
        if(expectComma){
          // shouldn't expect a comma
          throw std::runtime_error("parsing array type failed");
        }
        std::string temp;
        temp.push_back(*str_it);
        // get the token
        for(auto i = 0;i < 3;i++){
          str_it++;
          temp.push_back(*str_it);
        }
        if(temp == "null"){
          JsonNode newNode;
          result.push_back(newNode);
          expectComma = true;
          // move to next character
          str_it++;
        }
        else{
          // invalid null
          throw std::runtime_error("parsing null type failed");
        }
        break;
      }
      case '[':
        // expect an array
        try{
          if(!expectComma){
            std::unique_ptr<JsonNode::array> a(new JsonNode::array(parse_array(str_it)));
            JsonNode newNode(std::move(a));
            result.push_back(newNode);
            expectComma = true;
          }
          else{
            throw std::runtime_error("parsing array type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case '{':
        // expect an object
        try{
          if(!expectComma){
            std::unique_ptr<JsonNode::object> o(new JsonNode::object(parse_object(str_it)));
            JsonNode newNode(std::move(o));
            result.push_back(newNode);
            expectComma = true;
          }
          else{
            throw std::runtime_error("parsing array type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case ']':
        // end of an array
        if(expectComma){
          // should expect , or ] after an element
          str_it++;
          return result;
        }
        else{
          throw std::runtime_error("parsing array type failed");
        }
        break;
      case ',':
        // expect the next element
        if(expectComma){
          expectComma = false;
          // move to next character
          str_it++;
        }
        else{
          // should't be a comma here
          throw std::runtime_error("parsing array type failed");
        }
        break;
      default:
        // cannot match the element
        throw std::runtime_error("parsing array type failed");
        break;
    }
  }
  // shouldn't reach here!
  throw std::runtime_error("parsing array type failed");
}

JsonNode::object parse_object(std::string::const_iterator &str_it) {
  JsonNode::object result;
  // TODO: implement parsing and advance iterator
  // NOTE: 1. we did not provide `parse_null` above, however `null` is one of the
  //          valid object values
  //       2. object key can be any kind of json string, which means it may
  //          contain spaces, escapes, unicode code-points, etc., so take care!
  enum objectToken{
    Comma, Colon, Key, Value
  };
  objectToken expectToken = Key;
  std::string key;
  // the first character must be {
  str_it++;
  // parse the object
  // { "Key1" : Value1 , "Key2" : Value2 }
  while(*str_it){
    switch(*str_it){
      case ' ':
      // skip whitespace
        str_it++;
        break;
      case ',':
        if(expectToken == Comma){
          expectToken = Key;
          str_it++;
        }
        else{
          throw std::runtime_error("parsing object type failed");
        }
        break;
      case '\"':
        // expect a key or value
        try{
          if(expectToken == Key){
            // "Key"
            key = parse_string(str_it);
            expectToken = Colon;
          }
          else if(expectToken == Value){
            // the type of value is string
            std::unique_ptr<std::string> s(new std::string(parse_string(str_it)));
            JsonNode newNode(std::move(s));
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
          }
          else{
            // shouldn't be a " here
            throw std::runtime_error("parsing object type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case ':':
        // expect a colon
        if(expectToken == Colon){
          expectToken = Value;
          str_it++;
        }
        else{
          // shouldn't be colon here
          throw std::runtime_error("parsing object type failed");
        }
        break;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case '-': case '+':
        // expect a number
        try{
          if(expectToken == Value){
            JsonNode newNode(parse_number(str_it));
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
          }
          else{
            // number shouldn't appear in other fields
            throw std::runtime_error("parsing object type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case 'T': case 'F':
      case 't': case 'f':
        // expect a boolean
        try{
          if(expectToken == Value){
            JsonNode newNode(parse_bool(str_it));
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
          }
          else{
            // shouldn't be a boolean outside of value field
            throw std::runtime_error("parsing object type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case '[':
        // expect an array
        try{
          if(expectToken == Value){
            std::unique_ptr<JsonNode::array> a(new JsonNode::array(parse_array(str_it)));
            JsonNode newNode(std::move(a));
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
          }
          else{
            throw std::runtime_error("parsing object type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case '{':
        // expect an object
        try{
          if(expectToken == Value){
            std::unique_ptr<JsonNode::object> o(new JsonNode::object(parse_object(str_it)));
            JsonNode newNode(std::move(o));
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
          }
          else{
            throw std::runtime_error("parsing object type failed");
          }
        }
        catch(std::runtime_error err){
          throw err;
        }
        break;
      case '}':
        // expect , or } after a pair
        if(expectToken == Comma){
          str_it++;
          return result;
        }
        else{
          throw std::runtime_error("parsing object type failed");
        }
        break;
      case 'n': case 'N':{
        if(expectToken == Value){
          std::string temp;
          temp.push_back(*str_it);
          // get the token
          for(auto i = 0;i < 3;i++){
            str_it++;
            temp.push_back(*str_it);
          }
          if(temp == "null"){
            JsonNode newNode;
            result.insert(std::make_pair(key, newNode));
            expectToken = Comma;
            str_it++;
          }
          else{
            // invalid null type
            throw std::runtime_error("parsing null type failed");
          }
        }
        else{
          throw std::runtime_error("parsing object type failed");
        }
        break;
      }
      default:
        // what else?
        throw std::runtime_error("parsing object type failed");
    }
  }
  // shouldn't reach here!
  throw std::runtime_error("parsing object type failed");
}
}
