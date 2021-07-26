#pragma once

#include "Base.h"

#include "Buffers.h"
#include "Blender.h"
#include "Framebuffer.h"

#include "RendererPrograms/QuadRendererProgram.h"
#include "RendererPrograms/TextureRendererProgram.h"

#define LT_MAX_QUAD_RENDERER_VERTICES    1028u * 4u
#define LT_MAX_TEXTURE_RENDERER_VERTICES 1028u * 4u

struct GLFWwindow;

namespace Light {

	class RenderCommand;
	class Blender;

	class Framebuffer;

	class Camera;

	class Texture;

	class WindowResizedEvent;

	class SharedContext;

	class Renderer
	{
	private:
		static Renderer* s_Context;
		
		// renderer programs
		QuadRendererProgram m_QuadRenderer;
		TextureRendererProgram m_TextureRenderer;

		// constant buffers
		Scope<ConstantBuffer> m_ViewProjectionBuffer;

		Scope<RenderCommand> m_RenderCommand;
		Scope<Blender> m_Blender;

		Ref<Framebuffer> m_TargetFramebuffer;

		Ref<Camera> m_Camera;

	public:
		static Scope<Renderer> Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext);
		
		static inline void SetTargetFramebuffer(Ref<Framebuffer> framebuffer) { s_Context->SetTargetFramebufferImpl(framebuffer); }

		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint) { s_Context->DrawQuadImpl(position, size, tint); }
		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture> texture) { s_Context->DrawQuadImpl(position, size, texture); }

		static inline void BeginScene(const Ref<Camera>& camera, const Ref<Framebuffer>& targetFrameBuffer = nullptr) { s_Context->BeginSceneImpl(camera, targetFrameBuffer); }
		static inline void EndScene() { s_Context->EndSceneImpl(); }
		
		void OnWindowResize(const WindowResizedEvent& event);

		void BeginFrame();
		void EndFrame();

	private:
		Renderer(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext);

		void SetTargetFramebufferImpl(Ref<Framebuffer> framebuffer);

		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint);
		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, Ref<Texture> texture);

		void BeginSceneImpl(const Ref<Camera>& camera, const Ref<Framebuffer>& targetFrameBuffer = nullptr);
		void FlushScene();
		void EndSceneImpl();
	};

}