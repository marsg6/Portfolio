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
	UFUNCTION(BlueprintPure)
	FText SetDNAPool();

	UFUNCTION(BlueprintPure)
	FText SetTotalPopulation();
	UFUNCTION(BlueprintPure)
	FText SetTotalGeneration();
	UFUNCTION(BlueprintPure)
	FText SetTotalFitnesses();
	UFUNCTION(BlueprintPure)
	FText SetMutationRate();

	UFUNCTION()
	void ChangeGeneration();

	UFUNCTION()
	void Start();
	UFUNCTION()
	void End();

	UFUNCTION()
	void TargetChanged();
	UFUNCTION()
	void TargetCommitted();

	UFUNCTION()
	void TargetFound();

	void ActivateUIs(bool bActivate);

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
	class UButton* StartButton;
	UPROPERTY(Meta = (BindWidget))
	class UButton* EndButton;

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* PopulationList;

	bool bOnDoing;
	bool bTargetChanged;
};
