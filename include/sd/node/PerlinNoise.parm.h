#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(Frequency,   Float, frequency,    m_frequency,    (1.0f))
PARAM_INFO(Lacunarity,  Float, lacunarity,   m_lacunarity,   (2.0f))
PARAM_INFO(OctaveCount, Int,   octave_count, m_octave_count, (6))
PARAM_INFO(Persistence, Float, persistence,  m_persistence,  (0.5f))
PARAM_INFO(Seed,        Int,   seed,         m_seed,         (0))
