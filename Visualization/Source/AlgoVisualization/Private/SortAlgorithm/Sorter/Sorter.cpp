#include "Sorter.h"
#include "ObjToSort.h"
#include "SortMainWidget.h"

#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Containers/Queue.h"

ASorter::ASorter() {
	PrimaryActorTick.bCanEverTick = false;

	DefaultComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComp"));
	RootComponent = DefaultComp;

	ObjNum = 1800;
	SortType = ESortType::BubbleSort;
	SortMode = ESortMode::Once;
	Divisor = 5;

	bSorting = false;
	bRandomized = false;
	/* Sort can be faster by making it true. It makes the sorter process one cycle by "Divisor" ticks. */
	bUseInterval = false;

	/* For Widget */
	static ConstructorHelpers::FClassFinder<USortMainWidget> MainWidgetFinder(TEXT("WidgetBlueprint'/Game/Blueprints/Sort/Widget/SortMainWidget_BP.SortMainWidget_BP_C'"));
	if (MainWidgetFinder.Succeeded()) {
		MainWidgetClass = MainWidgetFinder.Class;
	}
}

void ASorter::BeginPlay() {
	Super::BeginPlay();
	SpawnObjs();

	/* For Widget */
	auto MainWidget = CreateWidget<USortMainWidget>(UGameplayStatics::GetPlayerController(this, 0), MainWidgetClass);
	if (MainWidget) {
		MainWidget->SetSorter(this);
		MainWidget->CustomInit();
		MainWidget->AddToViewport();
	}
}

void ASorter::SpawnObjs() {
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Origin = GetActorLocation();

		for (int32 Index = 0; Index < ObjNum; ++Index) {
			float Alpha = static_cast<float>(Index) / ObjNum;
			AObjToSort* Obj = World->SpawnActor<AObjToSort>(AObjToSort::StaticClass(), GetActorLocation(), FRotator(0.0f, 0.0f, Alpha * 360.0f), SpawnParams);
			
			Obj->SetRandomColor(Alpha);
			float Size = 0.18 * (360.0f / ObjNum);
			Obj->SetSize(FVector(Size, Size, 1.0f));
			Obj->SetID(Index);

			ObjsToSort.Add(Obj);
		}
	}
}

void ASorter::StartSort() {
	bSorting = true;
}

void ASorter::EndSort() {
	bSorting = false;
}

void ASorter::Randomize() {
	if (!bSorting) {
		bRandomized = true;
		Comparison = 0;
		ArrAccess = 0;
		for (const auto& Obj : ObjsToSort) {
			Obj->SetActorHiddenInGame(false);
		}
		for (int32 Index = 0; Index < ObjNum; ++Index) {
			ObjsToSort.Swap(Index, FMath::RandRange(0, ObjNum - 1));
		}
		LocateObjs();
	}
}

void ASorter::Sort() {
	if (!bSorting && bRandomized) {
		bRandomized = false;
		StartSort();
		switch (SortType) {
		case ESortType::BubbleSort:		SortMode == ESortMode::Once ? BubbleSort() : BubbleSortOneByOne(0, 0);			break;
		case ESortType::InsertionSort:	SortMode == ESortMode::Once ? InsertionSort() : InsertionSortOneByOne(0, 0);	break;
		case ESortType::SelectionSort:	SortMode == ESortMode::Once ? SelectionSort() : SelectionSortOneByOne(0, 1, 0); break;
		case ESortType::RadixSort: {
			TArray<FWrappedArray> Buckets;
			Buckets.AddDefaulted(10);
			MovedObjsToSort = ObjsToSort;
			SortMode == ESortMode::Once ? RadixSort() : RadixSortOneByOne(Buckets, 1, 0, 0, 0);
			break;
		}
		default: break;
		}
	}
}

void ASorter::Stop() {
	EndSort();
}

void ASorter::BubbleSort() {
	for (int32 I = 0; I < ObjNum - 1; ++I) {
		for (int32 j = 0; j < ObjNum - 1 - I; ++j) {
			++Comparison;
			if (ObjsToSort[j + 1]->GetID() < ObjsToSort[j]->GetID()) {
				/* Two times for swap */
				ArrAccess += 2;
				ObjsToSort.Swap(j, j + 1);
			}
		}
	}
	LocateObjs();

	EndSort();
}

void ASorter::BubbleSortOneByOne(int32 I, int32 J) {
	if (bSorting) {
		int32 Interval = ObjNum / Divisor;
		if (I < ObjNum - 1) {
			if (J < ObjNum - 1 - I) {
				if (bUseInterval) {
					int32 Max = J + Interval;
					Max = Max <= ObjNum - 1 - I ? Max : ObjNum - 1 - I;
					for (int32 K = J; K < Max; ++K) {
						++Comparison;
						if (ObjsToSort[K + 1]->GetID() < ObjsToSort[K]->GetID()) {
							ArrAccess += 2;
							SwapAndLocate(K, K + 1);
						}
					}
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("BubbleSortOnebyOne")), I, Max));
				}
				else {
					++Comparison;
					if (ObjsToSort[J + 1]->GetID() < ObjsToSort[J]->GetID()) {
						ArrAccess += 2;
						SwapAndLocate(J, J + 1);
					}
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("BubbleSortOnebyOne")), I, J + 1));
				}
			}
			else {
				GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("BubbleSortOnebyOne")), I + 1, 0));
			}
		}
		else {
			EndSort();
		}
	}
}

void ASorter::SelectionSort() {
	for (int32 I = 0; I < ObjNum - 1; ++I) {
		int32 MinValIndex = I;
		for (int32 J = I + 1; J < ObjNum; ++J) {
			++Comparison;
			if (ObjsToSort[J]->GetID() < ObjsToSort[MinValIndex]->GetID()) {
				MinValIndex = J;
			}
		}
		ArrAccess += 2;
		ObjsToSort.Swap(MinValIndex, I);
	}
	LocateObjs();

	EndSort();
}

void ASorter::SelectionSortOneByOne(int32 I, int32 J, int32 MinValIndex) {
	if (bSorting) {
		int32 Interval = ObjNum / Divisor;
		if (I < ObjNum - 1) {
			if (J < ObjNum) {
				if (bUseInterval) {
					int32 Max = J + Interval;
					Max = Max <= ObjNum ? Max : ObjNum;
					for (int32 K = J; K < Max; ++K) {
						++Comparison;
						if (ObjsToSort[K]->GetID() < ObjsToSort[MinValIndex]->GetID()) {
							MinValIndex = K;
						}
					}
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("SelectionSortOneByOne")), I, Max, MinValIndex));
				}
				else {
					++Comparison;
					if (ObjsToSort[J]->GetID() < ObjsToSort[MinValIndex]->GetID()) {
						MinValIndex = J;
					}
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("SelectionSortOneByOne")), I, J + 1, MinValIndex));
				}
			}
			else {
				ArrAccess += 2;
				SwapAndLocate(MinValIndex, I);
				GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("SelectionSortOneByOne")), I + 1, I + 2, I + 1));
			}
		}
		else {
			EndSort();
		}
	}
}

void ASorter::InsertionSort() {
	for (int32 I = 0; I < ObjNum - 1; ++I) {
		for (int32 J = I; 0 <= J && ObjsToSort[J + 1]->GetID() < ObjsToSort[J]->GetID(); --J) {
			++Comparison;
			ArrAccess += 2;
			ObjsToSort.Swap(J, J + 1);
		}
	}
	LocateObjs();

	EndSort();
}

void ASorter::InsertionSortOneByOne(int32 I, int32 J) {
	if (bSorting) {
		int32 Interval = ObjNum / Divisor;
		if (I < ObjNum - 1) {
			if (0 <= J && ObjsToSort[J + 1]->GetID() < ObjsToSort[J]->GetID()) {
				if (bUseInterval) {
					int32 Min = J - Interval;
					Min = -1 <= Min ? Min : -1;
					for (int32 K = J; Min < K && ObjsToSort[K + 1]->GetID() < ObjsToSort[K]->GetID(); --K) {
						++Comparison;
						ArrAccess += 2;
						SwapAndLocate(K, K + 1);
					}
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("InsertionSortOneByOne")), I, Min));
				}
				else {
					++Comparison;
					ArrAccess += 2;
					SwapAndLocate(J, J + 1);
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("InsertionSortOneByOne")), I, J - 1));
				}
			}
			else {
				GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("InsertionSortOneByOne")), I + 1, I + 1));
			}
		}
		else {
			EndSort();
		}
	}
}


/* Completed Above */

void ASorter::RadixSort() {
	TArray<TQueue<AObjToSort*>> Buckets;
	Buckets.AddDefaulted(10);
	int32 MaxDigit = FMath::LogX(10.0f, ObjNum) + 1;
	for (int32 I = 1; I <= MaxDigit; ++I) {
		for (auto Objs : ObjsToSort) {
			int32 ID = Objs->GetID() / static_cast<int32>(pow(10, I - 1));
			int32 ComparedDigit = ID % 10;
			++ArrAccess;
			Buckets[ComparedDigit].Enqueue(Objs);
		}

		ObjsToSort.Empty();
		for (auto& Bucket : Buckets) {
			AObjToSort* Obj;
			while (Bucket.Dequeue(Obj)) {
				++ArrAccess;
				ObjsToSort.Add(Obj);
			}
		}
	}
	LocateObjs();

	EndSort();
}

void ASorter::RadixSortOneByOne(TArray<FWrappedArray>& Buckets, int32 I, int32 J, int32 K, int32 L) {
	if (bSorting) {
		int32 Interval = ObjNum / Divisor;
		int32 MaxDigit = FMath::LogX(10.0f, ObjNum) + 1;
		if (I <= MaxDigit) {
			if (J < ObjNum) {
				int32 Max = J + Interval;
				Max = Max < ObjNum ? Max : ObjNum - 1;

				for (int32 M = J; M <= Max; ++M) {
					int32 ID = MovedObjsToSort[M]->GetID() / static_cast<int32>(pow(10, I - 1));
					int32 ComparedDigit = ID % 10;
					++ArrAccess;
					MovedObjsToSort[M]->SetActorHiddenInGame(true);
					Buckets[ComparedDigit].Bucket.Push(MovedObjsToSort[M]);
				}
				GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("RadixSortOneByOne")), Buckets, I, Max + 1, 0, 0));
			}
			else if (J == ObjNum) {
				static int32 Count;
				if (K == 0 && L == 0) {
					Count = 0;
					MovedObjsToSort.Empty();
				}
				if (K < 10) {
					auto& Bucket = Buckets[K].Bucket;
					if (L < Buckets[K].Bucket.Num()) {
						auto& Item = Bucket[L];
						++ArrAccess;
						float Alpha = static_cast<float>(Count++) / ObjNum;
						Item->SetActorRotation(FRotator(0.0f, 0.0f, Alpha * 360.0f));
						Item->SetActorHiddenInGame(false);
						MovedObjsToSort.Add(Item);
						GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("RadixSortOneByOne")), Buckets, I, J, K, L + 1));
					}
					else {
						Bucket.Empty();
						GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("RadixSortOneByOne")), Buckets, I, J, K + 1, 0));
					}
				}
				else {
					GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, FName(TEXT("RadixSortOneByOne")), Buckets, I + 1, 0, 0, 0));
				}
			}
		}
		else {
			EndSort();
		}
	}
}

void ASorter::LocateObjs() {
	for (int32 Index = 0; Index < ObjNum; ++Index) {
		float Alpha = static_cast<float>(Index) / ObjNum;
		ObjsToSort[Index]->SetActorRotation(FRotator(0.0f, 0.0f, Alpha * 360.0f));
	}
}

void ASorter::SwapAndLocate(int32 A, int32 B) {
	ObjsToSort.Swap(A, B);

	float Alpha = static_cast<float>(A) / ObjNum;
	float Beta = static_cast<float>(B) / ObjNum;

	ObjsToSort[A]->SetActorRotation(FRotator(0.0f, 0.0f, Alpha * 360.0f));
	ObjsToSort[B]->SetActorRotation(FRotator(0.0f, 0.0f, Beta * 360.0f));
}