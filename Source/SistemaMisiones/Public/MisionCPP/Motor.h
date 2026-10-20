#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Motor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

UCLASS()
class SISTEMAMISIONES_API AMotor : public AActor
{
	GENERATED_BODY()

public:
	AMotor();

protected:
	UFUNCTION()
	void AlEntrarEnZonaMotor(
		UPrimitiveComponent* ComponenteSolapado,
		AActor* OtroActor,
		UPrimitiveComponent* OtroComponente,
		int32 OtroIndiceCuerpo,
		bool bDesdeBarrido,
		const FHitResult& ResultadoBarrido);

	UPROPERTY(VisibleAnywhere, Category = "Motor")
	TObjectPtr<UBoxComponent> ZonaMotor;

	UPROPERTY(VisibleAnywhere, Category = "Motor")
	TObjectPtr<UStaticMeshComponent> ModeloMotor;

	UPROPERTY(EditInstanceOnly, Category = "Motor")
	FName IDMisionRequerida = TEXT("Mision_RecuperarBaterias");

	UPROPERTY(EditInstanceOnly, Category = "Motor")
	FName IDDestino = TEXT("MotorEmergencia");
};
