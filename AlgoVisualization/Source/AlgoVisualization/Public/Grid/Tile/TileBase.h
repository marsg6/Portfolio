#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

UCLASS()
class ALGOVISUALIZATION_API ATileBase : public AActor {
	GENERATED_BODY()
	
public:	
	ATileBase();

	void EndOverTile();
	void DeselectTile();

protected:
	virtual void BeginPlay() override;

private:
	void CustomInit();
	void SetTileColor();
	void SetTileSize();
	auto GetTileData();

	UFUNCTION()
	void MeshBeginCursorOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void MeshEndCursorOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void MeshClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void BeginOverTile();
	void SelectTile();

public:
	FVector2D GridCoord;
	UPROPERTY()
	class AGridBase* Grid;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
	class UWidgetComponent* WidgetComp;

	FTimerHandle InitTimer;
	bool bIsOvered;
	bool bIsSelected;
};
