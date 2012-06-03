#include "IntroState.h"

#include <Box2D/Box2D.h>
#include <Platform/Application.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/State/GLES1/GLES1State.h>
#include <Graphics/Camera.h>
#include <Factories/SpriteFactory.h>
#include <Utils/HashString.h>
#include <Utils/Sprite.h>

using namespace GLESGAE;

static float sTimeStep = 1.0F / 60.0F;
static Resource<Sprite> sQuirk;
static Resource<GraphicsSystem> sGraphicsSystem;
static Resource<Camera> sCamera;

IntroState::IntroState()
: State(HashString("IntroState"))
, mWorld(0)
, mBody(0)
, m_wheel1(0)
, m_wheel2(0)
, m_spring1(0)
, m_spring2(0)
{
	b2Vec2 gravity(0.0F, -10.0F);
	mWorld = new b2World(gravity);
	
	b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = mWorld->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&fd);

			float32 hs[10] = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

			float32 x = 20.0f, y1 = 0.0f, dx = 5.0f;

			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = hs[i];
				shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}

			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = hs[i];
				shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}

			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 80.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 40.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 10.0f, 5.0f));
			ground->CreateFixture(&fd);

			x += 20.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 40.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x, 20.0f));
			ground->CreateFixture(&fd);
		}
	
	// Car
		{
			b2PolygonShape chassis;
			b2Vec2 vertices[8];
			vertices[0].Set(-1.5f, -0.5f);
			vertices[1].Set(1.5f, -0.5f);
			vertices[2].Set(1.5f, 0.0f);
			vertices[3].Set(0.0f, 0.9f);
			vertices[4].Set(-1.15f, 0.9f);
			vertices[5].Set(-1.5f, 0.2f);
			chassis.Set(vertices, 6);

			b2CircleShape circle;
			circle.m_radius = 0.4f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f, 1.0f);
			mBody = mWorld->CreateBody(&bd);
			mBody->CreateFixture(&chassis, 1.0f);

			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.9f;

			bd.position.Set(-1.0f, 0.35f);
			m_wheel1 = mWorld->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(1.0f, 0.4f);
			m_wheel2 = mWorld->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			jd.Initialize(mBody, m_wheel1, m_wheel1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = true;
			jd.frequencyHz = 4.0F;
			jd.dampingRatio = 0.7F;
			m_spring1 = reinterpret_cast<b2WheelJoint*>(mWorld->CreateJoint(&jd));

			jd.Initialize(mBody, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 10.0f;
			jd.enableMotor = false;
			jd.frequencyHz = 4.0F;
			jd.dampingRatio = 0.7F;
			m_spring2 = reinterpret_cast<b2WheelJoint*>(mWorld->CreateJoint(&jd));
		}
	
	Resource<Texture> sprites(new Texture);
	sprites->loadBMP("data/sprites/testsheet.bmp");
	SpriteFactory spriteFactory(sprites);
	
	sQuirk = spriteFactory.create(Vector2(32.0F, 32.0F), 15U, 0U, 0U, 16U);
	Application* application(Application::getInstance());
	sGraphicsSystem = application->getGraphicsSystem();
	
	sCamera = Resource<Camera>(new Camera(Camera::CAMERA_2D));
	sCamera->set2dParams(0.0F, 0.0F, 640.0F, 480.0F);
	sCamera->getTransformMatrix().setPosition(Vector3(0.0F, 0.0F, -10.0F));
	sCamera->update();
	sGraphicsSystem->getCurrentContext()->getRenderState().recast<GLES1State>()->setVertexPositionsEnabled(true);
	sGraphicsSystem->getCurrentContext()->getRenderState().recast<GLES1State>()->setTexturingEnabled(true);
	sGraphicsSystem->getCurrentContext()->getRenderState().recast<GLES1State>()->setAlphaBlendingEnabled(true);
	sGraphicsSystem->getCurrentContext()->getRenderState().recast<GLES1State>()->setBlendingFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	sGraphicsSystem->getCurrentContext()->getRenderState()->setCamera(sCamera);
}

bool IntroState::update(const float /*deltaTime*/)
{
	mWorld->Step(sTimeStep, 6, 2);
	
	b2Vec2 position(mBody->GetPosition());
	float angle(mBody->GetAngle());
	
	sQuirk->setPosition(Vector2(position.x, position.y));
	sQuirk->setRotation(angle);
	
	m_spring1->SetMotorSpeed(1.0F);
	
	sCamera->getTransformMatrix().setPosition(Vector3(-320.0F + position.x, -240.0F + position.y, -10.0F));
	sCamera->update();
	sGraphicsSystem->getCurrentContext()->getRenderState()->setCamera(sCamera);
	
	sGraphicsSystem->getCurrentContext()->drawMesh(sQuirk->getMesh(), sQuirk->getTransform());
	sGraphicsSystem->getCurrentContext()->refresh();
	
	return true;
}

IntroState::~IntroState()
{
	delete mWorld;
}

