// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Guardem el Pawn del jugador
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior)
	{
		//Afegim l'arbre de la IA
		RunBehaviorTree(AIBehavior);
		//Afegim a la pissarra la posicio del jugador
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		//Afegim a la pissarra la posicio inicial de la IA (no ho fem servir de moment)
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Si la IA pot veure directament al jugador
	if (LineOfSightTo(PlayerPawn))
	{
		//Afegim a la pissarra la posicio actualitzada del jugador
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

		//Si el valor de la pissarra "SameColor" és true
		if (GetBlackboardComponent()->GetValueAsBool(TEXT("SameColor")) == true)
		{
			//Afegim la posicio del jugador a la pissarra
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		}
	}
}