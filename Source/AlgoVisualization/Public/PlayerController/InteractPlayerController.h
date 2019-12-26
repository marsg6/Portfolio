#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InteractPlayerController.generated.h"

UCLASS()
class ALGOVISUALIZATION_API AInteractPlayerController : public APlayerController {
	GENERATED_BODY()
	
public:
	AInteractPlayerController();

protected:
	virtual void BeginPlay() override;
};
