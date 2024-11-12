#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFacade.generated.h"

// Declaraci�n anticipada de la clase Enemigo
class AEnemigo;

UCLASS()
class DONKEYKONG_L02_API AEnemyFacade : public AActor
{
    GENERATED_BODY()

public:
    AEnemyFacade();

    // M�todo para crear un enemigo de un tipo espec�fico
    AEnemigo* CrearEnemigo(FString Tipo, FVector Posicion, float Velocidad);

    // M�todo para eliminar todos los enemigos
    void EliminarTodosLosEnemigos();

private:
    // Almacena todos los enemigos creados
    TArray<AEnemigo*> Enemigos;
};
