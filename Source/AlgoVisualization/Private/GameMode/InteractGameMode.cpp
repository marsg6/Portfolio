#include "InteractGameMode.h"
#include "InteractPlayerController.h"

AInteractGameMode::AInteractGameMode() {
	PlayerControllerClass = AInteractPlayerController::StaticClass();
}