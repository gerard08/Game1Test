// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "BTTask_CheckPlayerColor.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UBTTask_CheckPlayerColor : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_CheckPlayerColor();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

};
