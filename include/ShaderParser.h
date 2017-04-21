#ifndef SHADERPARSER_H_
#define SHADERPARSER_H_

#include <vector>
#include <string>
class ShaderParser
{
  public :
    enum class ParamType {INT,FLOAT,POINT,VECTOR,NORMAL,COLOR,MATRIX,STRING};
    struct ShaderParam
    {
        std::string name;
        ParamType type;
    };

    ShaderParser(const std::string &_shaderName);
    ShaderParser();
    ShaderParser(const ShaderParser &)=delete;
    bool setShader(const std::string &_shaderName);
    void print() const;
    size_t numInputs() const;
    size_t numOutputs() const;
    const std::string &name() const;
    const std::vector<ShaderParam> & getInputs() const;
    const std::vector<ShaderParam> & getOutputs() const;



  private :
    enum class ParamDirection{INPUT,OUTPUT};
    bool parseShader(const std::string &_shaderName);
    void parseShaderParam(std::vector <std::string>&_tokens,ParamDirection=ParamDirection::INPUT);
    std::vector<ShaderParam> m_inputs;
    std::vector<ShaderParam> m_outputs;
    std::string m_shaderName;
};


#endif
