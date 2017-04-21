#ifndef SHADERPARAMS_H
#define SHADERPARAMS_H

#include <QFrame>

namespace Ui {
  class ShaderParams;
}

class ShaderParams : public QFrame
{
    Q_OBJECT

  public:
    explicit ShaderParams(QWidget *parent = 0);
    ~ShaderParams();
    QString nodeLayer() const;
    QString nodeLabel() const;
    QString nodeVisibility() const;
  private:
    Ui::ShaderParams *ui;
};

#endif // SHADERPARAMS_H
