// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//importo els materials
#include "Materials/Material.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AGun;

UCLASS()
class TESTPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Override de la funcio per rebre mal
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	///////////////COLORS////////////////////////

	UMaterialInstanceDynamic* matInstance;

	//Defineixo els colors en els que es pot convertir el personatge
	
	UPROPERTY(EditAnywhere)
	FLinearColor Taronja = FLinearColor(0.89f, 0.30f, 0.06f);
	UPROPERTY(EditAnywhere)
	FLinearColor Verd = FLinearColor(0.15f, 0.78f, 0.07f);
	UPROPERTY(EditAnywhere)
	FLinearColor Turquesa = FLinearColor(0.125f, 0.811f, 0.729f);
	UPROPERTY(EditAnywhere)
	FLinearColor Rosa = FLinearColor(0.811f, 0.125f, 0.301f);
	UPROPERTY(EditAnywhere)
	FLinearColor Lila = FLinearColor(0.769f, 0.141f, 0.922f);

	FString ColorActual = "";

	//Numero de materials que tenim (fins quina capa canviem el color)
	UPROPERTY(EditAnywhere)
		uint8 nMaterials = 1;

	//Vector amb els noms dels colors en els que ens podem transformar
	TArray<FString> NomColors = { "Verd", "Taronja", "Turquesa", "Rosa", "Lila" };

	//Vector amb els colors en els que ens podem transformar
	TArray<FLinearColor> Colors = { Verd, Taronja, Turquesa, Rosa, Lila };

	//Index del color que estem fent servir actualment
	int8_t iColorActual = -1;

	//Suma color (hem afegit un bool que ens permet saber si la funció la crida el jugador o la IA)
	void ColorMes(bool IA = false);

	//Resta color (hem afegit un bool que ens permet saber si la funció la crida el jugador o la IA)
	void ColorMenys(bool IA = false);

	//Funcio que efectua el canvi de color i avisa a les parets d'aquest (hem afegit un bool que ens 
	//permet saber si la funció la crida el jugador o la IA)
	void CanviaColor(bool IA = false);

	//funcio per posar el color inicial
	void InicialitzaColor();

	//Canvi color per collision channel
	ECollisionChannel TradueixColor();

	//Primitive component
	UPrimitiveComponent* Primitive = nullptr;

	void SumaColor();

	void RestaColor();

	void SetOpacity(bool opacity);
	//////////////////ARMA//////////////////

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	//Per disparar
	void Shoot();


private:
	////////////////MOVIMENT///////////////////


	//Velocitat de moviment
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1.f;

	//Velocitat de camera
	UPROPERTY(EditAnywhere)
		float CameraSpeed = 1.f;

	//Funcions de moviment
	void MouEndavant(float value);
	void MiraAmunt(float value);
	void MiraAmuntRate(float value);
	void MiraDretaRate(float value);
	void MouDreta(float value);
	void MiraDreta(float value);

	////////////////PERSONATGE////////////////
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
		float Health;


};
