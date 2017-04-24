#include "ShaderDataModel.h"
#include <QDebug>
#include "nodes/ConnectionStyle.hpp"
// For some reason CMake could not generate moc-files correctly
// without having a cpp for an QObject from hpp.

Shader::Shader(QString _name ,unsigned int _numInputs, int _numOutputs,QWidget *_parent=nullptr)
  : m_name(_name), m_numInputs(_numInputs), m_numOutputs(_numOutputs)
{

  m_shaderParams = new ShaderParams();
  m_shaderParams->setStyleSheet(_parent->styleSheet());
}

Shader::Shader(const Shader &_s)
{
  m_name=_s.m_name;
  m_numInputs=_s.m_numInputs;
  m_numOutputs=_s.m_numOutputs;
  m_inputs=_s.m_inputs;
  m_outputs=_s.m_outputs;
// m_layer=_s.m_layer;
  m_shaderParams=new ShaderParams();


}


QString Shader::caption() const
{
  return  m_name;
}

QString Shader::name() const
{
  return m_name;
}

std::unique_ptr<QtNodes::NodeDataModel> Shader::clone() const
{
  return std::make_unique<Shader>(*this);
}

void Shader::addInput(QtNodes::NodeData *_input)
{
  m_inputs.emplace_back(_input);
}

void Shader::addOutput(QtNodes::NodeData *_output)
{
  m_outputs.emplace_back(_output);
}


unsigned int Shader::nPorts(QtNodes::PortType portType) const
{
  unsigned int result=0;

  switch (portType)
  {
    case QtNodes::PortType::In:
      result = m_numInputs;
      break;

    case QtNodes::PortType::Out:
      result = m_numOutputs;
     break;

    case QtNodes::PortType::None : break;
  }

  return result;
}

QtNodes::NodeDataType Shader::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
  switch (portType)
  {
    case QtNodes::PortType::In:
      return m_inputs[portIndex]->type();
    break;

    case QtNodes::PortType::Out:
    return m_outputs[portIndex]->type();
    break;

    case QtNodes::PortType::None :
    break;
  }
}

std::shared_ptr<QtNodes::NodeData> Shader::outData(QtNodes::PortIndex port)
{
/*  if (port < 1)
    return std::make_shared<Color>();

  return std::make_shared<Matrix>();

*/
}

bool Shader::eventFilter(QObject *object, QEvent *event)
{
//  if (object == m_layer)
//  {

//    qDebug()<<"edit?";
//  }
}



void Shader::setInData(std::shared_ptr<QtNodes::NodeData>, int)
{
  //
}

QWidget * Shader::embeddedWidget()
{
  return m_shaderParams;
}

QString Shader::getParamLayer() const
{
  return  m_shaderParams->nodeLayer();
}

QString Shader::getParamLabel() const
{
  return  m_shaderParams->nodeLabel();
}

QString Shader::getParamVisibility() const
{
  return  m_shaderParams->nodeVisibility();
}

QJsonObject Shader::save() const
{
  QJsonObject modelJson;

  modelJson["name"] = name();
  modelJson["nodeLayer"]= m_shaderParams->nodeLayer();
  modelJson["nodeLabel"]= m_shaderParams->nodeLabel();
  modelJson["nodeVisibility"] = m_shaderParams->nodeVisibility();


  return modelJson;
}

void Shader::restore(const QJsonObject &_data)
{
  m_shaderParams->setNodeLabel(_data["nodeLabel"].toString());
  m_shaderParams->setNodeLayer(_data["nodeLayer"].toString());
  m_shaderParams->setNodeVisibility(_data["nodeVisibility"].toString());
}
