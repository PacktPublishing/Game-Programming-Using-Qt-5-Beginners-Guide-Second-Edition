#include "mywindow.h"
#include "myrenderer.h"

QVulkanWindowRenderer *MyWindow::createRenderer() {
    return new MyRenderer(this);
}
