#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DNA_Shakespeare.h"
#include "Population_Shakespeare.generated.h"

UCLASS()
class ALGOVISUALIZATION_API APopulation_Shakespeare : public AActor {
	GENERATED_BODY()
	
public:	
	APopulation_Shakespeare();

protected:
	virtual void BeginPlay() override;

private:
	void RandomizeDNAs();
	void CalcFitnesses();
	FString PickByFitness();
	FString CrossOver();
	void Mutate(FString& DNA);
	void CreateNewGeneration();
	bool IsOptimal();

private:
	UPROPERTY()
	USceneComponent* DefaultComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	TArray<FDNA_Shakespeare> DNAs;
	FString DNAPool;

	int32 TotalPopulation;
	float MutationRate;
	TArray<int32> Fitnesses;
	int32 TotalFitnesses;
	int32 TotalGeneration;

	FString OptimalSentence;
	int32 SentenceLen;
};
