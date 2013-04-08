#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include "ui_test_window.h"

class Test_Window : public QMainWindow, private Ui::Test_Window
{
    Q_OBJECT
    
public:
    explicit Test_Window(QWidget *parent = 0);
};

#endif // TEST_WINDOW_HPP
