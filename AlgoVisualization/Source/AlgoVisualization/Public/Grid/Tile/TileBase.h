#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

UCLASS()
class ALGOVISUALIZATION_API ATileBase : public AActor {
	GENERATED_BODY()
	
public:	
	ATileBase();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SetTileColor();
	struct FTileData* GetTileData();

	UFUNCTION()
	void MeshBeginCursorOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void MeshEndCursorOver(UPrimitiveComponent* TouchedComponent);

public:
	FVector2D GridCoord;
	UPROPERTY()
	class AGridBase* Grid;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComp;

	bool bIsSelected;
};
