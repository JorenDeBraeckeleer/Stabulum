#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

#include "TransformComponent.h"
#include "TextureTransformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BurgerPartComponent.h"

BurgerComponent::BurgerComponent(TransformComponent* pTransformComponent, const Ingredient& ingredient, const std::string& filename)
	: m_pIngredientParts{}
	, m_pBurgerParts{}
	, m_pTransformComponent{ pTransformComponent }
	, m_Ingredient{ ingredient }
	, m_SpriteSheet{ filename }
	, m_BurgerAmount{ 4 }
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
			//RigidBodyComponent* pRdb = pGameObject->AddComponent<RigidBodyComponent>(pTfc, RigidBodyComponent::BodyType::Dynamic, 0.f, 1.f);
			RigidBodyComponent* pRdb = pGameObject->AddComponent<RigidBodyComponent>(pTfc, RigidBodyComponent::BodyType::Dynamic);
			BoxColliderComponent* pBcd = pGameObject->AddComponent<BoxColliderComponent>(pRdb, 0.5f, 0.5f, 0.25f, 0.25f);
			pGameObject->AddComponent<RenderComponent>(pTfc, m_SpriteSheet);
			BurgerPartComponent* pBrP = pGameObject->AddComponent<BurgerPartComponent>();
			pBcd->SetSensor();
			pBcd->OnTriggerEnter = std::bind(&BurgerPartComponent::OnTriggerEnter, pBrP, std::placeholders::_1);

			m_pBurgerParts.emplace_back(pBrP);

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
			std::cout << "Fall!" << std::endl;

			//Fall down...

			ResetParts();
		}
	}
}

void BurgerComponent::Dropped()
{
	Notify(m_pGameObject, GameEvent::BurgerDropped);
}

void BurgerComponent::ResetParts()
{
	for (BurgerPartComponent* pComp : m_pBurgerParts)
	{
		pComp->ResetHit();
	}
}