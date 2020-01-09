#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileWidget.generated.h"

UCLASS()
class ALGOVISUALIZATION_API UTileWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void CustomInit();

private:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetCurrentCost();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTileCost();

public:
	UPROPERTY()
	class AGridBase* Grid;
	FVector2D GridCoord;

private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CostFromStart;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TileCost;
};
