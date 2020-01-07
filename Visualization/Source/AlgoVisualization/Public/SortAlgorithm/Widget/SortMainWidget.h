#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SortMainWidget.generated.h"

UCLASS()
class ALGOVISUALIZATION_API USortMainWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	FORCEINLINE void SetSorter(class ASorter* NewSorter) { Sorter = NewSorter; }
	void CustomInit();

private:
	UFUNCTION()
	void SelectionChanged();
	UFUNCTION()
	void CheckChanged();
	UFUNCTION()
	void ChangeExplanation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetTotalObjs();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetComparison();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText SetArrAccess();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, Meta = (AllowPrivateAccess = true))
	class ASorter* Sorter;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* SortName;
	UPROPERTY(Meta = (BindWidget))
	class UComboBoxString* SortTypeList;
	UPROPERTY(Meta = (BindWidget))
	class UCheckBox* SortModeCheck;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Explanation;

	//UPROPERTY(Meta = (BindWidget))
	//class UTextBlock* TotalObjs;
	//UPROPERTY(Meta = (BindWidget))
	//class UTextBlock* Comparison;
	//UPROPERTY(Meta = (BindWidget))
	//class UTextBlock* ArrAccess;
};
