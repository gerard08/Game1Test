// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "MyCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* cont =  OwnerComp.GetAIOwner();

	if (!cont)
	{
		return EBTNodeResult::Failed;
	}
	
	AMyCharacter* Character = Cast<AMyCharacter>(cont->GetPawn());

	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();	

	return EBTNodeResult::Succeeded;
}