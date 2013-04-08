#ifndef TOOLBAR_EDITOR_PLUGIN_HPP
#define TOOLBAR_EDITOR_PLUGIN_HPP
#include <QDesignerCustomWidgetInterface>
#include <QObject>
class Toolbar_Editor_Plugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    Toolbar_Editor_Plugin (QObject *parent = 0);

    void initialize(QDesignerFormEditorInterface *core);
    bool isInitialized() const;

    QWidget *createWidget(QWidget *parent);

    QString name() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;

    QString domXml() const;

    QString includeFile() const;

private:
    bool initialized;

};

#endif // TOOLBAR_EDITOR_PLUGIN_HPP
