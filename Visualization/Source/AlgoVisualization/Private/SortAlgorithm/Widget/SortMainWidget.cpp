#include "SortMainWidget.h"
#include "Sorter.h"

#include "TextBlock.h"
#include "ComboBoxString.h"
#include "CheckBox.h"

void USortMainWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void USortMainWidget::CustomInit() {
	if (Sorter) {
		/* Set Combo Box */
		SortTypeList->AddOption(TEXT("1. Bubble Sort"));		// Index 0
		SortTypeList->AddOption(TEXT("2. Selection Sort"));		// Index 1
		SortTypeList->AddOption(TEXT("3. Insertion Sort"));		// Index 2
		SortTypeList->AddOption(TEXT("4. Radix Sort"));			// Index 3
		SortTypeList->SetSelectedIndex(0);
		SelectionChanged();
		FScriptDelegate ComboBoxDelegate;
		ComboBoxDelegate.BindUFunction(this, TEXT("SelectionChanged"));
		SortTypeList->OnSelectionChanged.AddUnique(ComboBoxDelegate);

		/* Set Check Box */
		FScriptDelegate CheckBoxDelegate;
		CheckBoxDelegate.BindUFunction(this, TEXT("CheckChanged"));
		SortModeCheck->OnCheckStateChanged.AddUnique(CheckBoxDelegate);
	}
}

void USortMainWidget::SelectionChanged() {
	FString Temp = SortTypeList->GetSelectedOption();
	/* Romove '#. ' from string */
	Temp.RemoveAt(0, 2);
	FString SortNameText = TEXT("- ") + Temp + TEXT(" -");

	SortName->SetText(FText::FromString(SortNameText));

	Sorter->SetSortType(static_cast<ESortType>(SortTypeList->GetSelectedIndex()));
}

void USortMainWidget::CheckChanged() {
	Sorter->SetSortMode(static_cast<ESortMode>(SortModeCheck->GetCheckedState()));
}

void USortMainWidget::ChangeExplanation() {

}

FText USortMainWidget::SetTotalObjs() {
	FString Res(TEXT("Total = "));
	if (Sorter) {
		Res += FString::FromInt(Sorter->GetObjNum());
	}
	return FText::FromString(Res);
}

FText USortMainWidget::SetComparison() {
	FString Res(TEXT("Comparison = "));
	if (Sorter) {
		Res += FString::FromInt(Sorter->GetComparison());
	}
	return FText::FromString(Res);
}

FText USortMainWidget::SetArrAccess() {
	FString Res(TEXT("ArrAccess = "));
	if (Sorter) {
		Res += FString::FromInt(Sorter->GetArrAccess());
	}
	return FText::FromString(Res);
}