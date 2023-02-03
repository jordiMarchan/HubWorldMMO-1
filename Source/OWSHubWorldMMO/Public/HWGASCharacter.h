// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" 
#include "CombatAttributeSet.h" 
#include "HWCharacter.h"
#include "HWPlayerController.h"
#include "HWHUD.h"
#include "HWAbilitySystemComponent.h"
#include "HWGASCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OWSHUBWORLDMMO_API AHWGASCharacter : public AHWCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AHWGASCharacter();

	static FName AbilitySystemComponentName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UHWAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		UCombatAttributeSet* CombatAttributes;

	//Reaction Gameplay Effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction Effects")
		TSubclassOf<class UGameplayEffect> BurningEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction Effects")
		TSubclassOf<class UGameplayEffect> WetEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction Effects")
		TSubclassOf<class UGameplayEffect> ColdEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction Effects")
		TSubclassOf<class UGameplayEffect> ChargedEffect;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return (UAbilitySystemComponent*)AbilitySystem;
	};

	UHWAbilitySystemComponent* GetHWAbilitySystemComponent() const
	{
		return AbilitySystem;
	};

	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void GrantAbility(TSubclassOf<class UGameplayAbility> NewAbility, int AbilityLevel);
	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void GrantAbilityKeyBind(TSubclassOf<class UGameplayAbility> NewAbility, int AbilityLevel, int InputID);

	//Events
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnDeath(AHWGASCharacter* WhoKilledMe);
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnTakeDamage(AHWGASCharacter* WhoAttackedMe, float DamageAmount, bool IsCritical);
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnInflictDamage(AHWGASCharacter* WhoWasDamaged, float DamageAmount, bool IsCritical);
	
	void OnUIRelatedTagsChanged(const FGameplayTag Tag, int32 NewCount);

	//Gameplay Tags
	FGameplayTag NormalAbility1CooldownTag;
	FGameplayTag BurningStateTag;

	FNormalAbility1CooldownBeginDelegate NormalAbility1CooldownBeginDelegate;
	FNormalAbility1CooldownEndDelegate NormalAbility1CooldownEndDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

protected:

	FSimpleMulticastDelegate OnAbilitySystemInitialized;
};
