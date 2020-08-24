// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	AAIController* cont = OwnerComp.GetAIOwner();


	//En cas que no es pugui
	if (!cont)
	{
		//retornem error
		return;
	}

	
	//Si la IA pot veure directament al jugador
	if (cont->LineOfSightTo(PlayerPawn))
	{

		//Afegim a la pissarra la posicio actualitzada del jugador
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

		//Si el valor de la pissarra "SameColor" és true
		if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("SameColor")) == true)
		{
			//Afegim la posicio del jugador a la pissarra
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		}
	}

}