#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjToSort.generated.h"

UCLASS()
class ALGOVISUALIZATION_API AObjToSort : public AActor {
	GENERATED_BODY()
	
public:	
	AObjToSort();

	bool operator==(const AObjToSort& Other) const;
	bool operator!=(const AObjToSort& Other) const;
	bool operator<(const AObjToSort& Other)  const;
	bool operator<=(const AObjToSort& Other) const;
	bool operator>(const AObjToSort& Other)  const;
	bool operator>=(const AObjToSort& Other) const;

	void SetRandomColor(const float HueVal);
	void SetSize(const FVector& Size);
	FORCEINLINE void SetID(int32 NewID) { ID = NewID; }
	FORCEINLINE int32 GetID() const { return ID; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sort|SortObj", Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sort|SortObj|ID", Meta = (AllowPrivateAccess = true))
	int32 ID;
};
