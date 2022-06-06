#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

#include "TransformComponent.h"
#include "TextureTransformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BurgerPartComponent.h"
#include "RenderOrder.h"

BurgerComponent::BurgerComponent(TransformComponent* pTransformComponent, const Ingredient& ingredient, const std::string& filename)
	: m_pIngredientParts{}
	, m_pBurgerParts{}
	, m_pTransformComponent{ pTransformComponent }
	, m_pRigidBodyComponent{ nullptr }
	, m_Ingredient{ ingredient }
	, m_SpriteSheet{ filename }
	, m_BurgerAmount{ 4 }
	, m_IsOverlapping{ false }
	, m_IsUpdateNeeded{ true }
{
}

BurgerComponent::~BurgerComponent()
{
	for (GameObject* pObj : m_pIngredientParts)
	{
		delete pObj;
		pObj = nullptr;
	}
}

void BurgerComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		//Create burger
		TransformComponent* pTfcomp = GetGameObject()->AddComponent<TransformComponent>(0.f, 0.f);
		m_pRigidBodyComponent = GetGameObject()->AddComponent<RigidBodyComponent>(pTfcomp, RigidBodyComponent::BodyType::Dynamic, 0.f, 1.f);
		BoxColliderComponent* pBcdComp = GetGameObject()->AddComponent<BoxColliderComponent>(m_pRigidBodyComponent, 4.f, 1.f, 2.f, 0.f, 0.f, static_cast<int>(ColliderComponent::CollisionGroup::Burger));
		pBcdComp->OnTriggerEnter = std::bind(&BurgerComponent::OnTriggerEnter, GetGameObject()->GetComponent<BurgerComponent>(), std::placeholders::_1);
		pBcdComp->OnTriggerExit = std::bind(&BurgerComponent::OnTriggerExit, GetGameObject()->GetComponent<BurgerComponent>(), std::placeholders::_1);

		//Create burger parts
		int width{ 16 };

		for (int idx{}; idx < m_BurgerAmount; ++idx)
		{
			GameObject* pGameObject{ new GameObject{} };
			m_pIngredientParts.emplace_back(pGameObject);

			switch (m_Ingredient)
			{
			case Ingredient::BunBottom:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 16, 16, 16);
				break;
			case Ingredient::BunTop:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 0, 16, 16);
				break;
			case Ingredient::Cheese:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 32, 16, 16);
				break;
			case Ingredient::Lettuce:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 80, 16, 16);
				break;
			case Ingredient::Meat:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 48, 16, 16);
				break;
			case Ingredient::Tomato:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 64, 16, 16);
				break;
			default:
				break;
			}

			TransformComponent* pTfc = pGameObject->AddComponent<TransformComponent>(16.f * idx, 0.f);
			RigidBodyComponent* pRdb = pGameObject->AddComponent<RigidBodyComponent>(pTfc, RigidBodyComponent::BodyType::Kinematic);
			BoxColliderComponent* pBcd = pGameObject->AddComponent<BoxColliderComponent>(pRdb, 0.4f, 0.4f, 0.25f, 0.25f, 0.f, static_cast<int>(ColliderComponent::CollisionGroup::Level));
			pGameObject->AddComponent<RenderComponent>(pTfc, static_cast<int>(RenderOrder::Burger), m_SpriteSheet);
			BurgerPartComponent* pBrp = pGameObject->AddComponent<BurgerPartComponent>();
			pBcd->SetSensor();
			pBcd->OnTriggerEnter = std::bind(&BurgerPartComponent::OnTriggerEnter, pBrp, std::placeholders::_1);

			m_pBurgerParts.emplace_back(pBrp);

			GetGameObject()->AddChild(pGameObject);
		}

		m_IsUpdateNeeded = false;
	}

	for (int idx{}; idx < m_BurgerAmount; ++idx)
	{
		if (!m_pBurgerParts[idx]->IsHit())
		{
			return;
		}

		if (idx + 1 == m_BurgerAmount)
		{
			Dropped(false);
		}
	}
}

void BurgerComponent::Dropped(bool givePoints)
{
	if (givePoints)
	{
		Notify(m_pGameObject, GameEvent::BurgerDropped);
	}

	m_pRigidBodyComponent->UpdateGravityScale(1.f);

	ResetParts();
}

void BurgerComponent::ResetParts()
{
	for (BurgerPartComponent* pComp : m_pBurgerParts)
	{
		pComp->ResetHit();
	}
}

void BurgerComponent::OnTriggerEnter(ColliderComponent* pCollider)
{
	if (BurgerComponent* pComp = pCollider->GetGameObject()->GetComponent<BurgerComponent>())
	{
		m_IsOverlapping = true;
	}
}

void BurgerComponent::OnTriggerExit(ColliderComponent* pCollider)
{
	if (BurgerComponent* pComp = pCollider->GetGameObject()->GetComponent<BurgerComponent>())
	{
		m_IsOverlapping = false;
	}
}