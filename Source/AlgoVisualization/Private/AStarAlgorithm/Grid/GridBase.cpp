#include "GridBase.h"
#include "TileBase.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AGridBase::AGridBase() {
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComp;

	GridLoc = { 0.0f, 0.0f, 0.0f };
	GridSize = { 500.0f, 500.0f };
	TileSize = 50.0f;
	TimeInterval = 0.2f;
}

void AGridBase::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	GridLoc = SceneComp->GetComponentLocation();
	TileSizeMinus = TileSize / 10.0f;

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
	TileInfos.Empty();

	UE_LOG(LogTemp, Error, TEXT("%d"), TileInfos.Num());
	for (int32 X = 0; X <= TileNumX; ++X) {
		for (int32 Y = 0; Y <= TileNumY; ++Y) {
			FVector TilePos = GetGridBottomLeft() + (SceneComp->GetRightVector() * (Y * TileSize * 2 + TileSize)) + (SceneComp->GetForwardVector() * (X * TileSize * 2 + TileSize));
			FHitResult NormalHitResult;
			FHitResult ObstacleHitResult;
			TArray<AActor*> ActorsToIgnore;

			FVector2D Coord(X, Y);
			FTileData TileData(EGroundType::None, TilePos, Coord, GetTileCost(EGroundType::None));

			if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::Type::None, NormalHitResult, true)) {
				if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::Type::None, ObstacleHitResult, true)) {
					if (ObstacleHitResult.Actor.IsValid()) {
						AObstacleBase* Obstacle = Cast<AObstacleBase>(ObstacleHitResult.Actor);
						if (Obstacle) {
							TileData.GroundType = Obstacle->GetObstacleType();
							TileData.TileCost = GetTileCost(Obstacle->GetObstacleType());
							TileInfos.Add(Coord, TileData);
						}
					}
				}
				else {
					TileData.GroundType = EGroundType::Normal;
					TileData.TileCost = GetTileCost(EGroundType::Normal);
					TileInfos.Add(Coord, TileData);
				}
			}
			else {
				TileInfos.Add(Coord, TileData);
			}
		}
	}
	UE_LOG(LogTemp, Error, TEXT("%d"), TileInfos.Num());
}

void AGridBase::SpawnTiles(bool bSpawnNoneTile) {
	UWorld* World = GetWorld();
	if (World) {
		for (auto& TileInfo : TileInfos) {
			if (bSpawnNoneTile || TileInfo.Value.GroundType != EGroundType::None) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ATileBase* TileBase = World->SpawnActor<ATileBase>(ATileBase::StaticClass(), TileInfo.Value.TilePos, FRotator::ZeroRotator, SpawnParams);

				if (TileBase) {
					TileBase->GridCoord = TileInfo.Value.GridCoord;
					TileBase->Grid = this;
					TileInfo.Value.Tile = TileBase;
				}
			}
		}
	}
}

void AGridBase::NewTileSelected(ATileBase* Tile) {
	if (Tile) {
		/* It is New One */
		if (Tile->Selected()) {
			/* If Previous One Exsits */
			if (SelectedTile) {
				SetTilesDefault();

				SelectedTile->DeselectTile();
			}
			/* No Previous One */
			else {

			}
			SelectedTile = Tile;
		}
		/* It is the Same One */
		else {
			SetTilesDefault();

			SelectedTile = nullptr;
		}
	}
}

void AGridBase::NewTileOvered(ATileBase* Tile) {

	if (OveredTile) {
		OveredTile->EndOverTile();
	}
	OveredTile = Tile;

	SetTilesDefault();

	if (SelectedTile && OveredTile) {
		FindPathToTarget(SelectedTile->GridCoord, OveredTile->GridCoord);
	}
}

int32 AGridBase::GetTileCost(EGroundType Type) const {
	int32 Cost = 0;
	switch (Type) {
	case EGroundType::Normal:			Cost = 1;	break;
	case EGroundType::Difficult:		Cost = 2;	break;
	case EGroundType::ReallyDifficult:	Cost = 5;	break;
	case EGroundType::Impossible:		Cost = 999; break;
	case EGroundType::None:				Cost = 999; break;
	}
	return Cost;
}

TArray<FVector2D> AGridBase::GetNeighborTiles(FVector2D Tile) {
	TArray<FVector2D> NeighborTiles;
	TArray<FVector2D> PossibleTiles = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	for (auto PossibleTile : PossibleTiles) {
		auto TileInfo = TileInfos.Find(Tile + PossibleTile);
		if (TileInfo) {
			auto Type = TileInfo->GroundType;
			if (Type != EGroundType::None && Type != EGroundType::Impossible) {
				NeighborTiles.AddUnique(Tile + PossibleTile);
			}
		}
	}
	return NeighborTiles;
}

int32 AGridBase::GetEstimatedCostToTarget(FVector2D CurrentTile, FVector2D TargetTile) {
	FVector2D Diff = CurrentTile - TargetTile;
	return FMath::RoundToInt(FMath::Abs(Diff.X) + FMath::Abs(Diff.Y));
}

void AGridBase::FindPathToTarget(FVector2D StartTile, FVector2D TargetTile) {
	auto TargetTileInfo = TileInfos.Find(TargetTile);

	auto Type = TargetTileInfo->GroundType;
	if (TargetTileInfo && Type != EGroundType::None && Type != EGroundType::Impossible) {
		/* Set Default Values*/
		SetTilesDefault();

		TargetTileInfo = TileInfos.Find(StartTile);
		if (TargetTileInfo) {
			AddTileInfo(*TargetTileInfo, { 0 ,0 }, 0, GetEstimatedCostToTarget(StartTile, TargetTile), GetEstimatedCostToTarget(StartTile, TargetTile));
		}

		/* Find Path Start */

		TArray<FVector2D> OpenList;
		TArray<FVector2D> ClosedList;
		FVector2D CurrentTile = StartTile;
		OpenList.AddUnique(CurrentTile);
		FVector2D CheapestTarget;

		/* One by One */
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUFunction(this, FName(TEXT("FindPath")), StartTile, TargetTile, OpenList, ClosedList, CurrentTile, CheapestTarget), TimeInterval, false);
	}
}

void AGridBase::FindPath(FVector2D StartTile, FVector2D TargetTile, TArray<FVector2D>& OpenList, TArray<FVector2D>& ClosedList, FVector2D& CurrentTile, FVector2D& CheapestTarget) {
	if (0 < OpenList.Num()) {
		CheapestTarget = OpenList[0];

		for (auto TargetToCompare : OpenList) {

			auto InfoToCompare = TileInfos.Find(TargetToCompare);
			auto CurrentTargetInfo = TileInfos.Find(CheapestTarget);

			if (InfoToCompare->TotalCost < CurrentTargetInfo->TotalCost) {
				CheapestTarget = TargetToCompare;
			}
			else if (InfoToCompare->TotalCost == CurrentTargetInfo->TotalCost) {
				if (InfoToCompare->CostFromStart < CurrentTargetInfo->CostFromStart) {
					CheapestTarget = TargetToCompare;
				}
				else if (InfoToCompare->CostFromStart == CurrentTargetInfo->CostFromStart) {
					if (InfoToCompare->EstimatedCostToTarget < CurrentTargetInfo->EstimatedCostToTarget) {
						CheapestTarget = TargetToCompare;
					}
				}
			}
		}

		CurrentTile = CheapestTarget;
		OpenList.Remove(CurrentTile);
		ClosedList.AddUnique(CurrentTile);
		TileInfos.Find(CurrentTile)->Tile.Get()->SetClosedListed(true);
		
		if (CurrentTile == TargetTile) {
			RetracePath(TargetTile, StartTile, Paths);

			for (auto Path : Paths) {
				TileInfos.Find(Path)->Tile.Get()->SetInPath(true);
			}

			return;
		}

		else {
			int32 CurrentNeighborCostFromStart;
			for (auto NeighborTile : GetNeighborTiles(CurrentTile)) {
				if (!ClosedList.Contains(NeighborTile)) {
					auto CurrentInfo = TileInfos.Find(CurrentTile);
					auto CurrentNeighborInfo = TileInfos.Find(NeighborTile);

					if (CurrentNeighborInfo) {
						CurrentNeighborCostFromStart = CurrentInfo->CostFromStart + CurrentNeighborInfo->TileCost;

						if (!OpenList.Contains(NeighborTile)) {
							OpenList.AddUnique(NeighborTile);
							TileInfos.Find(NeighborTile)->Tile.Get()->SetOpenListed(true);
							AddTileInfo(*CurrentNeighborInfo, CurrentTile, CurrentNeighborCostFromStart, GetEstimatedCostToTarget(NeighborTile, TargetTile));
						}
						else {
							if (CurrentNeighborCostFromStart < CurrentNeighborInfo->CostFromStart) {
								AddTileInfo(*CurrentNeighborInfo, CurrentTile, CurrentNeighborCostFromStart, GetEstimatedCostToTarget(NeighborTile, TargetTile));
							}
						}

						if (NeighborTile == TargetTile) {
							RetracePath(TargetTile, StartTile, Paths);

							for (auto Path : Paths) {
								TileInfos.Find(Path)->Tile.Get()->SetInPath(true);
							}

							return;
						}
					}
				}
			}
		}
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUFunction(this, FName(TEXT("FindPath")), StartTile, TargetTile, OpenList, ClosedList, CurrentTile, CheapestTarget), TimeInterval, false);
	}
}

void AGridBase::AddTileInfo(FTileData& TileInfo, FVector2D PrevTile, int32 CostFromStart, int32 EstimatedCost, int32 TotalCost) {
	TileInfo.PrevTile = PrevTile;
	TileInfo.CostFromStart = CostFromStart;
	TileInfo.EstimatedCostToTarget = EstimatedCost;
	TileInfo.TotalCost = (TotalCost == -1 ? CostFromStart + EstimatedCost : TotalCost);
}

void AGridBase::RetracePath(FVector2D TargetTile, FVector2D StartTile, TArray<FVector2D>& OutPaths) {
	OutPaths.Empty();
	FVector2D CurrentTile = TargetTile;
	TArray<FVector2D> InvertedPath;
	InvertedPath.AddUnique(StartTile);

	while (CurrentTile != StartTile) {
		InvertedPath.AddUnique(CurrentTile);
		CurrentTile = TileInfos.Find(CurrentTile)->PrevTile;
	}

	for (int32 Index = InvertedPath.Num() - 1; 0 <= Index; --Index) {
		OutPaths.AddUnique(InvertedPath[Index]);
	}
}

void AGridBase::SetTilesDefault() {
	GetWorldTimerManager().ClearTimer(TimerHandle);

	for (auto& TileInfo : TileInfos) {
		auto CurrentInfo = TileInfos.Find(TileInfo.Key);
		auto CurrentTile = CurrentInfo->Tile.Get();

		if (CurrentTile) {
			AddTileInfo(*CurrentInfo, { 0, 0 }, 999, 999, 999);
			CurrentTile->Initalize();
		}
	}
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