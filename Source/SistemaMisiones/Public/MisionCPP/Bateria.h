#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bateria.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

UCLASS()
class SISTEMAMISIONES_API ABateria : public AActor
{
	GENERATED_BODY()

public:
	ABateria();

protected:
	UFUNCTION()
	void AlRecogerBateria(
		UPrimitiveComponent* ComponenteSolapado,
		AActor* OtroActor,
		UPrimitiveComponent* OtroComponente,
		int32 OtroIndiceCuerpo,
		bool bDesdeBarrido,
		const FHitResult& ResultadoBarrido);

	UPROPERTY(VisibleAnywhere, Category = "Bateria")
	TObjectPtr<USphereComponent> ZonaRecoleccion;

	UPROPERTY(VisibleAnywhere, Category = "Bateria")
	TObjectPtr<UStaticMeshComponent> ModeloBateria;

	UPROPERTY(EditInstanceOnly, Category = "Bateria")
	FName IDDestino = TEXT("BateriaEnergia");
};
