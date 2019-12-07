// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObstacleBase.h"
#include "GridBase.generated.h"

USTRUCT(BlueprintType)
struct FTileData {
	GENERATED_BODY()

	FTileData() = default;
	FTileData(EGroundType Type, FVector Pos, FVector2D Coord) : GroundType(Type), TilePos(Pos), GridCoord(Coord) {}

	EGroundType GroundType;
	FVector TilePos;
	FVector2D GridCoord;
};

UCLASS()
class ALGOVISUALIZATION_API AGridBase : public AActor {
	GENERATED_BODY()
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	AGridBase();

	FORCEINLINE TMap<FVector2D, FTileData> GetTileInfos() { return TileInfos; }

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
	
	/* Debug Funtion */
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void DrawPlane(FVector Pos, EGroundType Type);
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	TMap<FVector2D, FTileData> TileInfos;
};
