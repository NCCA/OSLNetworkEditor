#include "ShaderDataModel.h"

// For some reason CMake could not generate moc-files correctly
// without having a cpp for an QObject from hpp.



QString Shader::caption() const
{
  return QString("Shader");
}

QString Shader::name() const
{
  return m_name;
}

std::unique_ptr<NodeDataModel> Shader::clone() const
{
  return std::make_unique<Shader>(m_name,m_el);
}



unsigned int Shader::nPorts(PortType portType) const
{
  std::cout<<"nPorts m_el "<<m_el<<'\n';
  unsigned int result;

  switch (portType)
  {
    case PortType::In:
      result = m_el;
      break;

    case PortType::Out:
      result = 2;
     break;

    default:
      break;
  }

  return result;
}

NodeDataType Shader::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      switch (portIndex)
      {
        case 0:
          return Color().type();
          break;

        case 1:
      case 2:
      case 3:
      case 4:
      case 5:
          return Normal().type();
          break;
      }
      break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return Color().type();
          break;

        case 1:
          return Matrix().type();
          break;
      }
      break;

    default:
      break;
  }
}

std::shared_ptr<NodeData> Shader::outData(PortIndex port)
{
  if (port < 1)
    return std::make_shared<Color>();

  return std::make_shared<Matrix>();
}

void Shader::setInData(std::shared_ptr<NodeData>, int)
{
  //
}

QWidget * Shader::embeddedWidget()
{
  return nullptr;
}
