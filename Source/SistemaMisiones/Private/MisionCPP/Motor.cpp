#include "MisionCPP/Motor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MisionCPP/ComponenteMisiones.h"
#include "MisionCPP/EstadoMisiones.h"
#include "MisionCPP/MisionTipos.h"
#include "UObject/ConstructorHelpers.h"

AMotor::AMotor()
{
	PrimaryActorTick.bCanEverTick = false;

	ZonaMotor = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaMotor"));
	RootComponent = ZonaMotor;
	ZonaMotor->SetBoxExtent(FVector(140.0f, 140.0f, 120.0f));
	ZonaMotor->SetCollisionProfileName(TEXT("Trigger"));
	ZonaMotor->SetGenerateOverlapEvents(true);
	ZonaMotor->OnComponentBeginOverlap.AddDynamic(
		this,
		&AMotor::AlEntrarEnZonaMotor);

	ModeloMotor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloMotor"));
	ModeloMotor->SetupAttachment(RootComponent);
	ModeloMotor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ModeloMotor->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.2f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCubo(
		TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MallaCubo.Succeeded())
	{
		ModeloMotor->SetStaticMesh(MallaCubo.Object);
	}
}

void AMotor::AlEntrarEnZonaMotor(
	UPrimitiveComponent* ComponenteSolapado,
	AActor* OtroActor,
	UPrimitiveComponent* OtroComponente,
	int32 OtroIndiceCuerpo,
	bool bDesdeBarrido,
	const FHitResult& ResultadoBarrido)
{
	if (!IsValid(OtroActor))
	{
		return;
	}

	UComponenteMisiones* ComponenteMisiones =
		OtroActor->FindComponentByClass<UComponenteMisiones>();

	if (ComponenteMisiones == nullptr ||
		!ComponenteMisiones->EstaMisionCompletada(IDMisionRequerida))
	{
		return;
	}

	if (AEstadoMisiones* EstadoMisiones =
		GetWorld()->GetGameState<AEstadoMisiones>())
	{
		EstadoMisiones->ReportarEventoObjetivo(
			ETipoObjetivoMision::Interactuar,
			IDDestino,
			1);
	}
}

