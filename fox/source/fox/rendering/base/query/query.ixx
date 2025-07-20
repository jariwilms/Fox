export module fox.rendering.base.query;

export namespace fox::gfx::api
{
	class Query
	{
	public:
		enum class Target
		{
            AnySamplesPassed, 
            AnySamplesPassedConservative, 
            ClippingInputPrimitives, 
            ClippingOutputPrimitives, 
            ComputeShaderInvocations, 
            FragmentShaderInvocations, 
            GeometryShaderInvocations, 
            GeometryShaderPrimitivesEmitted, 
            PrimitivesGenerated, 
            PrimitivesSubmitted, 
            SamplesPassed, 
            TessellationControlShaderPatches, 
            TessellationEvaluationShaderInvocations, 
            TimeElapsed, 
            Timestamp, 
            TransformFeedbackOverflow, 
            TransformFeedbackPrimitivesWritten, 
            TransformFeedbackStreamOverflow, 
            VertexShaderInvocations, 
            VerticesSubmitted, 
		};
	};
}
