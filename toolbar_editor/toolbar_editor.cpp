#include "toolbar_editor.hpp"
#include <QMenu>
#include <QToolBar>

Toolbar_Editor::Toolbar_Editor(QWidget *parent) :
    QWidget(parent), target(NULL)
{
    setupUi(this);
}

void Toolbar_Editor::setTargetWindow(QMainWindow *w)
{
    target = w;
    updateBars();
}

QSize Toolbar_Editor::sizeHint()
{
    return QSize(330,220);
}

void Toolbar_Editor::apply() const
{
    /// \todo
    if ( !target )
        return;
}


void Toolbar_Editor::updateBars()
{
    if ( !target )
        return;

    combo_menu->clear();
    list_menu->clear();
    combo_toolbar->clear();
    list_toolbar->clear();
    toobar_items.clear();

    foreach(QMenu* menu, target->findChildren<QMenu*>())
    {
        combo_menu->addItem(menu->title().replace('&',""),QVariant::fromValue(menu));
    }


    foreach(QToolBar* toolbar, target->findChildren<QToolBar*>())
    {
        toobar_items[toolbar->objectName()] = toolbar->actions();
        combo_toolbar->addItem(toolbar->objectName(),QVariant::fromValue(toolbar));
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
            item = new QListWidgetItem("--(separator)--");
            item->setTextAlignment(Qt::AlignHCenter);
        }

        item->setData(Qt::UserRole,QVariant::fromValue(act));
        list_menu->addItem(item);
    }
}

void Toolbar_Editor::update_list_toolbar(QString name)
{
    list_toolbar->clear();

    foreach(QAction* act, toobar_items[name] )
    {
        QListWidgetItem *item;
        if ( !act->isSeparator() )
            item = new QListWidgetItem(act->icon(),act->iconText());
        else
        {
            item = new QListWidgetItem("--(separator)--");
            item->setTextAlignment(Qt::AlignHCenter);
        }

        item->setData(Qt::UserRole,QVariant::fromValue(act));
        list_toolbar->addItem(item);
    }

}

void Toolbar_Editor::on_button_up_clicked()
{

    int curr_index = list_toolbar->currentRow();

    QList<QAction*>& list = toobar_items[combo_toolbar->currentText()];
    if ( curr_index < 1 || curr_index >= list.size() )
        return;

    qSwap(list[curr_index],list[curr_index-1]);

    update_list_toolbar(combo_toolbar->currentText());
    list_toolbar->setCurrentRow(curr_index-1);
}


void Toolbar_Editor::on_button_down_clicked()
{

    int curr_index = list_toolbar->currentRow();

    QList<QAction*>& list = toobar_items[combo_toolbar->currentText()];
    if ( curr_index < 0 || curr_index >= list.size()-1 )
        return;

    qSwap(list[curr_index],list[curr_index+1]);

    update_list_toolbar(combo_toolbar->currentText());
    list_toolbar->setCurrentRow(curr_index+1);



}

void Toolbar_Editor::on_button_insert_clicked()
{
    insert_action( list_menu->currentItem()->data(Qt::UserRole).value<QAction*>() );
}

void Toolbar_Editor::on_button_remove_clicked()
{
    int to_rm = list_toolbar->currentRow();


    QList<QAction*>& list = toobar_items[combo_toolbar->currentText()];
    if ( to_rm >= 0 && to_rm < list.size() )
    {
        list.removeAt(to_rm);
        update_list_toolbar(combo_toolbar->currentText());
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
        QList<QAction*>& list = toobar_items[combo_toolbar->currentText()];
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
