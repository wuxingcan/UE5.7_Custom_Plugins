// Copyright UMIUSHI Inc. All Rights Reserved.

#include "HealthCheckerStyle.h"
#include "HealthChecker.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#if (ENGINE_MAJOR_VERSION >= 5)
#include "Styling/SlateStyleMacros.h"
#define RootToContentDir Style->RootToContentDir
#else
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#endif

TSharedPtr<FSlateStyleSet> FHealthCheckerStyle::StyleInstance = nullptr;

void FHealthCheckerStyle::Initialize()
{
	if(!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FHealthCheckerStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

namespace HC4UE
{

const TCHAR* GetStyleSetString()
{
	static const TCHAR* StyleSetChar = TEXT("HealthCheckerStyle");
	return StyleSetChar;
}

}

const FName& FHealthCheckerStyle::GetStyleSetName()
{
	static FName StyleSetName(HC4UE::GetStyleSetString());
	return StyleSetName;
}

const FVector2D Icon32x32(32, 32);

TSharedRef<FSlateStyleSet> FHealthCheckerStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("HealthChecker")->GetBaseDir() / TEXT("Resources"));

	Style->Set("HealthChecker.MenuIcon", new IMAGE_BRUSH(TEXT("HealthCheckerIcon_32x32"), Icon32x32));
	return Style;
}

void FHealthCheckerStyle::ReloadTextures()
{
	if(FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FHealthCheckerStyle::Get()
{
	return *StyleInstance;
}

#if (ENGINE_MAJOR_VERSION >= 5)
// Do nothing
#else
#undef IMAGE_BRUSH
#endif
