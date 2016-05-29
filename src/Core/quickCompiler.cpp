#include "quickCompiler.hpp"
#include "quickUtilIO.hpp"

namespace quick {
    Compiler* Compiler::instance = nullptr;

    Qml::Register::Controller<Compiler> Compiler::Register = Qml::Register::Controller<Compiler>();

    Compiler::Compiler() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        instance = this;
    }

    auto Compiler::Create() -> void {
        instance = new Compiler();
    }

    auto Compiler::compile() -> void {

    }

    auto Compiler::openFile() -> void {
        this->m_fileName = Util::IO::FileFromDialog("Load QML File", "*.qml*");
        emit this->fileNameChanged();
    }

    auto Compiler::getFileName() -> QString {
        return this->m_fileName;
    }
}