#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmisorMision.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;
class UMisionDefinicion;

UCLASS()
class SISTEMAMISIONES_API AEmisorMision : public AActor
{
	GENERATED_BODY()

public:
	AEmisorMision();

protected:
	UFUNCTION()
	void AlEntrarEnZona(
		UPrimitiveComponent* ComponenteSolapado,
		AActor* OtroActor,
		UPrimitiveComponent* OtroComponente,
		int32 OtroIndiceCuerpo,
		bool bDesdeBarrido,
		const FHitResult& ResultadoBarrido);

	UPROPERTY(VisibleAnywhere, Category = "Mision")
	TObjectPtr<UBoxComponent> ZonaInicio;

	UPROPERTY(VisibleAnywhere, Category = "Mision")
	TObjectPtr<UStaticMeshComponent> ModeloTerminal;

	UPROPERTY(EditInstanceOnly, Category = "Mision")
	TObjectPtr<UMisionDefinicion> MisionAIniciar;
};
