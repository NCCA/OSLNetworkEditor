#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <nodes/NodeData.hpp>
#include <nodes/FlowScene.hpp>
#include <nodes/FlowView.hpp>
#include <nodes/DataModelRegistry.hpp>
#include <nodes/ConnectionStyle.hpp>

#include "ShaderDataModel.h"
#include "ShaderParser.h"

/// @file MainWindow.h

class MainWindow : public QMainWindow
{
  Q_OBJECT
  protected :
    /// @brief override the keyPressEvent inherited from QObject so we can handle key presses.
    /// @param [in] _event the event to process
    void keyPressEvent(QKeyEvent *_event) override;
    /// @brief override the resizeEvent inherited from QObject so we can handle key presses.
    /// @param [in] _event the event to process

    void resizeEvent (QResizeEvent * _event) override;
    public:
    /// @brief constructor
    /// @param _parent the parent window the for this window
    MainWindow(const QStringList _args,QWidget *_parent = 0);
    /// @brief  dtor free up the GLWindow and all resources
    ~MainWindow();
  private slots :

  private:

    QtNodes::FlowScene *m_scene;
    QtNodes::FlowView *m_view;
    void addShader(const QString _name);
    QtNodes::NodeData *  createParam(ShaderParser::ParamType _p, QString _name) const;
    void loadShaderFromFile();
    void writeXML()const;
    void nodeVisitor(QtNodes::Node *data);


};

#endif // MAINWINDOW_H
