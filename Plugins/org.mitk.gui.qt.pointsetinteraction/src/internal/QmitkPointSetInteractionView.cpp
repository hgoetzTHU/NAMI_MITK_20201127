/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "QmitkPointSetInteractionView.h"

#include <QInputDialog>
#include <QLineEdit>

#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateProperty.h>

#include <QmitkPointListWidget.h>
#include <QmitkRenderWindow.h>

const std::string QmitkPointSetInteractionView::VIEW_ID = "org.mitk.views.pointsetinteraction";

QmitkPointSetInteractionView::QmitkPointSetInteractionView()
  : m_Controls(nullptr)
{
}

QmitkPointSetInteractionView::~QmitkPointSetInteractionView()
{
}

void QmitkPointSetInteractionView::CreateQtPartControl(QWidget *parent)
{
  m_Controls = new Ui::QmitkPointSetInteractionViewControls;
  m_Controls->setupUi(parent);

  m_Controls->selectedPointSetWidget->SetDataStorage(GetDataStorage());
  m_Controls->selectedPointSetWidget->SetNodePredicate(mitk::NodePredicateAnd::New(
    mitk::TNodePredicateDataType<mitk::PointSet>::New(),
    mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("helper object"))));

  m_Controls->selectedPointSetWidget->SetSelectionIsOptional(true);
  m_Controls->selectedPointSetWidget->SetAutoSelectNewNodes(true);
  m_Controls->selectedPointSetWidget->SetEmptyInfo(QString("Please select a point set"));
  m_Controls->selectedPointSetWidget->SetPopUpTitel(QString("Select point set"));

  connect(m_Controls->selectedPointSetWidget, &QmitkSingleNodeSelectionWidget::CurrentSelectionChanged,
    this, &QmitkPointSetInteractionView::OnCurrentSelectionChanged);

  connect(m_Controls->addPointSetPushButton, &QPushButton::clicked,
    this, &QmitkPointSetInteractionView::OnAddPointSetClicked);

  if (mitk::IRenderWindowPart* renderWindowPart = GetRenderWindowPart())
  {
    RenderWindowPartActivated(renderWindowPart);
  }
}

void QmitkPointSetInteractionView::SetFocus()
{
  m_Controls->addPointSetPushButton->setFocus();
}

void QmitkPointSetInteractionView::OnCurrentSelectionChanged(QList<mitk::DataNode::Pointer> nodes)
{
  if (nodes.empty() || nodes.front().IsNull())
  {
    m_Controls->poinSetListWidget->SetPointSetNode(nullptr);
    return;
  }

  auto selectedPointSet = dynamic_cast<mitk::PointSet*>(nodes.front()->GetData());
  if (nullptr == selectedPointSet)
  {
    m_Controls->poinSetListWidget->SetPointSetNode(nullptr);
    return;
  }

  m_Controls->poinSetListWidget->SetPointSetNode(nodes.front());
}

void QmitkPointSetInteractionView::RenderWindowPartActivated(mitk::IRenderWindowPart* renderWindowPart)
{
  if (nullptr != m_Controls)
  {
    m_Controls->poinSetListWidget->AddSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("axial")->GetSliceNavigationController());
    m_Controls->poinSetListWidget->AddSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("sagittal")->GetSliceNavigationController());
    m_Controls->poinSetListWidget->AddSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("coronal")->GetSliceNavigationController());
  }
}

void QmitkPointSetInteractionView::RenderWindowPartDeactivated(mitk::IRenderWindowPart* renderWindowPart)
{
  if (nullptr != m_Controls)
  {
    m_Controls->poinSetListWidget->RemoveSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("axial")->GetSliceNavigationController());
    m_Controls->poinSetListWidget->RemoveSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("sagittal")->GetSliceNavigationController());
    m_Controls->poinSetListWidget->RemoveSliceNavigationController(renderWindowPart->GetQmitkRenderWindow("coronal")->GetSliceNavigationController());
  }
}

void QmitkPointSetInteractionView::OnAddPointSetClicked()
{
  // ask for the name of the point set
  bool ok = false;
  QString name = QInputDialog::getText(QApplication::activeWindow(),
    tr("Add point set..."), tr("Enter name for the new point set"), QLineEdit::Normal, tr("PointSet"), &ok);
  if (!ok || name.isEmpty())
  {
    return;
  }

  mitk::PointSet::Pointer pointSet = mitk::PointSet::New();
  mitk::DataNode::Pointer pointSetNode = mitk::DataNode::New();
  pointSetNode->SetData(pointSet);
  pointSetNode->SetProperty("name", mitk::StringProperty::New(name.toStdString()));
  pointSetNode->SetProperty("opacity", mitk::FloatProperty::New(1));
  pointSetNode->SetColor(1.0, 1.0, 0.0);
  this->GetDataStorage()->Add(pointSetNode);

  m_Controls->selectedPointSetWidget->SetCurrentSelectedNode(pointSetNode);
}
