#include "ShaderParams.h"
#include "ui_ShaderParams.h"

ShaderParams::ShaderParams(QWidget *parent) :
  QFrame(parent),
  ui(new Ui::ShaderParams)
{
  ui->setupUi(this);
}

ShaderParams::~ShaderParams()
{
  delete ui;
}

QString ShaderParams::nodeLayer() const
{
  return ui->m_nodeLayer->text();
}

void ShaderParams::setNodeLayer(QString t)
{
  ui->m_nodeLayer->setText(t);
}



QString ShaderParams::nodeLabel() const
{
  return ui->m_label->text();
}

void ShaderParams::setNodeLabel(QString t)
{
  ui->m_label->setText(t);
}


void ShaderParams::setNodeVisibility(QString t)
{
  if(t == "external")
    ui->m_visibility->setCurrentIndex(0);
  else
    ui->m_visibility->setCurrentIndex(1);

}


QString ShaderParams::nodeVisibility() const
{
  return ui->m_visibility->itemText(ui->m_visibility->currentIndex());
}
