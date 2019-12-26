// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObstacleBase.h"
#include "GridBase.generated.h"

USTRUCT(BlueprintType)
struct FTileData {
	GENERATED_BODY()

	FTileData() = default;
	FTileData(EGroundType Type, FVector Pos, FVector2D Coord, int32 TileCost)
		: GroundType(Type), TilePos(Pos), GridCoord(Coord), TileCost (TileCost) {}

	TWeakObjectPtr<class ATileBase> Tile;
	EGroundType GroundType;
	FVector TilePos;
	FVector2D GridCoord;
	int32 TileCost = 0;
	int32 CostFromStart = 0;
	int32 EstimatedCostToTarget = 0;
	int32 TotalCost = 0;
	FVector2D PrevTile = { 0, 0 };
};

UCLASS()
class ALGOVISUALIZATION_API AGridBase : public AActor {
	GENERATED_BODY()
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	AGridBase();

	FORCEINLINE TMap<FVector2D, FTileData> GetTileInfos() const { return TileInfos; }
	FORCEINLINE float GetTileSize() const { return TileSize; }

	void NewTileSelected(class ATileBase* Tile);
	void NewTileOvered(class ATileBase* Tile);

	int32 GetTileCost(EGroundType Type) const;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	FVector GetGridBottomLeft() const;
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void GetGridTileNumber(int32& OutTileNumX, int32& OutTileNumY);
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void GenerateMapData();
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void SpawnTiles(bool bSpawnNoneTile);
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	TArray<FVector2D> GetNeighborTiles(FVector2D Tile);
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	int32 GetEstimatedCostToTarget(FVector2D CurrentTile, FVector2D TargetTile);
	UFUNCTION(BlueprintCallable, Category = Path, Meta = (AllowPrivateAccess = true))
	void FindPathToTarget(FVector2D StartTile, FVector2D TargetTile);
	UFUNCTION(BlueprintCallable, Category = Path, Meta = (AllowPrivateAccess = true))
	void FindPath(FVector2D StartTile, FVector2D TargetTile, TArray<FVector2D>& OpenList, TArray<FVector2D>& ClosedList, FVector2D& CurrentTile, FVector2D& CheapestTarget);
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void AddTileInfo(FTileData& TileInfo, FVector2D PrevTile, int32 CostFromStart, int32 EstimatedCost, int32 TotalCost = -1/* Default */);
	UFUNCTION(BlueprintCallable, Category = Path, Meta = (AllowPrivateAccess = true))
	void RetracePath(FVector2D TargetTile, FVector2D StartTile, TArray<FVector2D>& OutPaths);
	UFUNCTION(BlueprintCallable, Category = Path, Meta = (AllowPrivateAccess = true))
	void SetTilesDefault();

	/* Debug Funtion */
	UFUNCTION(BlueprintCallable, Category = Debug, Meta = (AllowPrivateAccess = true))
	void DrawPlane(FVector Pos, EGroundType Type);
	UFUNCTION(BlueprintCallable, Category = Debug, Meta = (AllowPrivateAccess = true))
	void DrawTiles();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	USceneComponent* SceneComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	FVector GridLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	FVector2D GridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	float TileSize;
	float TileSizeMinus;
	int32 TileNumX;
	int32 TileNumY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	TMap<FVector2D, FTileData> TileInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, Meta = (AllowPrivateAccess = true))
	class ATileBase* SelectedTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, Meta = (AllowPrivateAccess = true))
	class ATileBase* OveredTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Path, Meta = (AllowPrivateAccess = true))
	TArray<FVector2D> Paths;

	/* Debug parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, Meta = (AllowPrivateAccess = true))
	float TimeInterval;
	FTimerHandle TimerHandle;
};
