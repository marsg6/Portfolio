#include "TileBase.h"
#include "GridBase.h"

#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ATileBase::ATileBase() {
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Resources/GridTile/SM_GridTile_01.SM_GridTile_01'"));
	if (MeshFinder.Succeeded()) {
		MeshComp->SetStaticMesh(MeshFinder.Object);
		MeshComp->OnBeginCursorOver.AddDynamic(this, &ATileBase::MeshBeginCursorOver);
		MeshComp->OnEndCursorOver.AddDynamic(this, &ATileBase::MeshEndCursorOver);
	}
	RootComponent = MeshComp;

	bIsSelected = false;
}

void ATileBase::BeginPlay() {
	Super::BeginPlay();
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = TEXT("SetTileColor");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, 0.2f, LatentInfo);
}

FTileData* ATileBase::GetTileData() {
	if (Grid) {
		return Grid->GetTileInfos().Find(GridCoord);
	}
	return nullptr;
}

void ATileBase::SetTileColor() {
	FLinearColor TileColor;
	auto TileData = GetTileData();

	if (TileData) {
		switch (TileData->GroundType) {
		case EGroundType::Normal:			TileColor = FLinearColor::White;	break;
		case EGroundType::Difficult:		TileColor = FLinearColor::Gray;		break;
		case EGroundType::ReallyDifficult:	TileColor = FLinearColor::Yellow;	break;
		case EGroundType::Impossible:		TileColor = FLinearColor::Red;		break;
		case EGroundType::None:				TileColor = FLinearColor::Blue;		break;
		default: break;
		}

		if (bIsSelected) {
			TileColor *= 3;
		}

		if (MeshComp) {
			MeshComp->SetVectorParameterValueOnMaterials(TEXT("TileColor"), UKismetMathLibrary::Conv_LinearColorToVector(TileColor));
		}
	}
}

void ATileBase::MeshBeginCursorOver(UPrimitiveComponent* TouchedComponent) {
	bIsSelected = true;
	SetTileColor();
}

void ATileBase::MeshEndCursorOver(UPrimitiveComponent* TouchedComponent) {
	bIsSelected = false;
	SetTileColor();
}