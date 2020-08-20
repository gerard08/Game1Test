// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckColor.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckColor::UBTTask_CheckColor()
{
	NodeName = TEXT("Check color");
	
}

EBTNodeResult::Type UBTTask_CheckColor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	//Si l'index del color de la IA �s mes petit que el del jugador
	if (Character->iColorActual < Player->iColorActual)
	{
		//Sumem un color
		Character->ColorMes(true);
		
		//Retornem correcte
		return EBTNodeResult::Succeeded;
	}

	//Si l'index del color de la IA �s mes gran que el del jugador
	if (Character->iColorActual > Player->iColorActual)
	{
		//Restem un color
		Character->ColorMenys(true);
		
		//Retornem correcte
		return EBTNodeResult::Succeeded;
	}

	//En cas que sigui el mateix color retornem error
	return EBTNodeResult::Failed;
}