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

	DNAPool = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,");
	OptimalSentence = TEXT("To be or not to be.");
	SentenceLen = OptimalSentence.Len();
	
	TotalPopulation = 200;
	TotalGeneration = 1;
	MutationRate = 0.01f;

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

	DNAs.AddDefaulted(TotalPopulation);
	RandomizeDNAs();
	CreateNewGeneration();
}

void APopulation_Shakespeare::RandomizeDNAs() {
	for (auto& DNA : DNAs) {
		DNA.Chars = OptimalSentence;
		for (int i = 0; i < SentenceLen; ++i) {
			DNA.Chars[i] = DNAPool[(UKismetMathLibrary::RandomInteger(DNAPool.Len()))];
		}
		DNA.Fitness = CalcFitness(DNA.Chars);
		TotalFitnesses += DNA.Fitness;
	}
}

int32 APopulation_Shakespeare::CalcFitness(FString DNA) {
	int32 Count = 0;
	for (int32 i = 0; i < SentenceLen; ++i) {
		if (DNA[i] == OptimalSentence[i]) {
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
		if (SentenceLen < 2 * Fitness) {
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
	FString ParentA = PickByFitness();
	FString ParentB = PickByFitness();

	return ParentA.Mid(0, SentenceLen / 2) + ParentB.Mid(SentenceLen / 2);
}

void APopulation_Shakespeare::Mutate(FString& DNA) {
	for (int32 i = 0; i < SentenceLen; ++i) {
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

		UE_LOG(LogTemp, Error, TEXT("%s"), *DNAs[i].Chars);
	}

	RecordedTotalFitnesses = static_cast<float>(TotalFitnesses) / (TotalPopulation * SentenceLen);
	++TotalGeneration;

	if (!IsOptimal()) {
		GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &APopulation_Shakespeare::CreateNewGeneration));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("FINISH!!!!!!!!!!!!!!!!"));
	}
}

bool APopulation_Shakespeare::IsOptimal() {
	for (const auto& DNA : DNAs) {
		if (DNA.Chars == OptimalSentence) {
			return true;
		}
	}
	return false;
}