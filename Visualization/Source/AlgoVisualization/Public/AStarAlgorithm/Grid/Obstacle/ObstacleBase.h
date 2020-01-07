#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UENUM(BlueprintType)
enum class EGroundType : uint8 {
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

	FORCEINLINE EGroundType GetObstacleType() const { return ObstacleType; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (AllowPrivateAccess = true))
	EGroundType ObstacleType;
};
