#include "EnemyFacade.h"
#include "Enemigo.h"

AEnemyFacade::AEnemyFacade()
{
    PrimaryActorTick.bCanEverTick = false;
}

AEnemigo* AEnemyFacade::CrearEnemigo(FString Tipo, FVector Posicion, float Velocidad)
{
    // Crear el enemigo y establecer sus propiedades iniciales
    FActorSpawnParameters SpawnParams;
    AEnemigo* NuevoEnemigo = GetWorld()->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), Posicion, FRotator::ZeroRotator, SpawnParams);

    if (NuevoEnemigo)
    {
        NuevoEnemigo->SetTipoEnemigo(Tipo);
        NuevoEnemigo->SetVelocidad(Velocidad);

        // Agregar el enemigo a la lista
        Enemigos.Add(NuevoEnemigo);
        UE_LOG(LogTemp, Warning, TEXT("Enemigo de tipo %s creado en %s"), *Tipo, *Posicion.ToString());
    }

    return NuevoEnemigo;
}

void AEnemyFacade::EliminarTodosLosEnemigos()
{
    for (AEnemigo* Enemigo : Enemigos)
    {
        if (Enemigo)
        {
            Enemigo->Destroy();
        }
    }

    // Vacía la lista después de eliminar los enemigos
    Enemigos.Empty();
    UE_LOG(LogTemp, Warning, TEXT("Todos los enemigos han sido eliminados"));
}






