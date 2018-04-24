#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QObject>
#include <QVulkanWindow>

class MyWindow : public QVulkanWindow {
public:
    QVulkanWindowRenderer *createRenderer() override;
};


#endif // MYWINDOW_H
