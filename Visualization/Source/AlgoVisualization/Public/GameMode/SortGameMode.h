#pragma once

#include "CoreMinimal.h"
#include "GameMode/InteractGameMode.h"
#include "SortGameMode.generated.h"

UCLASS()
class ALGOVISUALIZATION_API ASortGameMode : public AInteractGameMode {
	GENERATED_BODY()
	
public:
	ASortGameMode();

protected:
	virtual void BeginPlay() override;
};
