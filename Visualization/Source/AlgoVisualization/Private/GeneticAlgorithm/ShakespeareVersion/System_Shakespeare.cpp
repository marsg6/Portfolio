#include "System_Shakespeare.h"
#include "Population_Shakespeare.h"

#include "Components/TextRenderComponent.h"

#include "Engine/World.h"

ASystem_Shakespeare::ASystem_Shakespeare() {
	PrimaryActorTick.bCanEverTick = true;

	DefaultComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComp"));
	RootComponent = DefaultComp;

	TotalPopulation = 400;
	OptimalSentence = TEXT("To be or not to be, that is the question.");
	MutationRate = 0.02f;
}

void ASystem_Shakespeare::BeginPlay() {
	Super::BeginPlay();
}

void ASystem_Shakespeare::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}