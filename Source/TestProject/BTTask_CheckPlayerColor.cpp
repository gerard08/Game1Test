// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckPlayerColor.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckPlayerColor::UBTTask_CheckPlayerColor()
{

	NodeName = TEXT("Check player color");

}

EBTNodeResult::Type UBTTask_CheckPlayerColor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Agafem el controlador de la IA
	AAIController* cont = OwnerComp.GetAIOwner();

	//Si no es pot
	if (!cont)
	{
		//Retornem error
		return EBTNodeResult::Failed;
	}
	//Trobem la classe AMyCharacter controlada pel controlador de la IA
	AMyCharacter* Character = Cast<AMyCharacter>(cont->GetPawn());

	//Agafem el controlador del jugador
	APlayerController* pcont = GetWorld()->GetFirstPlayerController();

	//Trobem la classe AMyCharacter controlada pel jugador
	AMyCharacter* Player = Cast<AMyCharacter>(pcont->GetCharacter());

	//Si IA i Jugador tenen el mateix color
	if (Character->iColorActual == Player->iColorActual)
	{
		//Posem el valor de la pissarra com a true
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("SameColor"), true);
	}
	//sino
	else
	{
		//Esborrem el camp i la localitzacio del jugador
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("SameColor"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Playerlocation"));

	}

	return EBTNodeResult::Succeeded;
}