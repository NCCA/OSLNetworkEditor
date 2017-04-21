#ifndef SHADERNODEDATA_H_
#define SHADERNODEDATA_H_


#include <iostream>
#include <QtCore/QObject>

#include <nodes/NodeData.hpp>
#include <nodes/NodeDataModel.hpp>

#include <memory>


/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class Color : public QtNodes::NodeData
{
public:
  Color()=default;
  Color(const QString &_text) : m_text(_text){}
  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"color", m_text};
  }

 private :
  QString m_text;
};


class Int : public QtNodes::NodeData
{
public:
    Int()=default;
    Int(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"int", m_text};
  }
private :
   QString m_text;
};

class Float : public QtNodes::NodeData
{
public:
    Float()=default;
    Float(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"float", m_text};
  }
  private :
   QString m_text;
};

class Point : public QtNodes::NodeData
{
public:
    Point()=default;
    Point(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"point", m_text};
  }
  private :
   QString m_text;
};


class Vector : public QtNodes::NodeData
{
public:
    Vector()=default;
    Vector(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"vector", m_text};
  }

  private :
   QString m_text;
};

class Normal : public QtNodes::NodeData
{
public:
    Normal()=default;
    Normal(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"normal", m_text};
  }

  private :
   QString m_text;
};

class Matrix : public QtNodes::NodeData
{
public:
    Matrix()=default;
    Matrix(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"matrix", m_text};
  }
  private :
   QString m_text;
};

class String : public QtNodes::NodeData
{
public:
    String()=default;
    String(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"string", m_text};
  }
  private :
   QString m_text;
};

class Void : public QtNodes::NodeData
{
public:
    Void()=default;
    Void(const QString &_text) : m_text(_text){}

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"void", m_text};
  }
  private :
   QString m_text;
};

#endif
