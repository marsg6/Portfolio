#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DNA_Shakespeare.h"
#include "Population_Shakespeare.generated.h"

//This project is based on the YouTube Video series by "The Coding Tran"
//https://www.youtube.com/watch?v=c8gZguZWYik&list=PLRqwX-V7Uu6bw4n02JP28QDuUdNi3EXxJ 

DECLARE_DYNAMIC_DELEGATE(FGenerationChangedDelegate);
DECLARE_DYNAMIC_DELEGATE(FTargetFoundDelegate);

UCLASS()
class ALGOVISUALIZATION_API APopulation_Shakespeare : public AActor {
	GENERATED_BODY()

public:
	APopulation_Shakespeare();

	FORCEINLINE int32 GetTotalPopulation()		const { return TotalPopulation; }
	FORCEINLINE int32 GetTotalGeneration()		const { return TotalGeneration; }
	FORCEINLINE float GetTotalFitnesses()		const { return static_cast<float>(TotalFitnesses) / (TotalPopulation * PhraseLen) * 100; }
	FORCEINLINE float GetMutationRate()			const { return MutationRate * 100; }

	FORCEINLINE FString GetTargetPhrase()		const { return TargetPhrase; }
	FORCEINLINE FString GetDNAPool()			const { return DNAPool; }

	FORCEINLINE auto GetDNAs()					const { return DNAs; }

	UFUNCTION(BlueprintCallable, Category = "GeneticAlgorithm|Shakespeare|UI")
	void Start();
	UFUNCTION(BlueprintCallable, Category = "GeneticAlgorithm|Shakespeare|UI")
	void End();
	UFUNCTION(BlueprintCallable, Category = "GeneticAlgorithm|Shakespeare|UI")
	void SetTargetPhrase(const FString& NewTargetPhrase);
	UFUNCTION(BlueprintCallable, Category = "GeneticAlgorithm|Shakespeare|UI")
	void SetPhraseLen(int32 NewPhraseLen);

public:
	FGenerationChangedDelegate OnGenerationChanged;
	FTargetFoundDelegate OnTargetFound;

protected:
	virtual void BeginPlay() override;

private:
	void RandomizeDNAs();
	int32 CalcFitness(FString DNA);
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	int32 TotalPopulation;
	int32 TotalGeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	float MutationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	FString TargetPhrase;
	int32 PhraseLen;

	int32 TotalFitnesses;

	/* For widet */
	UPROPERTY()
		TSubclassOf<class UShakespeareWidget> ShakespeareWidgetClass;
};
