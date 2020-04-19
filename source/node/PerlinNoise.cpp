#include "texgraph/node/PerlinNoise.h"
#include "texgraph/Image.h"
#include "texgraph/Context.h"

#include <unirender2/TextureDescription.h>
#include <unirender2/Device.h>

#include <noise/module/perlin.h>

namespace texgraph
{
namespace node
{

void PerlinNoise::Execute(const std::shared_ptr<dag::Context>& ctx)
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
    std::vector<short> pixels(w * h, 0);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const float fx = static_cast<float>(x) / w;
            const float fy = static_cast<float>(y) / h;
            float v = static_cast<float>(noise.GetValue(fx, 0, fy));
            v = std::min(std::max(v, -1.0f), 1.0f);
            pixels[y * h + x] = static_cast<short>((v + 1.0f) * 0.5f * 0xffff);
        }
    }

    ur2::TextureDescription desc;
    desc.target = ur2::TextureTarget::Texture2D;
    desc.width  = w;
    desc.height = h;
    desc.format = ur2::TextureFormat::R16;

    auto& dev = *std::static_pointer_cast<Context>(ctx)->ur_dev;
    auto tex = dev.CreateTexture(desc, pixels.data());
    m_img->SetTexture(tex);
}

}
}