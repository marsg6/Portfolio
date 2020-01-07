#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System_Shakespeare.generated.h"

//This project is based on the YouTube Video series by "The Coding Tran"
//https://www.youtube.com/watch?v=c8gZguZWYik&list=PLRqwX-V7Uu6bw4n02JP28QDuUdNi3EXxJ 

UCLASS()
class ALGOVISUALIZATION_API ASystem_Shakespeare : public AActor {
	GENERATED_BODY()
	
public:	
	ASystem_Shakespeare();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	USceneComponent* DefaultComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	int32 TotalPopulation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Target", Meta = (AllowPrivateAccess = true))
	FString OptimalSentence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	float MutationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneticAlgorithm|Shakespeare|Population", Meta = (AllowPrivateAccess = true))
	class APopulation_Shakespeare* Population;
};
