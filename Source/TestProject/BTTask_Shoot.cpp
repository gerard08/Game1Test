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

	//Agafem el controlador de la IA
	AAIController* cont =  OwnerComp.GetAIOwner();

	//En cas que no es pugui
	if (!cont)
	{
		//retornem error
		return EBTNodeResult::Failed;
	}
	
	//Agafem la classe AMyCharacter que està sent controlada pel controlador de la IA
	AMyCharacter* Character = Cast<AMyCharacter>(cont->GetPawn());

	//En cas que no es pugui
	if (!Character)
	{
		//retornem error
		return EBTNodeResult::Failed;
	}

	//Cridem la funció de disparar de la classe que està sent controlada per la IA
	Character->Shoot();	

	//Retornem Success
	return EBTNodeResult::Succeeded;
}