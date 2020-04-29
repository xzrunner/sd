#pragma once

#include <unirender/typedef.h>

namespace texgraph
{

class Image
{
public:
    Image() {}

    auto GetWidth() const { return m_width; }
    auto GetHeight() const { return m_height; }

    void SetTexture(const ur::TexturePtr& tex) { m_tex = tex; }
    auto GetTexture() const { return m_tex; }

private:
    size_t m_width = 256;
    size_t m_height = 256;

    ur::TexturePtr m_tex = nullptr;

}; // Image

}