/**

@author Mattia Basaglia

@section License

    Copyright (C) 2013-2014 Mattia Basaglia

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef TOOLBAR_EDITOR_HPP
#define TOOLBAR_EDITOR_HPP

#include "ui_toolbar_editor.h"
#include <QMainWindow>

class Toolbar_Editor : public QWidget, private Ui::Toolbar_Editor
{
    Q_OBJECT
    Q_PROPERTY(QMainWindow* targetWindow READ targetWindow WRITE setTargetWindow DESIGNABLE false)
    Q_PROPERTY(Qt::ToolButtonStyle buttonStyle READ buttonStyle WRITE setButtonStyle )
    Q_PROPERTY(bool _customToolbarRemovalOnly READ customToolbarRemovalOnly WRITE setCustomToolbarRemovalOnly )

private:

    QMainWindow* target;
    QMap<QString,QList<QAction*> > toolbar_items;
    bool _customToolbarRemovalOnly;

public:
    explicit Toolbar_Editor(QWidget *parent = 0);
    static const QString customToolbarNamePrefix;

    /**
     * \brief Set the target window, will reset any changes
     */
    void setTargetWindow(QMainWindow* w);
    QMainWindow* targetWindow() const { return target; }

    QSize sizeHint() const;

    /**
     * \brief Style of the buttons
     */
    Qt::ToolButtonStyle buttonStyle() const;
    void setButtonStyle ( Qt::ToolButtonStyle style );

    /**
     * \brief Allow only non custom toolbars to be removed
     */
    bool customToolbarRemovalOnly() const;
    void setCustomToolbarRemovalOnly(bool flag);

public slots:
    /**
     * \brief Apply changes to the target window
     */
    void apply() const;

    /**
     * \brief Update menus and toolbars from the target window
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

    bool allowToolbarRemoval(QString name);
};

#endif // TOOLBAR_EDITOR_HPP
