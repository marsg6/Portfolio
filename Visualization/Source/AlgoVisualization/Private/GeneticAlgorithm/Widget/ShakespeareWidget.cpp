#include "ShakespeareWidget.h"
#include "Population_Shakespeare.h"

#include "EditableTextBox.h"
#include "ScrollBox.h"
#include "TextBlock.h"

void UShakespeareWidget::InitWidget(class APopulation_Shakespeare* NewPopulation) {
	Population = NewPopulation;

	FScriptDelegate TargetPhraseDelegate;
	TargetPhraseDelegate.BindUFunction(this, TEXT(""));
	TargetPhrase->OnTextChanged.AddUnique(TargetPhraseDelegate);
	if (Population) {
		TargetPhrase->SetText(FText::FromString(Population->GetOptimalSentence()));
	}

	if (Population) {
		for (int i = 0; i < 100 && i < Population->GetTotalPopulation(); ++i) {
			UTextBlock* Sentence = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
			PopulationList->AddChild(Sentence);
		}

		Population->OnGenerationChanged.BindUFunction(this, TEXT("ChangeGeneration"));
	}
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
		return FText::FromString(Default + FString::FromInt(Population->GetTotalFitnesses()) + TEXT("%"));
	}
	return FText::FromString(Default);
}

FText UShakespeareWidget::SetMutationRate() {
	FString Default = TEXT("Mutation Rate = ");
	if (Population) {
		return  FText::FromString(Default + FString::FromInt(Population->GetMutationRate()) + TEXT("%"));
	}
	return FText::FromString(Default);
}

void UShakespeareWidget::ChangeGeneration() {
	for (int i = 0; i < PopulationList->GetChildrenCount(); ++i) {
		auto TextBlock = Cast<UTextBlock>(PopulationList->GetChildAt(i));
	}
}