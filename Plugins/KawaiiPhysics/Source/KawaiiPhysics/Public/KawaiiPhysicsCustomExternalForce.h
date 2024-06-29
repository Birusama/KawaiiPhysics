﻿#pragma once
#include "AnimNode_KawaiiPhysics.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "KawaiiPhysicsCustomExternalForce.generated.h"


UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class KAWAIIPHYSICS_API UKawaiiPhysics_CustomExternalForce : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayPriority=1))
	bool bIsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayPriority=1))
	bool bDrawDebug = false;

public:
	UFUNCTION(BlueprintNativeEvent)
	void PreApply(UPARAM(ref) FAnimNode_KawaiiPhysics& Node,
	              const USkeletalMeshComponent* SkelComp);

	virtual void PreApply_Implementation(
		UPARAM(ref) FAnimNode_KawaiiPhysics& Node, const USkeletalMeshComponent* SkelComp)PURE_VIRTUAL(,);

	UFUNCTION(BlueprintNativeEvent)
	bool Apply(int32 ModifyBoneIndex, UPARAM(ref) FAnimNode_KawaiiPhysics& Node,
	           const USkeletalMeshComponent* SkelComp);

	virtual bool Apply_Implementation(int32 ModifyBoneIndex,
	                                  UPARAM(ref) FAnimNode_KawaiiPhysics& Node, const USkeletalMeshComponent* SkelComp)
	{
		return false;
	}

	UFUNCTION(BlueprintCallable)
	virtual bool IsDebugEnabled()
	{
		if (const auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("a.AnimNode.KawaiiPhysics.Debug")))
		{
			return CVar->GetBool() && bDrawDebug;
		}
		return false;
	}

#if ENABLE_ANIM_DEBUG
	virtual void AnimDrawDebug(
		const FKawaiiPhysicsModifyBone& ModifyBone, const FAnimNode_KawaiiPhysics& Node,
		const FComponentSpacePoseContext& PoseContext)
	{
	}
#endif

#if WITH_EDITOR
	virtual void AnimDrawDebugForEditMode(const FKawaiiPhysicsModifyBone& ModifyBone,
	                                      const FAnimNode_KawaiiPhysics& Node, FPrimitiveDrawInterface* PDI)
	{
	}
#endif
};

UCLASS(DisplayName = "Gravity")
class KAWAIIPHYSICS_API UKawaiiPhysics_CustomExternalForce_Gravity : public UKawaiiPhysics_CustomExternalForce
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault))
	float GravityScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseCharacterGravity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (PinHiddenByDefault, editcondition = "bOverrideGravityDirection"))
	FVector OverrideGravityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bOverrideGravityDirection = false;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, AdvancedDisplay)
	float DebugArrowLength = 10.0f;
	UPROPERTY(EditDefaultsOnly, AdvancedDisplay)
	float DebugArrowSize = 1.0f;
	UPROPERTY(EditDefaultsOnly, AdvancedDisplay)
	FVector DebugArrowOffset;
#endif

private:
	FVector Gravity;

public:
	virtual void
	PreApply_Implementation(FAnimNode_KawaiiPhysics& Node, const USkeletalMeshComponent* SkelComp) override;

	virtual bool
	Apply_Implementation(int32 ModifyBoneIndex,UPARAM(ref) FAnimNode_KawaiiPhysics& Node,
	                     const USkeletalMeshComponent* SkelComp) override;

#if ENABLE_ANIM_DEBUG
	virtual void AnimDrawDebug(const FKawaiiPhysicsModifyBone& ModifyBone, const FAnimNode_KawaiiPhysics& Node,
	                           const FComponentSpacePoseContext& PoseContext) override;
#endif

#if WITH_EDITOR
	virtual void
	AnimDrawDebugForEditMode(const FKawaiiPhysicsModifyBone& ModifyBone, const FAnimNode_KawaiiPhysics& Node,
	                         FPrimitiveDrawInterface* PDI) override;
#endif
};

UCLASS(DisplayName = "Curve")
class KAWAIIPHYSICS_API UKawaiiPhysics_CustomExternalForce_Curve : public UKawaiiPhysics_CustomExternalForce
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault))
	FVector ForceScale = FVector::OneVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault))
	float TimeScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (PinHiddenByDefault, XAxisName="Time", YAxisName="Force"))
	FRuntimeVectorCurve ForceCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (PinHiddenByDefault, XAxisName="LengthRate", YAxisName="ForceRate"))
	FRuntimeFloatCurve ForceRateCurve;


#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly)
	float DebugArrowLength = 5.0f;
	UPROPERTY(EditDefaultsOnly)
	float DebugArrowSize = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	FVector DebugArrowOffset;
#endif

	UPROPERTY(VisibleAnywhere)
	float Time;

private:


public:
	virtual void
	PreApply_Implementation(FAnimNode_KawaiiPhysics& Node, const USkeletalMeshComponent* SkelComp) override;

	virtual bool
	Apply_Implementation(int32 ModifyBoneIndex,UPARAM(ref) FAnimNode_KawaiiPhysics& Node,
	                     const USkeletalMeshComponent* SkelComp) override;

#if ENABLE_ANIM_DEBUG
	virtual void AnimDrawDebug(const FKawaiiPhysicsModifyBone& ModifyBone, const FAnimNode_KawaiiPhysics& Node,
	                           const FComponentSpacePoseContext& PoseContext) override;
#endif

#if WITH_EDITOR
	virtual void
	AnimDrawDebugForEditMode(const FKawaiiPhysicsModifyBone& ModifyBone, const FAnimNode_KawaiiPhysics& Node,
	                         FPrimitiveDrawInterface* PDI) override;
#endif
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0 // Test Instanced Struct
USTRUCT(BlueprintType)
struct KAWAIIPHYSICS_API FKawaiiPhysics_CustomExternalForce
{
	GENERATED_BODY()

public:
	virtual ~FKawaiiPhysics_CustomExternalForce() = default;

	virtual void Apply(FAnimNode_KawaiiPhysics& Node, const FComponentSpacePoseContext& PoseContext)
	{
	};

	virtual bool IsDebugEnabled()
	{
		if (const auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("a.AnimNode.KawaiiPhysics.Debug")))
		{
			return CVar->GetBool();
		}
		return false;
	}
};

USTRUCT(BlueprintType, DisplayName = "Gravity")
struct KAWAIIPHYSICS_API FKawaiiPhysics_CustomExternalForce_Gravity : public FKawaiiPhysics_CustomExternalForce
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GravityScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (PinHiddenByDefault, editcondition = "bOverrideGravityDirection"))
	FVector OverrideGravityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	uint8 bOverrideGravityDirection : 1;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly)
	float DebugArrowLength = 20.0f;
	UPROPERTY(EditDefaultsOnly)
	float DebugArrowSize = 20.0f;
	UPROPERTY(EditDefaultsOnly)
	FVector DebugArrowOffset;
#endif

public:
	virtual void Apply(FAnimNode_KawaiiPhysics& Node, const FComponentSpacePoseContext& PoseContext) override
	{
		const USkeletalMeshComponent* SkelComp = PoseContext.AnimInstanceProxy->GetSkelMeshComponent();
		FVector Gravity = bOverrideGravityDirection ? OverrideGravityDirection : FVector(0, 0, -1.0f);

		if (!bOverrideGravityDirection)
		{
			// For Character's Custom Gravity Direction
			if (const ACharacter* Character = Cast<ACharacter>(SkelComp->GetOwner()))
			{
				Gravity = Character->GetGravityDirection();

				if (const UCharacterMovementComponent* CharacterMovementComponent = Character->
					GetCharacterMovement())
				{
					Gravity *= CharacterMovementComponent->GetGravityZ();
				}
			}
		}
		Gravity *= GravityScale;

		const FTransform ComponentTransform = SkelComp->GetComponentTransform();
		Gravity = ComponentTransform.InverseTransformVector(Gravity);
		for (FKawaiiPhysicsModifyBone& Bone : Node.ModifyBones)
		{
			if (Bone.bSkipSimulate)
			{
				continue;
			}

			Bone.Location += 0.5 * Gravity * Node.DeltaTime * Node.DeltaTime;
		}

#if ENABLE_ANIM_DEBUG
		if (IsDebugEnabled())
		{
			const auto AnimInstanceProxy = PoseContext.AnimInstanceProxy;
			const FVector ModifyRootBoneLocationWS = AnimInstanceProxy->GetComponentTransform().TransformPosition(
				Node.ModifyBones[0].Location);

			AnimInstanceProxy->AnimDrawDebugDirectionalArrow(
				ModifyRootBoneLocationWS + DebugArrowOffset,
				ModifyRootBoneLocationWS + DebugArrowOffset + Gravity.GetSafeNormal() * DebugArrowLength,
				DebugArrowSize, FColor::Red, false, 0.f, 2);
		}
#endif
	}
};
#endif
