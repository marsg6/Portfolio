#include "Population_Shakespeare.h"
#include "ShakespeareWidget.h"

#include "ConstructorHelpers.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

APopulation_Shakespeare::APopulation_Shakespeare() {
	PrimaryActorTick.bCanEverTick = false;

	DefaultComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComp"));
	RootComponent = DefaultComp;

	DNAPool = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ., ");
	TargetPhrase = TEXT("To be or not to be.");
	PhraseLen = TargetPhrase.Len();

	TotalPopulation = 200;
	TotalGeneration = 0;
	MutationRate = 0.005f;

	TotalFitnesses = 0;

	static ConstructorHelpers::FClassFinder<UShakespeareWidget> ShakespeareWidgetFinder(TEXT("WidgetBlueprint'/Game/Blueprints/Genetic/Widget/ShakespeareWidget_BP.ShakespeareWidget_BP_C'"));
	if (ShakespeareWidgetFinder.Succeeded()) {
		ShakespeareWidgetClass = ShakespeareWidgetFinder.Class;
	}
}

void APopulation_Shakespeare::BeginPlay() {
	Super::BeginPlay();

	auto ShakespeareWidget = CreateWidget<UShakespeareWidget>(UGameplayStatics::GetPlayerController(this, 0), ShakespeareWidgetClass);
	if (ShakespeareWidget) {
		ShakespeareWidget->AddToViewport();
		ShakespeareWidget->InitWidget(this);
	}
}

void APopulation_Shakespeare::RandomizeDNAs() {
	TotalGeneration = 1;

	for (auto& DNA : DNAs) {
		DNA.Chars = TargetPhrase;
		for (int i = 0; i < PhraseLen; ++i) {
			DNA.Chars[i] = DNAPool[(UKismetMathLibrary::RandomInteger(DNAPool.Len()))];
		}
		DNA.Fitness = CalcFitness(DNA.Chars);
		TotalFitnesses += DNA.Fitness;
	}
}

int32 APopulation_Shakespeare::CalcFitness(FString DNA) {
	int32 Count = 0;
	for (int32 i = 0; i < PhraseLen; ++i) {
		if (DNA[i] == TargetPhrase[i]) {
			++Count;
		}
	}
	return Count;
}

FString APopulation_Shakespeare::PickByFitness() {
	while (true) {
		int32 Rand = UKismetMathLibrary::RandomInteger(TotalFitnesses);
		int32 i = UKismetMathLibrary::RandomInteger(TotalPopulation);
		int32 Fitness = DNAs[i].Fitness;
		if (PhraseLen < 2 * Fitness) {
			if (Rand < 2 * Fitness) {
				return DNAs[i].Chars;
			}
		}
		else {
			if (Rand < Fitness) {
				return DNAs[i].Chars;
			}
		}
	}
}

FString APopulation_Shakespeare::CrossOver() {
	return PickByFitness().Mid(0, PhraseLen / 2) + PickByFitness().Mid(PhraseLen / 2);
}

void APopulation_Shakespeare::Mutate(FString& DNA) {
	for (int32 i = 0; i < PhraseLen; ++i) {
		if (UKismetMathLibrary::RandomFloat() <= MutationRate) {
			DNA[i] = DNAPool[(UKismetMathLibrary::RandomInteger(DNAPool.Len()))];
		}
	}
}

void APopulation_Shakespeare::CreateNewGeneration() {
	for (int i = 0; i < TotalPopulation; ++i) {
		int32 OldFitness = DNAs[i].Fitness;
		DNAs[i].Chars = CrossOver();
		Mutate(DNAs[i].Chars);
		int32 NewFitness = CalcFitness(DNAs[i].Chars);
		DNAs[i].Fitness = NewFitness;

		TotalFitnesses += NewFitness - OldFitness;
	}

	OnGenerationChanged.ExecuteIfBound();

	++TotalGeneration;

	if (!IsOptimal()) {
		GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &APopulation_Shakespeare::CreateNewGeneration));
	}
	else {
		DNAs.Sort([](auto lDNA, auto rDNA) { return lDNA.Fitness > rDNA.Fitness; });
		OnGenerationChanged.ExecuteIfBound();
		OnTargetFound.ExecuteIfBound();
	}
}

bool APopulation_Shakespeare::IsOptimal() {
	for (const auto& DNA : DNAs) {
		if (DNA.Chars == TargetPhrase) {
			return true;
		}
	}
	return false;
}

void APopulation_Shakespeare::Start() {
	/* Initialize Info */
	TotalGeneration = 0;
	TotalFitnesses = 0;

	DNAs.AddDefaulted(TotalPopulation);
	RandomizeDNAs();
	CreateNewGeneration();
}

void APopulation_Shakespeare::End() {
	/* Clear Info */
	TotalGeneration = 0;
	TotalFitnesses = 0;

	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void APopulation_Shakespeare::SetTargetPhrase(const FString& NewTargetPhrase) {
	TargetPhrase = NewTargetPhrase;
}

void APopulation_Shakespeare::SetPhraseLen(int32 NewPhraseLen) {
	PhraseLen = NewPhraseLen;
}