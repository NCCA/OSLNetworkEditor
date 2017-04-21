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

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"color", "color"};
  }
};


class Int : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"int", "int"};
  }
};

class Float : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"float", "float"};
  }
};

class Point : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"point", "point"};
  }
};


class Vector : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"vector", "vector"};
  }
};

class Normal : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"normal", "normal"};
  }
};

class Matrix : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"matrix", "matrix"};
  }
};

class String : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"string", "string"};
  }
};

class Void : public QtNodes::NodeData
{
public:

  QtNodes::NodeDataType type() const override
  {
    return QtNodes::NodeDataType {"void", "void"};
  }
};

#endif
