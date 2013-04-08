#include "config_widget_plugin_collection.hpp"
#include "toolbar_editor_plugin.hpp"

Config_Widget_Plugin_Collection::Config_Widget_Plugin_Collection(QObject *parent)
    : QObject(parent)
{
    widgets.push_back(new Toolbar_Editor_Plugin(this));
}

QList<QDesignerCustomWidgetInterface *> Config_Widget_Plugin_Collection::customWidgets() const
{
    return widgets;
}
