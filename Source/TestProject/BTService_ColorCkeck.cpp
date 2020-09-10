// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ColorCkeck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.h"
#include "AIController.h"


UBTService_ColorCkeck::UBTService_ColorCkeck()
{
	NodeName = "Check Player Color";
}

void UBTService_ColorCkeck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Agafem el controlador de la IA
	AAIController* cont = OwnerComp.GetAIOwner();


	//Si no es pot
	if (!cont)
	{
		//Retornem error
		return;
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
		Character->SetOpacity(true);
		//Posem el valor de la pissarra com a true
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("SameColor"), true);
	}
	//sino
	else
	{
		Character->SetOpacity(false);
		//Esborrem el camp i la localitzacio del jugador
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("SameColor"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Playerlocation"));

	}


}