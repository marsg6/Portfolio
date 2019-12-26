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
	FORCEINLINE bool Selected() const { return bIsSelected; }
	void SetInPath(bool bIsInPath);
	void SetOpenListed(bool Listed);
	void SetClosedListed(bool Listed);
	void Initalize();
	
protected:
	virtual void BeginPlay() override;

private:
	void CustomInit();
	void SetTileColor();
	void SetTileSize();
	auto GetTileData() const;

	UFUNCTION()
	void MeshBeginCursorOver(UPrimitiveComponent* TouchedComponent);
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
	bool bOpenListed;
	bool bClosedListed;
	bool bInPath;
};
