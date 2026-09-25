from pathlib import Path
path = Path(r"D:\workspace\code\cpp\ue\5.7\CustonPlugins\Plugins\HealthChecker\Source\HealthChecker\Private\HealthCheckerEditorSubsystem.cpp")
text = path.read_text(encoding="utf-8")
start = text.find("\tauto WriteHealthCheckerReport")
end = text.find("\tGAssetRegistry = nullptr;")
if start < 0 or end < 0:
    raise SystemExit(f"markers not found {start} {end}")
new = r'''	auto BuildReportView = [&WorldPackagePath, &WorldType, &HealthCheckerReport, &AllScoreArray, &Settings]()
	{
		FHealthCheckerReportView View;
		View.bValid = true;
		View.Project = FApp::GetProjectName();
		View.Map = WorldPackagePath;
		View.Engine = FString::Printf(TEXT("UE%s - %s - %s"), *FEngineVersion::Current().ToString(EVersionComponent::Patch), GetWorldTypeString(WorldType), GetHealthCheckerEditorLanguage());
		View.GeneratedBy = Settings.bUseUserNameInReport
			? FString::Printf(TEXT("%s - %s"), FPlatformProcess::ComputerName(), FPlatformProcess::UserName())
			: FString(TEXT("HC4UE"));
		View.Version = UHealthCheckerSettings::GetVersion();
		View.LastUpdate = FDateTime::Now().ToString();

		auto CalcScoreAverage = [](const TArray<FScore>& ScoreArray)
		{
			float TotalScore = 0.f;
			for(const FScore& Score : ScoreArray)
			{
				if(!Score.bAllowHealthCheck || Score.ScoreWeight <= 0.f)
				{
					continue;
				}

				TotalScore += (float)Score.Score * Score.ScoreWeight;
			}
			return (EScore)(FMath::Min<int32>(FMath::DivideAndRoundNearest<float>(TotalScore, ScoreArray.Num()), (int32)EScore::MAX - 1));
		};
		const EScore OverallScore = CalcScoreAverage(AllScoreArray);
		View.OverallScore = GetScoreString(OverallScore);
		View.OverallDescription = HC4UE_LOCTEXT_FORMAT(HC4UE_LOCTEXT("Overall_Score_Description", "総合評価は{0}です。詳細は各グラフの評価を確認してください。"), FText::FromString(View.OverallScore)).ToString();

		for(const auto& Report : HealthCheckerReport)
		{
			if(!Report.Value.Score.bAllowHealthCheck || Report.Value.Score.ScoreWeight <= 0.f)
			{
				continue;
			}

			FString KeyString = Report.Key.ToString();
			FString GraphName, CategoryString;
			if(!KeyString.Split(TEXT("_("), &GraphName, &CategoryString))
			{
				GraphName = MoveTemp(KeyString);
			}

			FText LocText;
#if HC4UE_UE5_5
			if(FText::FindTextInLiveTable_Advanced(UHealthCheckerSettings::GetHealthCheckerString(), GraphName, LocText))
#else
			if(FText::FindText(UHealthCheckerSettings::GetHealthCheckerString(), GraphName, LocText))
#endif
			{
				GraphName = LocText.ToString();
			}
			else
			{
				GraphName.ReplaceInline(TEXT("_"), TEXT(" "));
			}

			if(!CategoryString.IsEmpty())
			{
				GraphName += TEXT(" (") + CategoryString;
			}

			FHealthCheckerTableSection& Section = View.Sections.AddDefaulted_GetRef();
			Section.Title = GraphName;
			Section.Score = GetScoreString(Report.Value.Score.Score);

			FString Description = Report.Value.Description.ToString();
			for(const FText& DetailsText : Report.Value.DetailsArray)
			{
				const FString Details = DetailsText.ToString();
				if(!Details.IsEmpty())
				{
					Description += TEXT("\n\n");
					Description += Details;
				}
			}
			Section.Description = MoveTemp(Description);

			for(const FHealthCheckerChartData& ChartData : Report.Value.ChartData)
			{
				if(ChartData.Value == 0)
				{
					continue;
				}

				FHealthCheckerTableRow& Row = Section.Rows.AddDefaulted_GetRef();
				Row.Label = ChartData.Label;
				Row.Value = ChartData.Value;
				Row.TotalValue = ChartData.TotalValue;
				Row.Unit = ChartData.Unit;
				Row.TotalLabel = ChartData.TotalLabel;
				if(ChartData.TotalValue != 0)
				{
					Row.bHasRatio = true;
					Row.Ratio = SafeDivideToPercentage<float>(ChartData.Value, ChartData.TotalValue);
				}
			}
		}

		return View;
	};

	if(bCheckResult)
	{
		HealthCheckerReport::SetLast(BuildReportView());
		UE_CLOG(bSkipAutoOpenReport, LogHealthChecker, Log, TEXT("Health Checker report updated for the Slate window."));
	}

'''
path.write_text(text[:start] + new + text[end:], encoding="utf-8")
print("patched", start, end)
