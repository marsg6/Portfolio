#include "InteractPlayerController.h"

#include "GameFramework/Pawn.h"

AInteractPlayerController::AInteractPlayerController() {
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void AInteractPlayerController::BeginPlay() {
	Super::BeginPlay();

	GetPawn()->SetHidden(true);
}