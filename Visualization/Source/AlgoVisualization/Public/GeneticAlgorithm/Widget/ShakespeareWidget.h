#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShakespeareWidget.generated.h"

UCLASS()
class ALGOVISUALIZATION_API UShakespeareWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	void InitWidget(class APopulation_Shakespeare* NewPopulation);

private:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetDNAPool();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTotalPopulation();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTotalGeneration();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTotalFitnesses();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetMutationRate();

	UFUNCTION()
	void ChangeGeneration();

private:
	UPROPERTY()
	class APopulation_Shakespeare* Population;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* TargetPhrase;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* DNAPool;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TotalPopulation;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TotalGeneration;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TotalFitnesses;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* MutationRate;

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* PopulationList;
};
