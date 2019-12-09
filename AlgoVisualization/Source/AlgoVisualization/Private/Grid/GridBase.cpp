#include "GridBase.h"
#include "TileBase.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Chaos/Pair.h"

AGridBase::AGridBase() {
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComp;

	GridLoc = { 0.0f, 0.0f, 0.0f };
	GridSize = { 500.0f, 500.0f };
	TileSize = 50.0f;
	TileSizeMinus = 5.0f;
}

void AGridBase::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	GridLoc = SceneComp->GetComponentLocation();

	UKismetSystemLibrary::FlushPersistentDebugLines(this);
	UKismetSystemLibrary::DrawDebugBox(this, GridLoc, FVector(GridSize, 5.0f), FLinearColor::Blue, FRotator::ZeroRotator, 10000.0f, 10.0f);
	UKismetSystemLibrary::DrawDebugBox(this, GetGridBottomLeft(), FVector(5.0f), FLinearColor::Red, FRotator::ZeroRotator, 10000.0f, 10.0f);
	GenerateMapData();
	DrawTiles();
}

void AGridBase::BeginPlay() {
	Super::BeginPlay();
	
	GridLoc = SceneComp->GetComponentLocation();
	UKismetSystemLibrary::FlushPersistentDebugLines(this);

	GenerateMapData();
	SpawnTiles(false);
}

FVector AGridBase::GetGridBottomLeft() const {
	return (GridLoc - SceneComp->GetRightVector() * GridSize.Y) - (SceneComp->GetForwardVector() * GridSize.X);
}

void AGridBase::GetGridTileNumber(int32& OutTileNumX, int32& OutTileNumY) {
	FVector2D Res = GridSize / TileSize;
	OutTileNumX = Res.X - 1;
	OutTileNumY = Res.Y - 1;
}

void AGridBase::GenerateMapData() {
	GetGridTileNumber(TileNumX, TileNumY);

	for (int32 X = 0; X <= TileNumX; ++X) {
		for (int32 Y = 0; Y <= TileNumY; ++Y) {
			FVector TilePos = GetGridBottomLeft() + (SceneComp->GetRightVector() * (Y * TileSize * 2 + TileSize)) + (SceneComp->GetForwardVector() * (X * TileSize * 2 + TileSize));

			FHitResult NormalHitResult;
			FHitResult ObstacleHitResult;
			TArray<AActor*> ActorsToIgnore;

			FVector2D Coord(X, Y);
			FTileData TileData(EGroundType::None, TilePos, Coord);

			if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::Type::None, NormalHitResult, true)) {
				if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::Type::None, ObstacleHitResult, true)) {
					if (ObstacleHitResult.Actor.IsValid()) {
						AObstacleBase* Obstacle = Cast<AObstacleBase>(ObstacleHitResult.Actor);
						if (Obstacle) {
							TileData.GroundType = Obstacle->GetObstacleType();
							TileInfos.Add(Coord, TileData);
						}
					}
				}
				else {
					TileData.GroundType = EGroundType::Normal;
					TileInfos.Add(Coord, TileData);
				}
			}
			else {
				TileInfos.Add(Coord, TileData);
			}
		}
	}
}

void AGridBase::SpawnTiles(bool bSpawnNoneTile) {
	UWorld* World = GetWorld();
	if (World) {
		for (auto TileInfo : TileInfos) {
			if (bSpawnNoneTile || TileInfo.Value.GroundType != EGroundType::None) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ATileBase* TileBase = World->SpawnActor<ATileBase>(ATileBase::StaticClass(), TileInfo.Value.TilePos, FRotator::ZeroRotator, SpawnParams);

				TileBase->GridCoord = TileInfo.Value.GridCoord;
				TileBase->Grid = this;
			}
		}
	}
}

void AGridBase::NewTileSelected(ATileBase* Tile) {
	if (SelectedTile) {
		SelectedTile->DeselectTile();
	}
	SelectedTile = Tile;
}

void AGridBase::NewTileOvered(ATileBase* Tile) {
	if (OveredTile) {
		OveredTile->EndOverTile();
	}
	OveredTile = Tile;
}

/* Debug Function */

void AGridBase::DrawPlane(FVector Pos, EGroundType Type) {
	switch (Type) {
	case EGroundType::Normal:				UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, Pos.Z), Pos, TileSize - TileSizeMinus, FLinearColor::White, 10000.0f); break;
	case EGroundType::Difficult:			UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, Pos.Z), Pos, TileSize - TileSizeMinus, FLinearColor::Gray, 10000.0f); break;
	case EGroundType::ReallyDifficult:		UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, Pos.Z), Pos, TileSize - TileSizeMinus, FLinearColor::Yellow, 10000.0f); break;
	case EGroundType::Impossible:			UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, Pos.Z), Pos, TileSize - TileSizeMinus, FLinearColor::Red, 10000.0f); break;
	case EGroundType::None: break;
	default: break;
	}
}

void AGridBase::DrawTiles() {
	for (auto TileInfo : TileInfos) {
		DrawPlane(TileInfo.Value.TilePos, TileInfo.Value.GroundType);
	}
}