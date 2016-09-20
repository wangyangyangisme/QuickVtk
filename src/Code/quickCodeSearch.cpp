#include "quickCodeSearch.hpp"
#include "quickCodeEditor.hpp"

namespace quick {

    namespace Code {

        Search* Search::instance = nullptr;
        Qml::Register::Controller<Search> Search::Register;

        Search::Search() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Search::Create() -> void {
            instance = new Search();
        }

        auto Search::GetInstance() -> Search* {
            return instance ? instance : new Search();
        }
        
        auto Search::setFindString(const QString& findString) -> void {
            if (this->m_findString.compare(findString) == 0) {
                this->findNext();
            } else {
                this->m_findString = findString;
                emit this->findStringChanged();

                this->processSearch();
            }
        }

        auto Search::getFindString() -> QString {
            return this->m_findString;
        }

        auto Search::setVisible(bool visible) -> void {
            if (this->m_visible != visible) {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }

        auto Search::getVisible() -> bool {
            return this->m_visible;
        }

        auto Search::setCurrentMatch(int currentMatch) -> void {
            if (this->m_currentMatch != currentMatch) {
                this->m_currentMatch = currentMatch;
                emit this->currentMatchChanged();
            }
        }

        auto Search::getCurrentMatch() -> int {
            return this->m_currentMatch;
        }

        auto Search::getMatchCount() -> int {
            return this->m_matches.count();
        }

        auto Search::processSearch() -> void {
            this->setCurrentMatch(0);
            this->m_matches.clear();

            auto cursor = Editor::GetInstance()->getCurrentCursor();
            cursor.setPosition(0);

            while (true) {
                cursor = Editor::GetInstance()->getDocument()->textDocument()->find(this->m_findString, cursor, QTextDocument::FindCaseSensitively);

                if (cursor.position() > -1) {
                    this->m_matches.append(cursor);
                } else {
                    break;
                }
            }

            emit this->matchCountChanged();
        }

        auto Search::findNext() -> void {
            if (this->m_matches.count() < 1) {
                return;
            }

            this->setCurrentMatch((this->m_currentMatch + 1) % this->m_matches.count());

            auto cursor = Editor::GetInstance()->getCurrentCursor();
        }

        auto Search::findPrevious() -> void {
            if (this->m_matches.count() < 1) {
                return;
            }

            this->setCurrentMatch((this->m_currentMatch - 1) % this->m_matches.count());

            auto cursor = Editor::GetInstance()->getCurrentCursor();
        }

        void Search::clear() {
            this->m_findString = "";
            this->setCurrentMatch(0);
            this->m_matches.clear();
            emit this->matchCountChanged();
        }
    }
}
