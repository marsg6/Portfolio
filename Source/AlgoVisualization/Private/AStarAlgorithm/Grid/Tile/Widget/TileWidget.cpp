#include "TileWidget.h"
#include "GridBase.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UTileWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void UTileWidget::CustomInit() {
	if (Grid) {
		FSlateFontInfo TileCostFontInfo{ TileCost->Font };
		TileCostFontInfo.Size = Grid->GetTileSize() / (50.0f / 24.0f);
		TileCost->SetFont(TileCostFontInfo);

		FSlateFontInfo CostFromStartFontInfo{ CostFromStart->Font };
		CostFromStartFontInfo.Size = Grid->GetTileSize() / (50.0f / 32.0f);
		CostFromStart->SetFont(CostFromStartFontInfo);
	}
}

FText UTileWidget::SetCurrentCost() {
	if (Grid) {
		auto TileData = Grid->GetTileInfos().Find(GridCoord);
		if (TileData) {
			if (TileData->CostFromStart != 999) {
				return FText::FromString(FString::FromInt(TileData->CostFromStart));
			}
		}
	}
	return FText();
}

FText UTileWidget::SetTileCost() {
	if (Grid) {
		auto TileData = Grid->GetTileInfos().Find(GridCoord);
		if (TileData) {
			return FText::FromString(FString::FromInt(TileData->TileCost));
		}
	}
	return FText();
}