#ifndef SHADERDATAMODEL_H_
#define SHADERDATAMODEL_H_
#include <iostream>
#include <QtCore/QObject>
#include <QLineEdit>
#include <nodes/NodeData.hpp>
#include <nodes/NodeDataModel.hpp>
#include "ShaderNodeData.h"
#include "ShaderParams.h"
#include <memory>


//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class Shader : public QtNodes::NodeDataModel
{
  Q_OBJECT

public:

  virtual ~Shader() {}
  Shader(QString _name ,unsigned int _numInputs, int _numOutputs,QWidget *_parent);
  Shader(Shader &&)=default;
  Shader(const Shader &);
  void addInput(QtNodes::NodeData *_input);
  void addOutput(QtNodes::NodeData *_output);
  QString getParamLayer() const;
  QString getParamLabel() const;
  QString getParamVisibility() const;
  const std::vector<QtNodes::NodeData *> & inputs() const {return m_inputs;}
  const std::vector<QtNodes::NodeData *> & outputs() const {return m_outputs;}
  QString caption() const override;

  QString name() const override;

  std::unique_ptr<QtNodes::NodeDataModel> clone() const override;
  unsigned int nPorts(QtNodes::PortType portType) const override;


  QtNodes::NodeDataType dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const override;
  std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override;
  QJsonObject save() const override;
  void restore(QJsonObject const &) override;

  void setInData(std::shared_ptr<QtNodes::NodeData>, int) override;

  QWidget * embeddedWidget() override;
  protected:
  bool eventFilter(QObject *object, QEvent *event) override;


  private :

    QString m_name;
    unsigned int m_numInputs;
    unsigned int m_numOutputs;
    std::vector<QtNodes::NodeData *> m_inputs;
    std::vector<QtNodes::NodeData *> m_outputs;
    ShaderParams *m_shaderParams;
    QWidget *m_parent;


};

#endif
