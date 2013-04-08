#include "test_window.hpp"

Test_Window::Test_Window(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    toolbar_editor->setTargetWindow(this);
}
