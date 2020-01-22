#include "ShakespeareWidget.h"
#include "Population_Shakespeare.h"

#include "EditableTextBox.h"
#include "ScrollBox.h"
#include "TextBlock.h"
#include "Button.h"

void UShakespeareWidget::InitWidget(class APopulation_Shakespeare* NewPopulation) {
	Population = NewPopulation;

	FScriptDelegate StartButtonDelegate;
	StartButtonDelegate.BindUFunction(this, TEXT("Start"));
	StartButton->OnClicked.AddUnique(StartButtonDelegate);

	FScriptDelegate EndButtonDelegate;
	EndButtonDelegate.BindUFunction(this, TEXT("End"));
	EndButton->OnClicked.AddUnique(EndButtonDelegate);

	FScriptDelegate TextChangeDelegate;
	TextChangeDelegate.BindUFunction(this, TEXT("TargetChanged"));
	TargetPhrase->OnTextChanged.AddUnique(TextChangeDelegate);

	FScriptDelegate TextCommitDelegate;
	TextCommitDelegate.BindUFunction(this, TEXT("TargetCommitted"));
	TargetPhrase->OnTextCommitted.AddUnique(TextCommitDelegate);

	if (Population) {
		TargetPhrase->SetText(FText::FromString(Population->GetTargetPhrase()));
	}

	if (Population) {
		for (int i = 0; i < 100 && i < Population->GetTotalPopulation(); ++i) {
			UTextBlock* Sentence = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
			PopulationList->AddChild(Sentence);
		}

		Population->OnGenerationChanged.BindUFunction(this, TEXT("ChangeGeneration"));
		Population->OnTargetFound.BindUFunction(this, TEXT("TargetFound"));
	}

	bOnDoing = false;
	bTargetChanged = false;
}

FText UShakespeareWidget::SetDNAPool() {
	FString Default = TEXT("Only the components of the following list can be typed.");
	if (Population) {
		return FText::FromString(Default + TEXT(" { ") +  Population->GetDNAPool() + TEXT(" }"));
	}
	return FText::FromString(Default);
}

FText UShakespeareWidget::SetTotalPopulation() {
	FString Default = TEXT("Total Population = ");
	if (Population) {
		return FText::FromString(Default + FString::FromInt(Population->GetTotalPopulation()));
	}
	return FText::FromString(Default);
}

FText UShakespeareWidget::SetTotalGeneration() {
	FString Default = TEXT("Total Generation = ");
	if (Population) {
		return FText::FromString(Default + FString::FromInt(Population->GetTotalGeneration()));
	}
	return FText::FromString(Default);
}

FText UShakespeareWidget::SetTotalFitnesses() {
	FString Default = TEXT("Total Fitnesses = ");
	if (Population) {
		return FText::FromString(Default + FString::Printf(TEXT("%.2f"), Population->GetTotalFitnesses()) + TEXT("%"));
	}
	return FText::FromString(Default);
}

FText UShakespeareWidget::SetMutationRate() {
	FString Default = TEXT("Mutation Rate = ");
	if (Population) {
		return  FText::FromString(Default + FString::Printf(TEXT("%.2f"), Population->GetMutationRate()) + TEXT("%"));
	}
	return FText::FromString(Default);
}

void UShakespeareWidget::ChangeGeneration() {
	for (int i = 0; i < PopulationList->GetChildrenCount(); ++i) {
		auto TextBlock = Cast<UTextBlock>(PopulationList->GetChildAt(i));
		TextBlock->SetText(FText::FromString(Population->GetDNAs()[i].Chars));
	}
}

void UShakespeareWidget::Start() {
	if (!bOnDoing) {
		bOnDoing = true;

		if (Population) {
			Population->Start();
		}

		ActivateUIs(false);
	}
}

void UShakespeareWidget::End() {
	if (bOnDoing) {
		bOnDoing = false;

		if (Population) {
			Population->End();
		}

		for (int i = 0; i < PopulationList->GetChildrenCount(); ++i) {
			auto TextBlock = Cast<UTextBlock>(PopulationList->GetChildAt(i));
			TextBlock->SetText(FText::FromString(TEXT("")));
		}

		ActivateUIs(true);
	}
}

void UShakespeareWidget::TargetChanged() {
	bTargetChanged = true;
}

void UShakespeareWidget::TargetCommitted() {
	if (bTargetChanged) {
		bTargetChanged = false;

		if (Population) {
			const auto& NewPhrase = TargetPhrase->GetText().ToString();
			Population->SetTargetPhrase(NewPhrase);
			Population->SetPhraseLen(NewPhrase.Len());
		}
	}
}

void UShakespeareWidget::TargetFound() {
	bOnDoing = false;
	ActivateUIs(true);
}

void UShakespeareWidget::ActivateUIs(bool bActivate) {
	StartButton->SetIsEnabled(bActivate);
	EndButton->SetIsEnabled(!bActivate);
	TargetPhrase->SetIsEnabled(bActivate);
}