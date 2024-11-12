// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L02GameMode.h"
#include "DonkeyKong_L02Character.h"
#include "UObject/ConstructorHelpers.h"
#include "ObstaculoMuro.h"
#include "Capsula.h"
#include "componentePlataforma.h"
#include "Barril.h"
#include "Esfera.h"
#include "EnemyFacade.h"

ADonkeyKong_L02GameMode::ADonkeyKong_L02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADonkeyKong_L02GameMode::BeginPlay()
{
    Super::BeginPlay();

	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	EnemyFacade = GetWorld()->SpawnActor<AEnemyFacade>(AEnemyFacade::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (EnemyFacade)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("EnemyFacade creado exitosamente."));
		// Usar el Facade para crear enemigos
		EnemyFacade->CrearEnemigo("Goomba", FVector(100.0f, 0.0f, 0.0f), 150.0f);
		EnemyFacade->CrearEnemigo("Koopa", FVector(200.0f, 0.0f, 0.0f), 100.0f);

		// Programar la eliminación de todos los enemigos después de 3 segundos
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, EnemyFacade, &AEnemyFacade::EliminarTodosLosEnemigos, 100.0f, false);
	}

	// Cambiar la posición del personaje inicial
	FVector SpawnLocation = FVector(1160.0f, 4300.0f, 7000.0f); // Cambia estos valores a tu posición deseada
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f); // Rotación inicial si es necesario

	// Verifica si el personaje predeterminado existe y luego lo mueve
	if (GetWorld())
	{
		ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
		if (Character)
		{
			Character->SetActorLocation(SpawnLocation); // Establecer la nueva posición
			Character->SetActorRotation(SpawnRotation); // Establecer la nueva rotación
		}
	}
	// Spawn an instance of the AMyFirstActor class at the
	//default location.
	/*FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculoMuro>(AObstaculoMuro::StaticClass(), SpawnLocation);*/
	/*if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}*/

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 1400.0f;
	float incrementoInicioPiso = 100.0f;

	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

		for (int ncp = 0; ncp < 10; ncp++) {
			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
			if (npp % 2 != 0) {
				//if (ncp == 0 || ncp == 1 || ncp == 4) {
				AcomponentePlataforma* cp = GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP);
				if (ncp == 1) {
					cp->bMoverHorizontalmente = true;
					cp->StartPoint = FVector(posicionInicial.X, posicionInicial.Y, posicionInicial.Z);
					cp->EndPoint = FVector(posicionInicial.X + 1000.0f, posicionInicial.Y, posicionInicial.Z);
				}
				componentesPlataforma.Add(cp);
				//componentesPlataforma.Add(GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP));
					
					
				if (ncp < 9) {
					posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
				}
			}
			else {
				componentesPlataforma.Add(GetWorld()->SpawnActor<AcomponentePlataforma>(AcomponentePlataforma::StaticClass(), SpawnLocationCP));
				if (ncp < 9) {
					posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
				}
			}
		}
		
		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnBarrilTimerHandle, this, &ADonkeyKong_L02GameMode::SpawnBarril, 3.0f, true);
	
	//Crear una esfera en la parte superior del primer piso que baje rebotando hasta llegar al suelo
	
	/*for (int nes = 0; nes < 5; nes++) {
		FTransform SpawnLocationEsfera;
		SpawnLocationEsfera.SetLocation(FVector(1300.0f, -200.0f, 1060.0f));
		SpawnLocationEsfera.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
		esferasMap.Add(nes, GetWorld()->SpawnActor<AEsfera>(AEsfera::StaticClass(), SpawnLocationEsfera));
	}*/
}

void ADonkeyKong_L02GameMode::SpawnBarril()
{
	//if (barriles.Num() >= numeroMaximoBarriles) {
	if (contadorBarriles < numeroMaximoBarriles) {
		//Spawn de un objeto barril en la escena sobre la primera plataforma
		FTransform SpawnLocationBarril;
		SpawnLocationBarril.SetLocation(FVector(1160.0f, 900.0f, 860.0f));
		SpawnLocationBarril.SetRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
		//ABarril* barril01 = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril);
		barriles.Add(GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocationBarril));
		contadorBarriles++;

		if (contadorBarriles >= numeroMaximoBarriles) {
			GetWorld()->GetTimerManager().ClearTimer(SpawnBarrilTimerHandle);
		}
	}
}
