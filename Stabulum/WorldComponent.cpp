#include "StabulumPCH.h"
#include "WorldComponent.h"

#include "b2_world.h"
#include "b2_body.h"
#include "b2_contact.h"
#include "b2_polygon_shape.h"
#include "b2_circle_shape.h"
#include "b2_fixture.h"

#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "ContactListener.h"
#include "RigidBodyComponent.h"
#include "TimeManager.h"
#include "TransformComponent.h"

WorldComponent::WorldComponent()
	: BaseComponent()
	, m_pWorld{ new b2World{ b2Vec2{ 0.f, 9.81f } } }
	, m_pContactListener{ new ContactListener{} }
	, m_pRigidBodyComponents{}
{
	m_pWorld->SetContactListener(m_pContactListener);
}

WorldComponent::~WorldComponent()
{
	delete m_pContactListener;
	m_pContactListener = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;
}

void WorldComponent::Update()
{
}

void WorldComponent::FixedUpdate()
{
	m_pContactListener->ResetContacts();

	m_pWorld->Step(TimeManager::FixedTimeStep, 5, 2);

	for (RigidBodyComponent* pComp : m_pRigidBodyComponents)
	{
		pComp->UpdatePosition();
	}

	for (ContactListener::Contact& contact : m_pContactListener->GetContacts())
	{
		switch (contact.Type)
		{
		case ContactListener::Contact::Type::OnSensorBegin:
			//std::cout << "OnSensorBegin" << std::endl;
			break;
		case ContactListener::Contact::Type::OnSensorEnd:
			//std::cout << "OnSensorEnd" << std::endl;
			break;
		case ContactListener::Contact::Type::OnCollisionBegin:
			//std::cout << "OnCollisionBegin" << std::endl;
			break;
		case ContactListener::Contact::Type::OnCollisionEnd:
			//std::cout << "OnCollisionEnd" << std::endl;
			break;
		default:
			break;
		}
	}
}

void WorldComponent::AddBody(TransformComponent* pTransformComponent, RigidBodyComponent* pRigidBodyComponent)
{
	m_pRigidBodyComponents.emplace_back(pRigidBodyComponent);

	b2BodyDef bodyDefinition{};
	bodyDefinition.position.Set(pTransformComponent->GetWorldPosition(false).x, pTransformComponent->GetWorldPosition(false).y);
	bodyDefinition.angle = pRigidBodyComponent->GetAngle();
	bodyDefinition.linearVelocity.Set(pRigidBodyComponent->GetLinearVelocity().x, pRigidBodyComponent->GetLinearVelocity().y);
	bodyDefinition.angularVelocity = pRigidBodyComponent->GetAngularVelocity();
	bodyDefinition.linearDamping = pRigidBodyComponent->GetLinearDamping();
	bodyDefinition.angularDamping = pRigidBodyComponent->GetAngularDamping();
	bodyDefinition.allowSleep = pRigidBodyComponent->GetAllowSleep();
	bodyDefinition.awake = pRigidBodyComponent->GetIsAwake();
	bodyDefinition.fixedRotation = pRigidBodyComponent->GetHasFixedRotation();
	bodyDefinition.bullet = pRigidBodyComponent->GetIsBullet();
	bodyDefinition.type = b2BodyType(pRigidBodyComponent->GetBodyType());
	bodyDefinition.enabled = pRigidBodyComponent->GetIsEnabled();
	bodyDefinition.userData.pointer = reinterpret_cast<uintptr_t>(pRigidBodyComponent);
	bodyDefinition.gravityScale = pRigidBodyComponent->GetGravityScale();

	b2Body* body{ m_pWorld->CreateBody(&bodyDefinition) };

	pRigidBodyComponent->SetPhysicsBody(body);
}

void WorldComponent::RemoveBody(RigidBodyComponent* pRigidBodyComponent)
{
	m_pWorld->DestroyBody(pRigidBodyComponent->GetPhysicsBody());

	m_pRigidBodyComponents.erase(std::remove(m_pRigidBodyComponents.begin(), m_pRigidBodyComponents.end(), pRigidBodyComponent));
}

void WorldComponent::AddToBodyColliderBox(RigidBodyComponent* pRigidBodyComponent, BoxColliderComponent* pBoxColliderComponent, int16 groupIndex)
{
	b2PolygonShape boxShape{};
	boxShape.SetAsBox(pBoxColliderComponent->GetWidth() / 2.f, pBoxColliderComponent->GetHeight() / 2.f, GetVecb2(pBoxColliderComponent->GetCenter()), pBoxColliderComponent->GetAngle());

	AddToBodyCollider(boxShape, pRigidBodyComponent, pBoxColliderComponent, groupIndex);
}

void WorldComponent::AddToBodyColliderCircle(RigidBodyComponent* pRigidBodyComponent, CircleColliderComponent* pCircleColliderComponent, int16 groupIndex)
{
	b2CircleShape circleShape{};
	circleShape.m_radius = pCircleColliderComponent->GetRadius();
	circleShape.m_p = GetVecb2(pCircleColliderComponent->GetPoint());

	AddToBodyCollider(circleShape, pRigidBodyComponent, pCircleColliderComponent, groupIndex);
}

void WorldComponent::AddToBodyCollider(const b2Shape& shape, RigidBodyComponent* pRigidBodyComponent, ColliderComponent* pColliderComponent, int16 groupIndex)
{
	b2FixtureDef fixtureDefinition{};
	fixtureDefinition.shape = &shape;
	fixtureDefinition.friction = pColliderComponent->GetFriction();
	fixtureDefinition.restitution = pColliderComponent->GetRestitution();
	fixtureDefinition.restitutionThreshold = pColliderComponent->GetRestitutionTreshold();
	fixtureDefinition.density = pColliderComponent->GetDensity();
	fixtureDefinition.isSensor = pColliderComponent->GetIsSensor();
	fixtureDefinition.userData.pointer = reinterpret_cast<uintptr_t>(pColliderComponent);

	b2Fixture* fixture{ pRigidBodyComponent->GetPhysicsBody()->CreateFixture(&fixtureDefinition) };
	
	b2Filter filter{};
	filter.groupIndex = groupIndex;
	filter.categoryBits = groupIndex;
	filter.maskBits = groupIndex;
	fixture->SetFilterData(filter);

	pColliderComponent->SetPhysicsFixture(fixture);
}