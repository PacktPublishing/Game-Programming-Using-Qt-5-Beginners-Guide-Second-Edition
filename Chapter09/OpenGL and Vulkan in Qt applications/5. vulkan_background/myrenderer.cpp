#include "myrenderer.h"
#include <QVulkanFunctions>
#include <QFile>

MyRenderer::MyRenderer(QVulkanWindow *w)
    : m_window(w)
{
}

void MyRenderer::initResources()
{
    VkDevice device = m_window->device();
    m_devFuncs = m_window->vulkanInstance()->deviceFunctions(device);
}

void MyRenderer::startNextFrame()
{
    m_hue += 0.005f;
    if (m_hue > 1.0f) {
        m_hue = 0.0f;
    }
    QColor color = QColor::fromHslF(m_hue, 1, 0.5);

    VkClearValue clearValues[2];
    memset(clearValues, 0, sizeof(clearValues));
    clearValues[0].color = {
        static_cast<float>(color.redF()),
        static_cast<float>(color.greenF()),
        static_cast<float>(color.blueF()),
        1.0f
    };
    clearValues[1].depthStencil = { 1.0f, 0 };

    VkRenderPassBeginInfo info;
    memset(&info, 0, sizeof(info));
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.renderPass = m_window->defaultRenderPass();
    info.framebuffer = m_window->currentFramebuffer();
    const QSize imageSize = m_window->swapChainImageSize();
    info.renderArea.extent.width = imageSize.width();
    info.renderArea.extent.height = imageSize.height();
    info.clearValueCount = 2;
    info.pClearValues = clearValues;
    VkCommandBuffer commandBuffer = m_window->currentCommandBuffer();
    m_devFuncs->vkCmdBeginRenderPass(commandBuffer, &info,
                                     VK_SUBPASS_CONTENTS_INLINE);
    m_devFuncs->vkCmdEndRenderPass(commandBuffer);
    m_window->frameReady();
    m_window->requestUpdate();
}

