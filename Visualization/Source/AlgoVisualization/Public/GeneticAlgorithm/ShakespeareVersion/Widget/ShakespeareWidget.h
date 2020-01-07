#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShakespeareWidget.generated.h"

UCLASS()
class ALGOVISUALIZATION_API UShakespeareWidget : public UUserWidget {
	GENERATED_BODY()
	
private:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTotalPopulation();

private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* SortName;
};
