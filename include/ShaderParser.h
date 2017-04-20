#ifndef SHADERPARSER_H_
#define SHADERPARSER_H_

#include <vector>
#include <string>
class ShaderParser
{
    enum class ParamType {INT,FLOAT,POINT,VECTOR,NORMAL,COLOR,MATRIX,STRING,VOID};
    struct ShaderParam
    {
        std::string name;
        ParamType type;
    };

  public :

    ShaderParser(const std::string &_shaderName);
    ShaderParser();
    ShaderParser(const ShaderParser &)=delete;
    bool setShader(const std::string &_shaderName);
    void print() const;
  private :
    enum class ParamDirection{INPUT,OUTPUT};
    bool parseShader(const std::string &_shaderName);
    void parseShaderParam(std::vector <std::string>&_tokens,ParamDirection=ParamDirection::INPUT);
    std::vector<ShaderParam> m_inputs;
    std::vector<ShaderParam> m_outputs;
    std::string m_shaderName;
};


#endif
