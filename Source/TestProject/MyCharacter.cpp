// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "PlatformColor.h"
#include "Gun.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//inicialitzo color
	InicialitzaColor();

	//spawnejem una arma
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	//Amaguem l'os de l'arma que ens ve amb el nostre mesh per poder acoplar la nostra que acabem de spawnejar
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	//L'acoplem al socket del mesh que te el nom de "WeaponSocket"
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
	Gun->SetOwner(this);

	Health = MaxHealth;
}

// Called every frame
/*void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Endavant"), this, &AMyCharacter::MouEndavant);
	PlayerInputComponent->BindAxis(TEXT("MiraAmunt"), this, &AMyCharacter::MiraAmunt);
	PlayerInputComponent->BindAxis(TEXT("MiraAmuntRate"), this, &AMyCharacter::MiraAmuntRate);
	PlayerInputComponent->BindAxis(TEXT("MiraDreta"), this, &AMyCharacter::MiraDreta);
	PlayerInputComponent->BindAxis(TEXT("MiraDretaRate"), this, &AMyCharacter::MiraDretaRate);
	PlayerInputComponent->BindAxis(TEXT("MouDreta"), this, &AMyCharacter::MouDreta);
	PlayerInputComponent->BindAction(TEXT("Salta"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ColorMes"), EInputEvent::IE_Pressed, this, &AMyCharacter::ColorMes);
	PlayerInputComponent->BindAction(TEXT("ColorMenys"), EInputEvent::IE_Pressed, this, &AMyCharacter::ColorMenys);
	PlayerInputComponent->BindAction(TEXT("Dispara"), EInputEvent::IE_Pressed, this, &AMyCharacter::Shoot);

}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Health > 0)
	{
		Health -= DamageApplied;
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);
	
	return Health;
}

bool AMyCharacter::IsDead() const
{
	if (Health > 0)return false;
	else return true;
}

void AMyCharacter::MouEndavant(float value)
{
	AddMovementInput(GetActorForwardVector() * value, MovementSpeed);
}

void AMyCharacter::MiraAmunt(float value)
{
	AddControllerPitchInput(value * CameraSpeed);
}

void AMyCharacter::MiraAmuntRate(float value)
{
	AddControllerPitchInput(value * CameraSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::MiraDretaRate(float value)
{
	AddControllerPitchInput(value * CameraSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::MouDreta(float value)
{
	AddMovementInput(GetActorRightVector() * value, MovementSpeed);
}

void AMyCharacter::MiraDreta(float value)
{
	AddControllerYawInput(value * CameraSpeed);
}

void AMyCharacter::Shoot()
{
	Gun->PullTrigger();
}

void AMyCharacter::ColorMes()
{
	if (iColorActual < Colors.Num() - 1)
	{
		iColorActual += 1;
	}
	else
	{
		iColorActual = 0;
	}

	CanviaColor();	

}

void AMyCharacter::ColorMenys()
{
	if (iColorActual > 0)
	{
		iColorActual -= 1;
	}
	else
	{
		iColorActual = Colors.Num() - 1;
	}
	CanviaColor();

}

void AMyCharacter::CanviaColor()
{
	ColorActual = NomColors[iColorActual];
	if (matInstance)
	{
		//Si s'ha creat correctament, agafem el paràmetre _BodyColor i el posem al color blanc
		matInstance->SetVectorParameterValue("_BodyColor", Colors[iColorActual]);
		//UE_LOG(LogTemp, Warning, TEXT("Canvi %s"), *ColorActual);
		for (int i = 0; i < nMaterials + 1; i++)
		{
			//Apliquem aquest material creat al nostre mesh
			GetMesh()->SetMaterial(i, matInstance);
		}
	}

	for (TObjectIterator<UPlatformColor> Itr; Itr; ++Itr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("NAME: %s"), *Itr->GetName());

		if (Itr->IsA(UPlatformColor::StaticClass()))
		{
			UPlatformColor* actorClass = *Itr;
			actorClass->checkColor(ColorActual);
		}
	}
	
}

void AMyCharacter::InicialitzaColor()
{
	//Agafem el material del skeletical mesh que utilitzem
	UMaterialInterface* Material = GetMesh()->GetMaterial(0);
	//Creem un material dinamic a partir d'aquest
	matInstance = GetMesh()->CreateDynamicMaterialInstance(0, Material);
	if (matInstance)
	{
		//Si s'ha creat correctament, agafem el paràmetre _BodyColor i el posem al color blanc
		matInstance->SetVectorParameterValue("_BodyColor", FLinearColor(255.f, 255.f, 255.f));

		for (int i = 0; i < nMaterials; i++)
		{
			//Apliquem aquest material creat al nostre mesh
			GetMesh()->SetMaterial(i, matInstance);
		}
	}
}