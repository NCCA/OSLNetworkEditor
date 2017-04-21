#ifndef SHADERDATAMODEL_H_
#define SHADERDATAMODEL_H_
#include <iostream>
#include <QtCore/QObject>

#include <nodes/NodeData.hpp>
#include <nodes/NodeDataModel.hpp>
#include "ShaderNodeData.h"
#include <memory>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;




//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class Shader : public NodeDataModel
{
  Q_OBJECT

public:

  virtual ~Shader() {}
  Shader(QString _name ,unsigned int _el) : m_name(_name), m_el(_el){std::cout<<"ctor "<<m_el<<'\n';}
  Shader(Shader &&)=default;


  QString caption() const override;

  QString name() const override;

  std::unique_ptr<NodeDataModel> clone() const override;
  unsigned int nPorts(PortType portType) const override;


  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  std::shared_ptr<NodeData> outData(PortIndex port) override;


  void setInData(std::shared_ptr<NodeData>, int) override;

  QWidget * embeddedWidget() override;

  private :

    QString m_name;
    unsigned int m_el;

};

#endif
