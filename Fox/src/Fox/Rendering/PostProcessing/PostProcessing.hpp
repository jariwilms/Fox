#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
    enum class PostProcessing
    {
        AmbientOcclusion, 
        AntiAliasing, 
        AutoExposure, 
        Bloom, 
        ChannelMixer, 
        ChromaticAberration, 
        ColorAdjustment, 
        ColorCurve, 
        Fog, 
        DepthOfField, 
        FilmGrain, 
        LensDistortion, 
        //LiftGammaGain, 
        MotionBlur, 
        //PaniniProjection, 
        ScreenSpaceReflection, 
        //ShadowsMidtonesHighlights, 
        //SplitToning, 
        ToneMapping, 
        Vignette, 
        WhiteBalance, 
    };
}
