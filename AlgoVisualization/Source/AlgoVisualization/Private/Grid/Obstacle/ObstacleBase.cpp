#include "ObstacleBase.h"

#include "Components/StaticMeshComponent.h"

AObstacleBase::AObstacleBase() {
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

	MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
}

void AObstacleBase::BeginPlay() {
	Super::BeginPlay();
	
}