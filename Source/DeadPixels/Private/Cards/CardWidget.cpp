#include "CardWidget.h"
#include "Kismet/GameplayStatics.h"

void UCardWidget::OnCardClicked()
{
	if (!CardInstance)
		return;

	//AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//CardInstance->ApplyCard(Player);

	AActor* Weapon = UGameplayStatics::GetActorOfClass(GetWorld(), 0);
	CardInstance->ApplyCard(Weapon);

	// Close UI
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}