#include "SistemaMisionesCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "MisionCPP/ComponenteMisiones.h"
#include "MisionCPP/RastreadorMisiones.h"
#include "SistemaMisiones.h"

ASistemaMisionesCharacter::ASistemaMisionesCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity = 500.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(
        CameraBoom,
        USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    ComponenteMisiones = CreateDefaultSubobject<UComponenteMisiones>(
        TEXT("ComponenteMisiones"));
}

void ASistemaMisionesCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!IsLocallyControlled())
    {
        return;
    }

    RastreadorMisionesCPP = CreateWidget<URastreadorMisiones>(
        GetWorld(),
        URastreadorMisiones::StaticClass());

    if (IsValid(RastreadorMisionesCPP))
    {
        RastreadorMisionesCPP->AddToViewport();
        RastreadorMisionesCPP->VincularComponente(ComponenteMisiones);
    }
}

void ASistemaMisionesCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent =
        Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(
            JumpAction,
            ETriggerEvent::Started,
            this,
            &ACharacter::Jump);

        EnhancedInputComponent->BindAction(
            JumpAction,
            ETriggerEvent::Completed,
            this,
            &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(
            MoveAction,
            ETriggerEvent::Triggered,
            this,
            &ASistemaMisionesCharacter::Move);

        EnhancedInputComponent->BindAction(
            MouseLookAction,
            ETriggerEvent::Triggered,
            this,
            &ASistemaMisionesCharacter::Look);

        EnhancedInputComponent->BindAction(
            LookAction,
            ETriggerEvent::Triggered,
            this,
            &ASistemaMisionesCharacter::Look);
    }
    else
    {
        UE_LOG(
            LogSistemaMisiones,
            Error,
            TEXT("'%s' Failed to find an Enhanced Input component!"),
            *GetNameSafe(this));
    }
}

void ASistemaMisionesCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void ASistemaMisionesCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ASistemaMisionesCharacter::DoMove(float Right, float Forward)
{
    if (GetController() != nullptr)
    {
        const FRotator Rotation = GetController()->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

        const FVector ForwardDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        const FVector RightDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, Forward);
        AddMovementInput(RightDirection, Right);
    }
}

void ASistemaMisionesCharacter::DoLook(float Yaw, float Pitch)
{
    if (GetController() != nullptr)
    {
        AddControllerYawInput(Yaw);
        AddControllerPitchInput(Pitch);
    }
}

void ASistemaMisionesCharacter::DoJumpStart()
{
    Jump();
}

void ASistemaMisionesCharacter::DoJumpEnd()
{
    StopJumping();
}
