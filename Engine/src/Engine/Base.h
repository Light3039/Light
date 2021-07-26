#pragma once

#include <memory>

namespace Light {

	// Ref (Ref)
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr Ref<T> MakeRef(T* rawPointer)
	{
		return std::shared_ptr<T>(T);
	}

	// Scope (std::unique_ptr)
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr std::unique_ptr<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr std::unique_ptr<T> MakeScope(T* rawPointer)
	{
		return std::unique_ptr<T>(rawPointer);
	}

}

// platform	
#define LT_WIN(x) // windows
#define LT_LIN(x) // linux
#define LT_MAC(x) // mac

#if defined(LIGHT_PLATFORM_WINDOWS)
	#define LT_BUILD_PLATFORM "Windows"
	#define LT_WIN(x) x
	
#elif defined(LIGHT_PLATFORM_LINUX)
	#define LT_BUILD_PLATFORM "Linux"
	#define LT_LIN(x) x
	
#elif defined(LIGHT_PLATFORM_MAC)
	#error "Unsupported platform: MAC"
	#define LT_MAC(x) x
	
#else
	#error "Unsupported platform: Unknown"

#endif


// operations
#define BIT(x) 1 << x

// assertions
#if defined(LIGHT_DIST)
	#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_FILE_CRITICAL(__VA_ARGS__); throw ::Light::FailedEngineAssertion(__FILE__, __LINE__); } }
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_FILE_CRITICAL(__VA_ARGS__); throw ::Light::FailedClientAssertion(__FILE__, __LINE__); } }
#else
	#define LT_ENGINE_ASSERT(x, ...) { if(!(x)) { LT_ENGINE_CRITICAL(__VA_ARGS__); LT_BREAK(); throw ::Light::FailedEngineAssertion(__FILE__, __LINE__); } }
	#define LT_CLIENT_ASSERT(x, ...) { if(!(x)) { LT_CLIENT_CRITICAL(__VA_ARGS__); LT_BREAK(); throw ::Light::FailedClientAssertion(__FILE__, __LINE__); } }
#endif

///*** [  PORTABLES  ] ***///
//** PORTABLE_DEBUG_BREAK **//
// copied from: https://github.com/nemequ/portable-snippets/tree/master/debug-trap
#if defined(__has_builtin) && !defined(__ibmxl__)
	#if __has_builtin(__builtin_debugtrap)
		#define LT_BREAK() __builtin_debugtrap()

	#elif __has_builtin(__debugbreak)
		#define LT_BREAK() __debugbreak()

	#endif
#endif

#if !defined(LT_BREAK)
	#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
		#define LT_BREAK() __debugbreak()

	#elif defined(__ARMCC_VERSION)
		#define LT_BREAK() __breakpoint(42)

	#elif defined(__ibmxl__) || defined(__xlC__)
		#include <builtins.h>
		#define LT_BREAK() __trap(42)

	#elif defined(__DMC__) && defined(_M_IX86)
		static inline void LT_BREAK(void) { __asm int 3h; }

	#elif defined(__i386__) || defined(__x86_64__)
		static inline void LT_BREAK(void) { __asm__ __volatile__("int3"); }

	#elif defined(__thumb__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xde01"); }

	#elif defined(__aarch64__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xd4200000"); }

	#elif defined(__arm__)
		static inline void LT_BREAK(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }

	#elif defined (__alpha__) && !defined(__osf__)
		static inline void LT_BREAK(void) { __asm__ __volatile__("bpt"); }

	#elif defined(_54_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("ESTOP"); }

	#elif defined(_55_)
		static inline void LT_BREAK(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }

	#elif defined(_64P_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("SWBP 0"); }

	#elif defined(_6x_)
		static inline void LT_BREAK(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }

	#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
		#define LT_BREAK() __builtin_trap()

	#else
		#include <signal.h>

	#if defined(SIGTRAP)
		#define LT_BREAK() raise(SIGTRAP)

	#else
		#define LT_BREAK() raise(SIGABRT)

	#endif
	#endif
#endif

#if !defined(LT_BREAK)
	#define LT_BERAK LT_ENGINE_WARN("Unable to break!, LT_BREAK macro is undefined")
#endif

//** PORTABLE_DEBUG_BREAK **//
///*** [  PORTABLES  ] ***///


#ifndef LT_LOGGER_H
#include "Debug/Logger.h"
#define LT_LOGGER_H
#endif

#include "Debug/Exceptions.h"
#include "Utility/Stringifier.h"