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

QString ShaderParams::nodeLabel() const
{
  return ui->m_label->text();
}

QString ShaderParams::nodeVisibility() const
{
  return ui->m_visibility->itemText(ui->m_visibility->currentIndex());
}
