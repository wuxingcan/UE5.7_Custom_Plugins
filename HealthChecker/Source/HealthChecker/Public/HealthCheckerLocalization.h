// Copyright UMIUSHI Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
//#include "InternationalizationSettingsModel.h"

namespace HC4UE
{

bool IsEditorJapaneseLanguage()
{
	//if(const UInternationalizationSettingsModel* InternationalizationSettingsModel = GetDefault<UInternationalizationSettingsModel>())
	//{
	//	FString EditorLanguage;
	//	if(InternationalizationSettingsModel->GetEditorLanguage(EditorLanguage))
	//	{
	//		if(EditorLanguage == TEXT("ja"))
	//		{
	//			return true;
	//		}
	//	}
	//}

	const FCulture& Culture = FInternationalization::Get().GetCurrentLanguage().Get();
	const FString& CurrentLanguage = Culture.GetName();
	if(CurrentLanguage == TEXT("ja-JP") || CurrentLanguage == TEXT("ja"))
	{
		return true;
	}

	return false;
}

const TCHAR* GetHealthCheckerEditorLanguage()
{
	return IsEditorJapaneseLanguage() ? TEXT("ja") : TEXT("en");
}

template<typename... TextArgs>
FText TextFormat(const FText& Format, TextArgs&&... Args)
{
	// FText::Formatで使用されるNumberFormattingOptionsが外部から変更できないので自前で変換する

	static const FNumberFormattingOptions FormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(2).SetUseGrouping(false);

	auto ConvertArgs = [&](auto&& Arg)->FFormatArgumentValue
	{
		using ArgType = std::decay_t<decltype(Arg)>;
		if constexpr(TIsArithmetic<ArgType>::Value)
		{
			return FText::AsNumber(Arg, &FormattingOptions);
		}
		else if constexpr(std::is_same_v<ArgType, FText>)
		{
			return Arg;
		}
		else if constexpr(std::is_same_v<ArgType, FString>)
		{
			return FText::FromString(Arg);
		}
		else if constexpr(std::is_same_v<ArgType, const TCHAR*>)
		{
			return FText::FromString(Arg);
		}
		else
		{
			static_assert(sizeof(ArgType) == 0, "Unsupported type for FText format arguments");
		}
	};

	TArray<FFormatArgumentValue> Arguments;
	Arguments.Reserve(sizeof...(TextArgs));
#if (ENGINE_MAJOR_VERSION >= 5) && (_MSC_VER >= 1930)
	// VS2022以降
	(Arguments.Add(ConvertArgs(Forward<TextArgs>(Args))), ...);
#else
	// VS2019はイニシャライザリストを経由して初期化する
	using expander = int[];
	(void)expander{ 0, (Arguments.Add(ConvertArgs(Forward<TextArgs>(Args))), 0)... };
#endif
	return FText::Format(Format, Arguments);
}

const TCHAR* GetLocalizedString(const TCHAR* LocKey, const TCHAR* DefaultString = nullptr)
{
#define HC4UE_ENTRY_LOCTEXT(Key, Str) { TEXT(Key), TEXT(Str) }

	static const TMap<FName, FString> LocalizedTextMap[2] =
	{
		// 日本語
		{
#include "HealthCheckerJaText.inl"
		},
		// 英語
		{
#include "HealthCheckerEnText.inl"
		}
	};

#undef HC4UE_ENTRY_LOCTEXT

	if(FPlatformMisc::IsDebuggerPresent())
	{
		auto SameKeyCheck = []()
		{
			ensureAlwaysMsgf(LocalizedTextMap[0].Num() == LocalizedTextMap[1].Num(), TEXT("Localized text count mismatch"));
			for(auto It : LocalizedTextMap[0])
			{
				if(!LocalizedTextMap[1].Contains(It.Key))
				{
					ensureAlwaysMsgf(false, TEXT("Localization (en) key not found: %s"), *It.Key.ToString());
				}
			}
			for(auto It : LocalizedTextMap[1])
			{
				if(!LocalizedTextMap[0].Contains(It.Key))
				{
					ensureAlwaysMsgf(false, TEXT("Localization (ja) key not found: %s"), *It.Key.ToString());
				}
			}
			return true;
		};
		static const bool bSameKeyCheckFirstTime = SameKeyCheck();

		if(DefaultString)
		{
			if(const FString* JapaneseLocalizedText = LocalizedTextMap[0].Find(LocKey))
			{
				ensureAlwaysMsgf(FCString::Strcmp(DefaultString, **JapaneseLocalizedText) == 0, TEXT("Japanese localized text mismatch (%s): %s <!=> %s"), LocKey, DefaultString, **JapaneseLocalizedText);
			}
			else
			{
				ensureAlwaysMsgf(false, TEXT("Localization (%s) key not found: %s"), GetHealthCheckerEditorLanguage(), LocKey);
			}
		}
	}

	const int32 LocalizedTextMapIndex = IsEditorJapaneseLanguage() ? 0 : 1;
	if(const FString* LocalizedText = LocalizedTextMap[LocalizedTextMapIndex].Find(LocKey))
	{
		return **LocalizedText;
	}

	if(FPlatformMisc::IsDebuggerPresent())
	{
		ensureAlwaysMsgf(false, TEXT("Localization (%s) key not found: %s"), GetHealthCheckerEditorLanguage(), LocKey);
	}

	return DefaultString ? DefaultString : TEXT("Error");
}

FText GetLocalizedText(const TCHAR* LocKey, const TCHAR* DefaultString = nullptr)
{
	return FText::FromString(GetLocalizedString(LocKey, DefaultString));
}

} // namespace HC4UE
