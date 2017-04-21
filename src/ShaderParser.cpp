#include "ShaderParser.h"
#include <iostream>
#include <QProcess>
#include <QDir>
#include <string>
#include <sstream>

ShaderParser::ShaderParser(const std::string &_shaderName)
{

  if(!parseShader(_shaderName))
    std::cerr<<"unable to read shader "<<_shaderName<<'\n';
}

const std::vector<ShaderParser::ShaderParam> & ShaderParser::getInputs() const
{
  return m_inputs;
}
const std::vector<ShaderParser::ShaderParam> & ShaderParser::getOutputs() const
{
  return m_outputs;
}


bool ShaderParser::parseShader(const std::string &_shaderName)
{
  bool result=true;
  std::vector<std::string> shaderOutput;
  std::string command="oslinfo ";
  command+=_shaderName;
  FILE *stream = popen (command.c_str(), "r");
  char *ptr = nullptr;
  size_t len;
  std::string str;

  while (getline (&ptr, &len, stream) != -1)
  {
   str = ptr;
   shaderOutput.push_back (str);
  }


  for(auto s : shaderOutput)
  {
    // tokenise the parameter
    std::istringstream iss(s);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                          std::istream_iterator<std::string>{}};
//    std::cout<<tokens.size()<<'\n';
//    for(auto t : tokens)
//      std::cout<<"token "<<t<<'\n';

    if(tokens[0] == "shader" || tokens[0]=="surface")
    {
      // oslinfo puts name in " " so remove
      m_shaderName=tokens[1].substr(1,tokens[1].size()-2);
      std::cout<<"Shader Name "<<m_shaderName<<'\n';
    }
    else if(tokens[0] == "output")
    {
      // don't need to parse the output tag so remove
      tokens.erase(std::begin(tokens));
      parseShaderParam(tokens,ParamDirection::OUTPUT);
    }
    else
    {
      parseShaderParam(tokens,ParamDirection::INPUT);
    }
  }
  return result;
}


void ShaderParser::parseShaderParam(std::vector <std::string>&_tokens,ParamDirection _dir)
{
  ShaderParam p;
  // INT,FLOAT,POINT,VECTOR,NORMAL,COLOR,MATRIX,STRING,VOID
  if(_tokens[0]== "int") p.type=ParamType::INT;
  else if(_tokens[0]== "float") p.type=ParamType::FLOAT;
  else if(_tokens[0]== "point") p.type=ParamType::POINT;
  else if(_tokens[0]== "vector") p.type=ParamType::VECTOR;
  else if(_tokens[0]== "normal") p.type=ParamType::NORMAL;
  else if(_tokens[0]== "color") p.type=ParamType::COLOR;
  else if(_tokens[0]== "matrix") p.type=ParamType::MATRIX;
  else if(_tokens[0]== "string") p.type=ParamType::STRING;
  else if(_tokens[0]== "void") p.type=ParamType::VOID;
  p.name=_tokens[1];
  if(_dir == ParamDirection::INPUT)
    m_inputs.push_back(p);
  else
    m_outputs.push_back(p);

}


bool ShaderParser::setShader(const std::string &_shaderName)
{
  auto result=parseShader(_shaderName);

  if(!result)
  {
    std::cerr<<"unable to read shader "<<_shaderName<<'\n';
  }
  return result;
}

void ShaderParser::print() const
{

  auto getType=[this ](ParamType _p)
  {
    // INT,FLOAT,POINT,VECTOR,NORMAL,COLOR,MATRIX,STRING,VOID

    if(_p == ParamType::INT) return "int ";
    else if(_p == ParamType::FLOAT) return "float " ;
    else if(_p == ParamType::POINT) return "point " ;
    else if(_p == ParamType::VECTOR) return "vector " ;
    else if(_p == ParamType::NORMAL) return "normal " ;
    else if(_p == ParamType::COLOR) return "color " ;
    else if(_p == ParamType::MATRIX) return "matrix " ;
    else if(_p == ParamType::STRING) return "string " ;
    else if(_p == ParamType::VOID) return "void " ;
    else return "";
  };

  std::cout<<"Shader Name "<<m_shaderName<<'\n';
  std::cout<<"Number of Inputs :" << m_inputs.size()<<'\n';
  for(auto i : m_inputs)
    std::cout<<getType(i.type)<<i.name<<'\n';
  std::cout<<"Number of Outputs :" << m_outputs.size()<<'\n';
  for(auto i : m_outputs)
    std::cout<<getType(i.type)<<i.name<<'\n';
}


size_t ShaderParser::numInputs() const
{
  return m_inputs.size();
}
size_t ShaderParser::numOutputs() const
{
  return m_outputs.size();

}

const std::string & ShaderParser::name() const
{
  return m_shaderName;
}

