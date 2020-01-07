#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sorter.generated.h"

//This project is inspired by the YouTube Videos by "Timo Bingmann" and "w0rthy"
//https://www.youtube.com/watch?v=kPRA0W1kECg
//https://www.youtube.com/watch?v=y9Ecb43qw98

USTRUCT()
struct FWrappedArray {
	GENERATED_BODY()

	UPROPERTY()
	TArray<class AObjToSort*> Bucket;
};

UENUM(BlueprintType)
enum class ESortType : uint8 {
	BubbleSort,
	SelectionSort,
	InsertionSort,
	
	RadixSort,
};

UENUM(BlueprintType)
enum class ESortMode : uint8 {
	Once,
	OneByOne,
	
	Undefined,
};

UCLASS()
class ALGOVISUALIZATION_API ASorter : public AActor {
	GENERATED_BODY()

public:
	ASorter();

	UFUNCTION(BlueprintCallable, Category = "Sort|Spawner")
	void Randomize();
	UFUNCTION(BlueprintCallable, Category = "Sort|Spawner")
	void Sort();
	UFUNCTION(BlueprintCallable, Category = "Sort|Spawner")
	void Stop();

	FORCEINLINE void SetSortType(ESortType NewSortType) { SortType = NewSortType; }
	FORCEINLINE void SetSortMode(ESortMode NewSortMode) { SortMode = NewSortMode; }
	FORCEINLINE int32 GetObjNum() const { return ObjNum; }
	FORCEINLINE int32 GetComparison() const { return Comparison; }
	FORCEINLINE int32 GetArrAccess() const { return ArrAccess; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSorting() const { return bSorting; }

protected:
	virtual void BeginPlay() override;

private:
	void SpawnObjs();

	void StartSort();
	void EndSort();

	void BubbleSort();
	UFUNCTION()
	void BubbleSortOneByOne(int32 I, int32 J);
	void SelectionSort();
	UFUNCTION()
	void SelectionSortOneByOne(int32 I, int32 J, int32 MinValIndex);
	void InsertionSort();
	UFUNCTION()
	void InsertionSortOneByOne(int32 I, int32 J);
	void RadixSort();
	UFUNCTION()
	void RadixSortOneByOne(TArray<FWrappedArray>& Buckets, int32 I, int32 J, int32 K, int32 L);

	void LocateObjs();
	void SwapAndLocate(int32 A, int32 B);

private:
	UPROPERTY()
	USceneComponent* DefaultComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	TArray<class AObjToSort*> ObjsToSort;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	TArray<class AObjToSort*> MovedObjsToSort;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	int32 ObjNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	ESortType SortType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	ESortMode SortMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	int32 Divisor;

	bool bSorting;
	bool bRandomized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort|Spawner", Meta = (AllowPrivateAccess = true))
	bool bUseInterval;

	int32 Comparison;
	int32 ArrAccess;

	/* For Widget */
	TSubclassOf<class USortMainWidget> MainWidgetClass;
};
