#include "MainWindow.h"
#include "ShaderParser.h"
#include "ShaderDataModel.h"
#include <QApplication>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QDebug>
#include "nodes/Node.hpp"
#include "nodes/ConnectionGraphicsObject.hpp"
#include "ui_MainWindow.h"
MainWindow::MainWindow(const QStringList _args,QWidget *_parent ): QMainWindow(_parent),  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  resize(QSize(1024,720));
  setWindowTitle(QString("OSL Shader Network Editor"));

  m_scene= new QtNodes::FlowScene(std::make_shared<QtNodes::DataModelRegistry>());
  m_view=new QtNodes::FlowView(m_scene);
  m_view->setParent(this);
  //m_view->resize(ui->m_centralwidget->size());
  this->setCentralWidget(m_view);
  for(auto a : _args)
  {
    addShader(a);
  }
  QtNodes::ConnectionStyle::setConnectionStyle(
  R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");

  connect(ui->m_loadScene,SIGNAL(clicked()),this,SLOT(loadScene()));
  connect(ui->m_loadShaders,SIGNAL(clicked()),this,SLOT(loadShaderFromFile()));
  connect(ui->m_newScene,&QToolButton::clicked, [this](){m_scene->clearScene();} );
}

MainWindow::~MainWindow()
{
}


void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
    case Qt::Key_A :
      loadShaderFromFile();
    break;
    case Qt::Key_S : m_scene->save(); break;
  case Qt::Key_L : m_scene->load(); break;
    case Qt::Key_W :
      writeXML();
    break;
    default : break;
  }
}

void MainWindow::resizeEvent ( QResizeEvent * _event )
{
  m_view->resize(_event->size());

}


QtNodes::NodeData * MainWindow::createParam(ShaderParser::ParamType _p, QString _name) const
{
  if(_p == ShaderParser::ParamType::INT) return new Int("int "+_name);
  else if(_p == ShaderParser::ParamType::FLOAT)  return new Float(QString("float "+_name)) ;
  else if(_p == ShaderParser::ParamType::POINT) return new Point(QString("point "+_name)) ;
  else if(_p == ShaderParser::ParamType::VECTOR) return  new Vector(QString("vector "+_name)) ;
  else if(_p == ShaderParser::ParamType::NORMAL) return new Normal(QString("normal "+_name)) ;
  else if(_p == ShaderParser::ParamType::COLOR) return new Color(QString("color "+_name)) ;
  else if(_p == ShaderParser::ParamType::MATRIX) return new Matrix(QString("matrix "+_name)) ;
  else if(_p == ShaderParser::ParamType::STRING) return new String(QString("string "+_name)) ;
  else return nullptr;

}



void MainWindow::addShader(const QString _name)
{
  ShaderParser s(_name.toStdString());
  QtNodes::DataModelRegistry &reg=m_scene->registry();

  std::unique_ptr<Shader> model(new Shader(s.name().c_str(),s.numInputs(),s.numOutputs(),this));


  for(auto a : s.getInputs())
  {
    model->addInput(createParam(a.type,a.name.c_str()));
  }

  for(auto a : s.getOutputs())
  {
    model->addOutput(createParam(a.type,a.name.c_str()));
  }

  reg.registerModel<Shader>("shaders",std::move(model));

}

void MainWindow::loadShaderFromFile()
{

  QFileDialog dialog(this,"Select OSL Files");
  dialog.setDirectory(QDir::currentPath());
  dialog.setFileMode(QFileDialog::ExistingFiles);
  dialog.setNameFilter(trUtf8("*.oso"));
  QStringList fileNames;
  if (dialog.exec())
    fileNames = dialog.selectedFiles();

  for (auto f : fileNames)
  {
    addShader(f);
  }
}


void MainWindow::nodeVisitor(QtNodes::Node * data)
{

}

void MainWindow::writeXML() const
{
  QString filename = QFileDialog::getSaveFileName(this->parentWidget(),
                                     tr("Save Xml"), ".",
                                     tr("Xml files (*.xml)"));


    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("RenderManOSLNetwork");
    xmlWriter.writeStartElement("NodeList");

    auto visitor=[this,&xmlWriter](QtNodes::NodeDataModel *_node)
    {
      xmlWriter.writeStartElement("Node");
        xmlWriter.writeStartElement("NodeId");
          xmlWriter.writeCharacters(_node->name());
        xmlWriter.writeEndElement(); // end NodeID
        Shader *model= reinterpret_cast<Shader*>(_node);
        xmlWriter.writeStartElement("NodeLayer");
         xmlWriter.writeCharacters(model->getParamLayer());
        xmlWriter.writeEndElement(); // end NodeLayer
        xmlWriter.writeStartElement("Label");
         xmlWriter.writeCharacters(model->getParamLabel());
        xmlWriter.writeEndElement(); // end Label
        QString visibility=model->getParamVisibility();
        xmlWriter.writeStartElement("Properties");
        for(auto p : model->inputs())
        {
          // I store param name as type -> name so split and proccess
          QStringList d=p->type().name.split(" ");
          xmlWriter.writeStartElement(d[1]);
          xmlWriter.writeStartElement("Visibility");
          xmlWriter.writeCharacters(visibility);
          xmlWriter.writeEndElement(); // end Visibility

            xmlWriter.writeStartElement("Type");
            xmlWriter.writeCharacters(d[0]);
            xmlWriter.writeEndElement(); // end type
          xmlWriter.writeEndElement();
        }

        for(auto p : model->outputs())
        {
          // I store param name as type -> name so split and proccess
          QStringList d=p->type().name.split(" ");
          xmlWriter.writeStartElement(d[1]);
          xmlWriter.writeStartElement("Access");
          xmlWriter.writeCharacters("output");
          xmlWriter.writeEndElement(); // end Visibility

            xmlWriter.writeStartElement("Type");
            xmlWriter.writeCharacters(d[0]);
            xmlWriter.writeEndElement(); // end type
          xmlWriter.writeEndElement();
        }


        xmlWriter.writeEndElement();
      xmlWriter.writeEndElement();
    };

    m_scene->iterateOverNodeDataDependentOrder(visitor);



    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("ConnectionList");
    auto connections= m_scene->connections();
    for(auto c : connections)
    {
      // OSL XML and Flow reverse Source / Destination!
      xmlWriter.writeStartElement("Connection");
      {
        auto outIndex=c.second->getPortIndex(QtNodes::PortType::Out);
        auto outNode=c.second->getNode(QtNodes::PortType::Out);
        auto outPort=outNode->nodeDataModel()->dataType(QtNodes::PortType::Out,outIndex);
        Shader *model= reinterpret_cast<Shader*>(outNode->nodeDataModel());
        xmlWriter.writeStartElement("Source");
        xmlWriter.writeStartElement("NodeId");
          xmlWriter.writeCharacters(outNode->nodeDataModel()->name());
        xmlWriter.writeEndElement(); // end NodeID
        xmlWriter.writeStartElement("NodeLayer");
          xmlWriter.writeCharacters(model->getParamLayer());
        xmlWriter.writeEndElement(); // end NodeLayer
        // I store param name as type -> name so split and proccess
        QStringList n=outPort.name.split(" ");
        xmlWriter.writeStartElement("ParameterName");
          xmlWriter.writeCharacters(n[1]);
        xmlWriter.writeEndElement(); // end parameterName
      xmlWriter.writeEndElement(); // end Source
      }
      {
        auto inIndex=c.second->getPortIndex(QtNodes::PortType::In);
        auto inNode=c.second->getNode(QtNodes::PortType::In);
        auto inPort=inNode->nodeDataModel()->dataType(QtNodes::PortType::In,inIndex);
        Shader *model= reinterpret_cast<Shader*>(inNode->nodeDataModel());
        xmlWriter.writeStartElement("Destination");
        xmlWriter.writeStartElement("NodeId");
          xmlWriter.writeCharacters(inNode->nodeDataModel()->name());
        xmlWriter.writeEndElement(); // end NodeID
        xmlWriter.writeStartElement("NodeLayer");
          xmlWriter.writeCharacters(model->getParamLayer());
        xmlWriter.writeEndElement(); // end NodeLayer
        // I store param name as type -> name so split and proccess
        QStringList n=inPort.name.split(" ");
        xmlWriter.writeStartElement("ParameterName");
          xmlWriter.writeCharacters(n[1]);
        xmlWriter.writeEndElement(); // end parameterName
      xmlWriter.writeEndElement(); // end Destination
      }


//      auto n=c.second->getNode(QtNodes::PortType::In);
//      auto port=n->nodeDataModel()->dataType(QtNodes::PortType::In,inIndex);
//      qDebug()<<"input "<<n->nodeDataModel()->name()<<' '<<port.id<<' '<<port.name;

//      n=c.second->getNode(QtNodes::PortType::Out);
//      port=n->nodeDataModel()->dataType(QtNodes::PortType::Out,outIndex);
//      qDebug()<<"output "<<n->nodeDataModel()->name()<<' '<<port.id<<' '<<port.name ;
      xmlWriter.writeEndElement(); // end connection

    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();

    file.close();
}

void MainWindow::loadScene()
{
  m_scene->load();
}


