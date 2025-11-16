#include "visualization.h"
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkLineSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>

Visualizer::Visualizer() {
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_renderWindow->AddRenderer(m_renderer);
    m_interactor->SetRenderWindow(m_renderWindow);
    m_renderer->SetBackground(1.0, 1.0, 1.0); // 白色背景
}

void Visualizer::addModel(vtkSmartPointer<vtkPolyData> polyData, const Vector3D& color) {
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color.x, color.y, color.z);
    m_renderer->AddActor(actor);
}

void Visualizer::addSphereMarker(const Vector3D& center, double radius, const Vector3D& color) {
    auto sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(center.x, center.y, center.z);
    sphere->SetRadius(radius);
    sphere->SetThetaResolution(20);
    sphere->SetPhiResolution(20);
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color.x, color.y, color.z);
    m_renderer->AddActor(actor);
}

void Visualizer::addLineMarker(const Vector3D& p1, const Vector3D& p2, const Vector3D& color, double lineWidth) {
    auto line = vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(p1.x, p1.y, p1.z);
    line->SetPoint2(p2.x, p2.y, p2.z);
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(line->GetOutputPort());
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color.x, color.y, color.z);
    actor->GetProperty()->SetLineWidth(lineWidth);
    m_renderer->AddActor(actor);
}

void Visualizer::show() {
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_interactor->SetInteractorStyle(style);
    m_renderWindow->Render();
    m_interactor->Start();
}
