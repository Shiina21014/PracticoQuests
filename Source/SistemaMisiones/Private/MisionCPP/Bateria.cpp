#include "MisionCPP/Bateria.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MisionCPP/ComponenteMisiones.h"
#include "MisionCPP/EstadoMisiones.h"
#include "MisionCPP/MisionTipos.h"
#include "UObject/ConstructorHelpers.h"

ABateria::ABateria()
{
	PrimaryActorTick.bCanEverTick = false;

	ZonaRecoleccion = CreateDefaultSubobject<USphereComponent>(TEXT("ZonaRecoleccion"));
	RootComponent = ZonaRecoleccion;
	ZonaRecoleccion->SetSphereRadius(90.0f);
	ZonaRecoleccion->SetCollisionProfileName(TEXT("Trigger"));
	ZonaRecoleccion->SetGenerateOverlapEvents(true);
	ZonaRecoleccion->OnComponentBeginOverlap.AddDynamic(
		this,
		&ABateria::AlRecogerBateria);

	ModeloBateria = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloBateria"));
	ModeloBateria->SetupAttachment(RootComponent);
	ModeloBateria->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ModeloBateria->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.7f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCilindro(
		TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

	if (MallaCilindro.Succeeded())
	{
		ModeloBateria->SetStaticMesh(MallaCilindro.Object);
	}
}

void ABateria::AlRecogerBateria(
	UPrimitiveComponent* ComponenteSolapado,
	AActor* OtroActor,
	UPrimitiveComponent* OtroComponente,
	int32 OtroIndiceCuerpo,
	bool bDesdeBarrido,
	const FHitResult& ResultadoBarrido)
{
	if (!IsValid(OtroActor) ||
		OtroActor->FindComponentByClass<UComponenteMisiones>() == nullptr)
	{
		return;
	}

	if (AEstadoMisiones* EstadoMisiones =
		GetWorld()->GetGameState<AEstadoMisiones>())
	{
		EstadoMisiones->ReportarEventoObjetivo(
			ETipoObjetivoMision::Recolectar,
			IDDestino,
			1);

		Destroy();
	}
}

