#ifndef CONFIG_WIDGET_PLUGIN_COLLECTION_HPP
#define CONFIG_WIDGET_PLUGIN_COLLECTION_HPP

#include <QDesignerCustomWidgetCollectionInterface>

class Config_Widget_Plugin_Collection : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "mattia.basaglia.Config_Widgets_Plugin")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    explicit Config_Widget_Plugin_Collection(QObject *parent = 0);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
   QList<QDesignerCustomWidgetInterface*> widgets;

};

#endif // CONFIG_WIDGET_PLUGIN_COLLECTION_HPP
