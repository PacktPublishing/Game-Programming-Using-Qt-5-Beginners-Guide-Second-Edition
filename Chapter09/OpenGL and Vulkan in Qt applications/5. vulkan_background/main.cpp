#include <QGuiApplication>
#include <QVulkanWindow>
#include <vulkan/vulkan.h>
#include "myrenderer.h"
#include <QVulkanInstance>
#include <QVulkanFunctions>
#include <QLoggingCategory>
#include "mywindow.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));
    QVulkanInstance vulkan;
    vulkan.setLayers({ "VK_LAYER_LUNARG_standard_validation" });
    if (!vulkan.create()) {
        qFatal("Failed to create Vulkan instance: %d", vulkan.errorCode());        
    }
    MyWindow window;
    window.resize(1024, 768);
    window.setVulkanInstance(&vulkan);
    window.show();

    return app.exec();
}
