// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.generated.h"

UCLASS()
class ALGOVISUALIZATION_API AGridBase : public AActor {
	GENERATED_BODY()
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	AGridBase();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	FVector GetGridBottomLeft() const;
	UFUNCTION(BlueprintCallable, Category = Grid, Meta = (AllowPrivateAccess = true))
	void GetGridTileNumber(int32& OutTileNumX, int32& OutTileNumY);
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
	FLinearColor GridBoxColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid, Meta = (AllowPrivateAccess = true))
	float TileSize;
	int32 TileNumX;
	int32 TileNumY;
};
