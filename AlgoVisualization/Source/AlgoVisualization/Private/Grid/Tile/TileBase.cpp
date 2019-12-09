#include "TileBase.h"
#include "GridBase.h"

#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "TimerManager.h"

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
		MeshComp->OnClicked.AddDynamic(this, &ATileBase::MeshClicked);
	}
	RootComponent = MeshComp;

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("WidgetBlueprint'/Game/Blueprints/Grid/Tile/Widget/TileWidget_BP.TileWidget_BP_C'"));
	if (WidgetFinder.Succeeded()) {
		WidgetComp->SetWidgetClass(WidgetFinder.Class);
		WidgetComp->SetWindowFocusable(false);
		WidgetComp->SetGenerateOverlapEvents(false);
		WidgetComp->SetCollisionProfileName(TEXT("NoCollision"));
		WidgetComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	}

	bIsOvered = false;
	bIsSelected = false;
}

void ATileBase::BeginPlay() {
	Super::BeginPlay();

	/* BlueprintInternalUseOnly can't and shouldn't be used.
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = TEXT("SetTileColor");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, 0.2f, LatentInfo);
	*/

	/* Use Timer for a latent action */
	GetWorldTimerManager().SetTimer(InitTimer, this, &ATileBase::CustomInit, 0.2f, true);
}

void ATileBase::CustomInit() {
	SetTileColor();
	SetTileSize();

	GetWorldTimerManager().ClearTimer(InitTimer);
}

auto ATileBase::GetTileData() {
	return Grid->GetTileInfos().Find(GridCoord);
}

void ATileBase::SetTileColor() {
	FLinearColor TileColor;

	switch (GetTileData()->GroundType) {
	case EGroundType::Normal:			TileColor = FLinearColor::White;	break;
	case EGroundType::Difficult:		TileColor = FLinearColor::Gray;		break;
	case EGroundType::ReallyDifficult:	TileColor = FLinearColor::Yellow;	break;
	case EGroundType::Impossible:		TileColor = FLinearColor::Red;		break;
	case EGroundType::None:				TileColor = FLinearColor::Blue;		break;
	default: break;
	}

	if (bIsOvered) {
		TileColor *= 3;
	}
	MeshComp->SetScalarParameterValueOnMaterials(TEXT("bIsSelected"), static_cast<float>(bIsSelected));
	MeshComp->SetVectorParameterValueOnMaterials(TEXT("TileColor"), UKismetMathLibrary::Conv_LinearColorToVector(TileColor));
}

void ATileBase::SetTileSize() {
	FVector Size = MeshComp->GetComponentScale() * Grid->GetTileSize() / 50.0f;
	MeshComp->SetWorldScale3D({ Size.X, Size.Y, 1.0f });
}

void ATileBase::MeshBeginCursorOver(UPrimitiveComponent* TouchedComponent) {
	BeginOverTile();

	Grid->NewTileOvered(this);
}

void ATileBase::MeshEndCursorOver(UPrimitiveComponent* TouchedComponent) {

}

void ATileBase::BeginOverTile() {
	bIsOvered = true;
	SetTileColor();
}

void ATileBase::EndOverTile() {
	bIsOvered = false;
	SetTileColor();
}

void ATileBase::MeshClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) {
	SelectTile();

	Grid->NewTileSelected(this);
}

void ATileBase::SelectTile() {
	bIsSelected = true;
	SetTileColor();
}

void ATileBase::DeselectTile() {
	bIsSelected = false;
	SetTileColor();
}