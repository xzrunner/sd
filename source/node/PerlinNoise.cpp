#include "texgraph/node/PerlinNoise.h"
#include "texgraph/Image.h"

#include <unirender/Blackboard.h>

#include <noise/module/perlin.h>

namespace texgraph
{
namespace node
{

void PerlinNoise::Execute()
{
    m_img = std::make_shared<Image>();

    noise::module::Perlin noise;
    noise.SetNoiseQuality(noise::NoiseQuality::QUALITY_STD);
    noise.SetFrequency(m_frequency);
    noise.SetLacunarity(m_lacunarity);
    noise.SetOctaveCount(m_octave_count);
    noise.SetPersistence(m_persistence);
    noise.SetSeed(m_seed);

    const auto w = m_img->GetWidth();
    const auto h = m_img->GetHeight();
    std::vector<unsigned char> pixels(w * h, 0);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const float fx = static_cast<float>(x) / w;
            const float fy = static_cast<float>(y) / h;
            float v = static_cast<float>(noise.GetValue(fx, 0, fy));
            v = std::min(std::max(v, -1.0f), 1.0f);
            pixels[y * h + x] = static_cast<unsigned char>((v + 1.0f) * 0.5f * 255.0f);
        }
    }

    auto& rc = ur::Blackboard::Instance()->GetRenderContext();
    ur::TexturePtr tex = std::make_shared<ur::Texture>();
    tex->Upload(&rc, w, h, ur::TEXTURE_RED, pixels.data());
    m_img->SetTexture(tex);
}

}
}