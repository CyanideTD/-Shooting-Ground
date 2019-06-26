// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIOwner = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIOwner->GetPawn();
    UPatrolRoute* PatrolComp = ControlledPawn->FindComponentByClass<UPatrolRoute>();

    if (!ensure(PatrolComp))
    {
        UE_LOG(LogTemp, Error, TEXT("does not have patrol component"))
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

    int32 Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    TArray<AActor*>* target_points = PatrolComp->GetPatrolPoint();
    
    if (target_points->Num() == 0)
    {
		UE_LOG(LogTemp, Warning, TEXT("does not have patrol points"))
		return EBTNodeResult::Succeeded;
    }
    
    BlackBoardComp->SetValueAsObject(NextWayPoint.SelectedKeyName, target_points->operator[](Index));
    BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % target_points->Num());
    return EBTNodeResult::Succeeded;
}