// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick()
	MoveToActor(PlayerPawn, 200);
}
