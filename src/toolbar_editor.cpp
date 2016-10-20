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
#include "toolbar_editor.hpp"
#include <QMenu>
#include <QToolBar>

Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QToolBar*)
Q_DECLARE_METATYPE(QAction*)

Toolbar_Editor::Toolbar_Editor(QWidget *parent) :
    QWidget(parent), target(NULL)
{
    setupUi(this);

    foreach(QToolButton* b, findChildren<QToolButton*>())
        b->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void Toolbar_Editor::setTargetWindow(QMainWindow *w)
{
    target = w;
    updateBars();
}

QSize Toolbar_Editor::sizeHint() const
{
    return QSize(462,220);
}

void Toolbar_Editor::apply() const
{
    if ( !target )
        return;


    QList<QToolBar*> new_toolbars;

    for(QMap<QString,QList<QAction*> >::const_iterator i = toolbar_items.begin(),
            e = toolbar_items.end(); i != e; ++i )
    {
        QToolBar *newtb = target->findChild<QToolBar*>(i.key());

        if ( !newtb )
        {
            newtb = new QToolBar(i.key(),target);
            newtb->setObjectName(i.key());
            new_toolbars.push_back(newtb);
        }

        newtb->clear();
        foreach(QAction* act, i.value() )
        {
            newtb->insertAction(0,act);
        }

    }


    foreach(QToolBar* toolbar, target->findChildren<QToolBar*>())
    {
        if ( !toolbar_items.contains(toolbar->objectName()) )
        {
            target->removeToolBar(toolbar);
        }
    }

    foreach(QToolBar* toolbar, new_toolbars )
    {
        target->addToolBar(Qt::TopToolBarArea,toolbar);
        toolbar->show();
    }
}


void Toolbar_Editor::updateBars()
{
    if ( !target )
        return;

    combo_menu->clear();
    list_menu->clear();
    combo_toolbar->clear();
    list_toolbar->clear();
    toolbar_items.clear();

    foreach(QMenu* menu, target->findChildren<QMenu*>())
    {
        combo_menu->addItem(menu->title().replace('&',""),QVariant::fromValue(menu));
    }


    foreach(QToolBar* toolbar, target->findChildren<QToolBar*>())
    {
        toolbar_items[toolbar->objectName()] = toolbar->actions();
        combo_toolbar->addItem(toolbar->objectName()/*,QVariant::fromValue(toolbar)*/);
    }
}


void Toolbar_Editor::on_combo_menu_currentIndexChanged(int index)
{
    list_menu->clear();
    QMenu* menu = combo_menu->itemData(index).value<QMenu*>();
    if ( !menu )
        return;

    foreach(QAction* act, menu->actions())
    {
        QListWidgetItem *item;
        if ( !act->isSeparator() )
            item = new QListWidgetItem(act->icon(),act->iconText());
        else
        {
            item = new QListWidgetItem(tr("--(separator)--"));
            item->setTextAlignment(Qt::AlignHCenter);
        }

        item->setData(Qt::UserRole,QVariant::fromValue(act));
        list_menu->addItem(item);
    }
}

void Toolbar_Editor::update_list_toolbar(QString name)
{
    list_toolbar->clear();

    foreach(QAction* act, toolbar_items[name] )
    {
        QListWidgetItem *item;
        if ( !act->isSeparator() )
            item = new QListWidgetItem(act->icon(),act->iconText());
        else
        {
            item = new QListWidgetItem(tr("--(separator)--"));
            item->setTextAlignment(Qt::AlignHCenter);
        }

        item->setData(Qt::UserRole,QVariant::fromValue(act));
        list_toolbar->addItem(item);
    }

}

void Toolbar_Editor::on_button_up_clicked()
{

    int curr_index = list_toolbar->currentRow();

    QList<QAction*>& list = toolbar_items[combo_toolbar->currentText()];
    if ( curr_index < 1 || curr_index >= list.size() )
        return;

    qSwap(list[curr_index],list[curr_index-1]);

    update_list_toolbar(combo_toolbar->currentText());
    list_toolbar->setCurrentRow(curr_index-1);
}


void Toolbar_Editor::on_button_down_clicked()
{

    int curr_index = list_toolbar->currentRow();

    QList<QAction*>& list = toolbar_items[combo_toolbar->currentText()];
    if ( curr_index < 0 || curr_index >= list.size()-1 )
        return;

    qSwap(list[curr_index],list[curr_index+1]);

    update_list_toolbar(combo_toolbar->currentText());
    list_toolbar->setCurrentRow(curr_index+1);



}

void Toolbar_Editor::on_button_insert_clicked()
{
    QListWidgetItem *item = list_menu->currentItem();

    if (item == Q_NULLPTR)
        return;

    insert_action( item->data(Qt::UserRole).value<QAction*>() );
}

void Toolbar_Editor::on_button_remove_clicked()
{
    int to_rm = list_toolbar->currentRow();

    QList<QAction*>& list = toolbar_items[combo_toolbar->currentText()];
    if ( to_rm >= 0 && to_rm < list.size() )
    {
        list.removeAt(to_rm);
        update_list_toolbar(combo_toolbar->currentText());
        list_toolbar->setCurrentRow(to_rm-1);
    }

}

void Toolbar_Editor::on_button_insert_separator_clicked()
{
    QAction* act = new QAction(NULL);
    act->setSeparator(true);
    insert_action(act);
}

void Toolbar_Editor::insert_action(QAction *new_action)
{
    int act_before = list_toolbar->currentRow();

    if ( new_action )
    {
        QList<QAction*>& list = toolbar_items[combo_toolbar->currentText()];
        if ( act_before >= 0 && act_before < list.size() )
        {
            list.insert(act_before+1,new_action);
            update_list_toolbar(combo_toolbar->currentText());
            list_toolbar->setCurrentRow(act_before+1);
        }
        else
        {
            list.push_back(new_action);
            update_list_toolbar(combo_toolbar->currentText());
            list_toolbar->setCurrentRow(list.size()-1);
        }

    }
}

void Toolbar_Editor::on_button_remove_toolbar_clicked()
{
    toolbar_items.remove(combo_toolbar->currentText());
    combo_toolbar->removeItem(combo_toolbar->currentIndex());
}

void Toolbar_Editor::on_button_add_toolbar_clicked()
{
    QString name = QString("custom_toolbar_%1").arg(toolbar_items.size());
    toolbar_items.insert(name,QList<QAction*>());

    combo_toolbar->addItem(name);
    combo_toolbar->setCurrentIndex(combo_toolbar->count()-1);
}


void Toolbar_Editor::setButtonStyle(Qt::ToolButtonStyle style)
{
    foreach(QToolButton* b, findChildren<QToolButton*>())
        b->setToolButtonStyle(style);
}

Qt::ToolButtonStyle Toolbar_Editor::buttonStyle() const
{
    return button_insert->toolButtonStyle();
}
