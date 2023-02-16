#pragma once

#include "stdafx.hpp"

namespace hlx
{
    struct PostProcessing
    {
        enum class Option
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
    };
}
