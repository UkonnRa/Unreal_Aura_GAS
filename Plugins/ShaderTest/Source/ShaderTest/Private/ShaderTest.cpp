// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderTest.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FShaderTestModule"

void FShaderTestModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("ShaderTest"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/ShaderTest"), PluginShaderDir);
}

void FShaderTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderTestModule, ShaderTest)