#include "ObjToSort.h"

#include "Components/StaticMeshComponent.h"

#include "ConstructorHelpers.h"

AObjToSort::AObjToSort() {
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMFinder(TEXT("StaticMesh'/Game/Resources/Geometry/Pillar_50x500.Pillar_50x500'"));
	if (SMFinder.Succeeded()) {
		MeshComp->SetStaticMesh(SMFinder.Object);
		RootComponent = MeshComp;
	}
}

void AObjToSort::BeginPlay() {
	Super::BeginPlay();

}

void AObjToSort::SetRandomColor(const float HueVal) {
	MeshComp->SetScalarParameterValueOnMaterials(TEXT("HueVal"), HueVal);
}

void AObjToSort::SetSize(const FVector& Size) {
	MeshComp->SetRelativeScale3D(Size);
}

bool AObjToSort::operator==(const AObjToSort& Other) const	{ return ID == Other.ID; }
bool AObjToSort::operator!=(const AObjToSort& Other) const	{ return !operator==(Other); }
bool AObjToSort::operator<(const AObjToSort& Other)	 const	{ return ID < Other.ID; }
bool AObjToSort::operator<=(const AObjToSort& Other) const	{ return ID <= Other.ID; }
bool AObjToSort::operator>(const AObjToSort& Other)	 const	{ return !operator<=(Other); }
bool AObjToSort::operator>=(const AObjToSort& Other) const	{ return !operator<(Other); }
