#ifndef TOOLBAR_EDITOR_HPP
#define TOOLBAR_EDITOR_HPP

#include "ui_toolbar_editor.h"
#include <QMainWindow>

class Toolbar_Editor : public QWidget, private Ui::Toolbar_Editor
{
    Q_OBJECT
    Q_PROPERTY(QMainWindow* targetWindow READ targetWindow WRITE setTargetWindow DESIGNABLE false)

private:

    QMainWindow* target;
    QMap<QString,QList<QAction*> > toolbar_items;
    
public:
    explicit Toolbar_Editor(QWidget *parent = 0);

    /**
     * Set the target window, will reset any changes
     */
    void setTargetWindow(QMainWindow* w);
    QMainWindow* targetWindow() const { return target; }

    QSize sizeHint();

public slots:
    /**
     * Apply changes to the target window
     */
    void apply() const;

    /**
     * Update menus and toolbars from the target window
     */
    void updateBars();

private slots:
    void on_combo_menu_currentIndexChanged(int index);
    void on_button_up_clicked();
    void on_button_down_clicked();
    void on_button_insert_clicked();
    void on_button_remove_clicked();
    void on_button_insert_separator_clicked();
    void on_button_remove_toolbar_clicked();
    void on_button_add_toolbar_clicked();


    /**
     * Update list_toolbar with the actions of the given toolbar
     */
    void update_list_toolbar(QString name);

private:
    /// Insert a new action to the current toolbar
    void insert_action(QAction* new_action);
};

#endif // TOOLBAR_EDITOR_HPP
