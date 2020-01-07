#include "Population_Shakespeare.h"

#include "TimerManager.h"

#include "Kismet/KismetMathLibrary.h"

APopulation_Shakespeare::APopulation_Shakespeare() {
	PrimaryActorTick.bCanEverTick = false;

	DefaultComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComp"));
	RootComponent = DefaultComp;

	DNAPool = TEXT(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.");
	OptimalSentence = TEXT("To be or not to be.");
	SentenceLen = OptimalSentence.Len();
	
	TotalPopulation = 200;
	TotalGeneration = 1;
	MutationRate = 0.01f;

	TotalFitnesses = 0;
}

void APopulation_Shakespeare::BeginPlay() {
	Super::BeginPlay();

	DNAs.AddDefaulted(TotalPopulation);
	Fitnesses.AddDefaulted(TotalPopulation);
	RandomizeDNAs();
	CreateNewGeneration();
}

void APopulation_Shakespeare::RandomizeDNAs() {
	for (auto& DNA : DNAs) {
		DNA.Chars = OptimalSentence;
		for (int i = 0; i < SentenceLen; ++i) {
			DNA.Chars[i] = DNAPool[(UKismetMathLibrary::RandomInteger(DNAPool.Len()))];
		}
	}
}

void APopulation_Shakespeare::CalcFitnesses() {
	for (int32 i = 0; i < DNAs.Num(); ++i) {
		FString Sentence = DNAs[i].Chars;
		int32 Count = 0;
		for (int32 j = 0; j < SentenceLen; ++j) {
			if (Sentence[j] == OptimalSentence[j]) {
				++Count;
			}
		}
		Fitnesses[i] = Count;
		TotalFitnesses += Count;
	}
}

FString APopulation_Shakespeare::PickByFitness() {
	while (true) {
		int32 Rand = UKismetMathLibrary::RandomInteger(TotalFitnesses);
		int32 i = UKismetMathLibrary::RandomInteger(TotalPopulation - 1);
		if (Rand < Fitnesses[i]) {
			return DNAs[i].Chars;
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
	CalcFitnesses();

	TArray<FDNA_Shakespeare> NewDNAs;
	NewDNAs.AddDefaulted(TotalPopulation);
	
	for (int i = 0; i < TotalPopulation; ++i) {
		NewDNAs[i].Chars = CrossOver();
		Mutate(NewDNAs[i].Chars);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *NewDNAs[i].Chars);
	}

	DNAs = MoveTemp(NewDNAs);

	UE_LOG(LogTemp, Error, TEXT("%f"), (float)TotalFitnesses / (SentenceLen * TotalPopulation));
	TotalFitnesses = 0;
	++TotalGeneration;
	UE_LOG(LogTemp, Error, TEXT("%d"), TotalGeneration);

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