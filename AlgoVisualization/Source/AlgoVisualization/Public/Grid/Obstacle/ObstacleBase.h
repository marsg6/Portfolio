#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UENUM(BlueprintType)
enum class EObstacleType : uint8 {
	Normal,
	Difficult,
	ReallyDifficult,
	Impossible,
	None,
};

UCLASS()
class ALGOVISUALIZATION_API AObstacleBase : public AActor {
	GENERATED_BODY()
	
public:	
	AObstacleBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (AllowPrivateAccess = true))
	EObstacleType ObstacleType;
};
