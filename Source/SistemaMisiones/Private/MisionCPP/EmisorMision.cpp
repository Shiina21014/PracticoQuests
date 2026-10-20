#include "MisionCPP/EmisorMision.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MisionCPP/ComponenteMisiones.h"
#include "MisionCPP/MisionDefinicion.h"
#include "UObject/ConstructorHelpers.h"

AEmisorMision::AEmisorMision()
{
	PrimaryActorTick.bCanEverTick = false;

	ZonaInicio = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaInicio"));
	RootComponent = ZonaInicio;
	ZonaInicio->SetBoxExtent(FVector(120.0f, 120.0f, 120.0f));
	ZonaInicio->SetCollisionProfileName(TEXT("Trigger"));
	ZonaInicio->SetGenerateOverlapEvents(true);
	ZonaInicio->OnComponentBeginOverlap.AddDynamic(
		this,
		&AEmisorMision::AlEntrarEnZona);

	ModeloTerminal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloTerminal"));
	ModeloTerminal->SetupAttachment(RootComponent);
	ModeloTerminal->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ModeloTerminal->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.5f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCubo(
		TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MallaCubo.Succeeded())
	{
		ModeloTerminal->SetStaticMesh(MallaCubo.Object);
	}
}

void AEmisorMision::AlEntrarEnZona(
	UPrimitiveComponent* ComponenteSolapado,
	AActor* OtroActor,
	UPrimitiveComponent* OtroComponente,
	int32 OtroIndiceCuerpo,
	bool bDesdeBarrido,
	const FHitResult& ResultadoBarrido)
{
	if (!IsValid(MisionAIniciar) || !IsValid(OtroActor))
	{
		return;
	}

	if (UComponenteMisiones* ComponenteMisiones =
		OtroActor->FindComponentByClass<UComponenteMisiones>())
	{
		ComponenteMisiones->AgregarMision(MisionAIniciar);
	}
}
