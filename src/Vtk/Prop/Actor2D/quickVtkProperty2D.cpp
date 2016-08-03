#include "quickVtkProperty2D.hpp"
#include "quickVtkActor2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Property2D> Property2D::Register;

        Property2D::Property2D() {
        }

        Property2D::Property2D(Actor2D* actor2D) : m_actor2D(actor2D) {
            this->m_vtkActor2D = this->m_actor2D->Actor2D::getVtkObject();
        }

        auto Property2D::setActor2D(Actor2D* actor2D) -> void {
            this->m_vtkActor2D = actor2D->Actor2D::getVtkObject();
        }

        auto Property2D::update() -> void {
            this->m_actor2D->update();
        }

        auto Property2D::setColor(QColor color) -> void {
            this->m_color = color;

            this->m_vtkActor2D->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->colorChanged();
        }

        auto Property2D::getColor() -> QColor {
            return this->m_color;
        }

        auto Property2D::setOpacity(double opacity) -> void {
            this->m_vtkActor2D->GetProperty()->SetOpacity(opacity);
            this->update();

            emit this->opacityChanged();
        }

        auto Property2D::getOpacity() -> double {
            return this->m_vtkActor2D->GetProperty()->GetOpacity();
        }

        Property2D::~Property2D() {
            this->m_vtkActor2D = nullptr;
            this->m_actor2D = nullptr;
        }
    }
}