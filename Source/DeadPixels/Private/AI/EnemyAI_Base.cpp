// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAI_Base.h"

#include "Characters/Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AEnemyAI_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedEnemy = Cast<AEnemyBase>(InPawn);
	if (!PossessedEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to possess enemy!"));
	}

}

void AEnemyAI_Base::BeginPlay()
{
	Super::BeginPlay();
	PlayerTarget = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAI_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("EnemyAI Tick running"));
	if (PlayerTarget)
	{
		FVector TargetForwardVector;
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			PossessedEnemy->GetActorLocation(),
			PlayerTarget->GetActorLocation());

		TargetForwardVector = UKismetMathLibrary::GetForwardVector(TargetRotation);

		if (DistanceToPlayer() > StopDistance)
		{
			PossessedEnemy->MoveEnemy(TargetForwardVector);
		}

		FVector PlayerDirection = TargetForwardVector;
		PlayerDirection.Z = 0; // Flattens to a 2D Plane
		PlayerDirection.Normalize();
		
		EnemyDirectionality = FVector2D(PlayerDirection.X, PlayerDirection.Y);
		PossessedEnemy->EnemyDirectionality = EnemyDirectionality;
	}
}

float AEnemyAI_Base::DistanceToPlayer()
{
	float distance = UKismetMathLibrary::Vector_Distance(PlayerTarget->GetActorLocation(),
	                                                     PossessedEnemy->GetActorLocation());
	return distance;
}
