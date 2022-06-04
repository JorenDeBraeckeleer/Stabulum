#include "StabulumPCH.h"
#include "TriggerComponent.h"

void TriggerComponent::Update()
{
}

void TriggerComponent::OnTriggerEnter(ColliderComponent*)
{
	std::cout << "Test." << std::endl;
}