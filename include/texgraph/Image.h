#pragma once

#include <unirender2/typedef.h>

namespace texgraph
{

class Image
{
public:
    Image() {}

    auto GetWidth() const { return m_width; }
    auto GetHeight() const { return m_height; }

    void SetTexture(const ur2::TexturePtr& tex) { m_tex = tex; }
    auto GetTexture() const { return m_tex; }

private:
    size_t m_width = 256;
    size_t m_height = 256;

    ur2::TexturePtr m_tex = nullptr;

}; // Image

}