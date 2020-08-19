// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckColor.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "EnemyAIController.h"

UBTTask_CheckColor::UBTTask_CheckColor()
{
	NodeName = TEXT("Check color");
	
}

EBTNodeResult::Type UBTTask_CheckColor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* cont = OwnerComp.GetAIOwner();

	if (!cont)
	{
		return EBTNodeResult::Failed;
	}
	AMyCharacter* Character = Cast<AMyCharacter>(cont->GetPawn());
	

	if (!Character)UE_LOG(LogTemp, Warning, TEXT("IA"));
	
	APlayerController* pcont = GetWorld()->GetFirstPlayerController();

	AMyCharacter* Player = Cast<AMyCharacter>(pcont->GetCharacter());
	if (!Player)UE_LOG(LogTemp, Warning, TEXT("Player"));

	if (Character->iColorActual < Player->iColorActual)
	{
		Character->ColorMes(true);
		return EBTNodeResult::Succeeded;
	}
	if (Character->iColorActual > Player->iColorActual)
	{
		Character->ColorMenys(true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;
}