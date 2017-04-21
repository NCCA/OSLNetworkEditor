#include "ShaderParser.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>

//#include <nodes/NodeData.hpp>
//#include <nodes/FlowScene.hpp>
//#include <nodes/FlowView.hpp>
//#include <nodes/DataModelRegistry.hpp>
//#include <nodes/ConnectionStyle.hpp>

//#include "ShaderDataModel.h"

//static std::shared_ptr<QtNodes::DataModelRegistry> registerDataModels()
//{
//  auto ret = ;

//  return ret;
//}

/*
static void setStyle()
{
  QtNodes::ConnectionStyle::setConnectionStyle(
  R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}


//------------------------------------------------------------------------------

QtNodes::NodeData * createParam(ShaderParser::ParamType _p, QString _name)
{
  if(_p == ShaderParser::ParamType::INT) return new Int("int "+_name);
  else if(_p == ShaderParser::ParamType::FLOAT)  return new Float(QString("float "+_name)) ;
  else if(_p == ShaderParser::ParamType::POINT) return new Point(QString("point "+_name)) ;
  else if(_p == ShaderParser::ParamType::VECTOR) return  new Vector(QString("vector "+_name)) ;
  else if(_p == ShaderParser::ParamType::NORMAL) return new Normal(QString("normal "+_name)) ;
  else if(_p == ShaderParser::ParamType::COLOR) return new Color(QString("color "+_name)) ;
  else if(_p == ShaderParser::ParamType::MATRIX) return new Matrix(QString("matrix "+_name)) ;
  else if(_p == ShaderParser::ParamType::STRING) return new String(QString("string "+_name)) ;
  else if(_p == ShaderParser::ParamType::VOID) return new Void(QString("void "+_name)) ;
  else return nullptr;

}



void addShader(const std::string &_name, QtNodes::FlowScene &_scene)
{
  ShaderParser s(_name);
  QtNodes::DataModelRegistry &reg=_scene.registry();

  std::unique_ptr<Shader> model(new Shader(s.name().c_str(),s.numInputs(),s.numOutputs()));


  for(auto a : s.getInputs())
  {
    model->addInput(createParam(a.type,a.name.c_str()));
  }

  for(auto a : s.getOutputs())
  {
    model->addOutput(createParam(a.type,a.name.c_str()));
  }

  reg.registerModel<Shader>("nodes",std::move(model));

}


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  setStyle();

  QtNodes::FlowScene scene(std::make_shared<QtNodes::DataModelRegistry>());

  QtNodes::FlowView view(&scene);


   addShader(argv[1],scene);
   addShader("mixColours",scene);
   addShader("dots",scene);





  view.setWindowTitle("OSL Shader Network Editor");
  view.resize(800, 600);
  view.show();

  return app.exec();
}
*/

int main(int argc, char* argv[])
{
  // make an instance of the QApplication
  QApplication a(argc, argv);
  // Create a new MainWindow
  MainWindow w;
  // show it
  w.show();
  // hand control over to Qt framework
  return a.exec();
}

