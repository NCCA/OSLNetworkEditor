#include "ShaderParser.h"

#include <QtWidgets/QApplication>

#include <nodes/NodeData.hpp>
#include <nodes/FlowScene.hpp>
#include <nodes/FlowView.hpp>
#include <nodes/DataModelRegistry.hpp>
#include <nodes/ConnectionStyle.hpp>

#include "ShaderDataModel.h"

static std::shared_ptr<QtNodes::DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<QtNodes::DataModelRegistry>();

 // ret->registerModel<NaiveDataModel>();
   std::unique_ptr<Shader> model(new Shader("noise",5));
   //model->setEl();
   ret->registerModel<Shader>("nodes",std::move(model));

   model.reset(new Shader("dots",3));
   //model->setEl();
   ret->registerModel<Shader>("nodes",std::move(model));

   /*
     We could have more models registered.
     All of them become items in the context meny of the scene.

     ret->registerModel<AnotherDataModel>();
     ret->registerModel<OneMoreDataModel>();

   */

  return ret;
}


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

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  setStyle();

  QtNodes::FlowScene scene(registerDataModels());

  QtNodes::FlowView view(&scene);

  view.setWindowTitle("Node-based flow editor");
  view.resize(800, 600);
  view.show();

  return app.exec();
}


/*#include <cstdlib>
int main(int argc, char **argv)
{
  ShaderParser s(argv[1]);
  s.print();
  return EXIT_SUCCESS;
}
*/
