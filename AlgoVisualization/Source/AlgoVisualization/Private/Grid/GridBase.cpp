#include "GridBase.h"

#include "Components/SceneComponent.h"

#include "Kismet/KismetSystemLibrary.h"

AGridBase::AGridBase() {
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComp;

	GridLoc = { 0.0f, 0.0f, 0.0f };
	GridSize = { 500.0f, 500.0f };
	GridBoxColor = FLinearColor::Blue;
	TileSize = 50.0f;
}

void AGridBase::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	GridLoc = SceneComp->GetComponentLocation();

	UKismetSystemLibrary::FlushPersistentDebugLines(this);
	UKismetSystemLibrary::DrawDebugBox(this, GridLoc, FVector(GridSize, 5.0f), GridBoxColor, FRotator::ZeroRotator, 10000.0f, 10.0f);
	UKismetSystemLibrary::DrawDebugBox(this, GetGridBottomLeft(), FVector(5.0f), FLinearColor::Red, FRotator::ZeroRotator, 10000.0f, 10.0f);
	DrawTiles();
}

void AGridBase::BeginPlay() {
	Super::BeginPlay();
	
}

FVector AGridBase::GetGridBottomLeft() const {
	return (GridLoc - SceneComp->GetRightVector() * GridSize.Y) - (SceneComp->GetForwardVector() * GridSize.X);
}

void AGridBase::GetGridTileNumber(int32& OutTileNumX, int32& OutTileNumY) {
	FVector2D Res = GridSize / TileSize;
	OutTileNumX = Res.X - 1;
	OutTileNumY = Res.Y - 1;
}

void AGridBase::DrawTiles() {
	GetGridTileNumber(TileNumX, TileNumY);

	for (int32 X = 0; X <= TileNumX; ++X) {
		for (int32 Y = 0; Y <= TileNumY; ++Y) {

			FVector TilePos = GetGridBottomLeft() + (SceneComp->GetRightVector() * (Y * TileSize * 2 + TileSize)) + (SceneComp->GetForwardVector() * (X * TileSize * 2 + TileSize));

			FHitResult NormalHitResult;
			FHitResult ObstacleHitResult;
			TArray<AActor*> ActorsToIgnore;

			float TileSizeMinus = 5.0f;
			if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::Type::None, NormalHitResult, true)) {
				UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, TilePos.Z), TilePos, TileSize - TileSizeMinus, FLinearColor::Yellow, 10000.0f);
			}
			if (UKismetSystemLibrary::SphereTraceSingle(this, TilePos, TilePos + FVector(0.01f), TileSize - TileSizeMinus, ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::Type::None, ObstacleHitResult, true)) {
				UKismetSystemLibrary::DrawDebugPlane(this, FPlane(0.0f, 0.0f, 1.0f, TilePos.Z), TilePos, TileSize - TileSizeMinus, FLinearColor::Red, 10000.0f);
			}
		}
	}
}