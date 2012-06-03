#include "GameState.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <States/StateStack.h>
#include <Time/Clock.h>

#include <Graphics/GraphicsSystem.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Factories/SpriteFactory.h>
#include <Maths/Matrix4.h>

#include "../../Resources/Entities.h"
#include "../../Resources/States.h"
#include "../../Resources/Textures.h"
#include "../../Resources/VertexBuffers.h"
#include "../../Resources/IndexBuffers.h"
#include "../../Resources/Materials.h"
#include "../../Resources/Transforms.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Shaders.h"
#include "../../Resources/Rooms.h"

#include "../../World/WorldManager.h"
#include "../../World/Floor1/StartingRoom.h"
#include "../../World/Floor1/Floor1RoomA.h"
#include "../../World/Floor1/Floor1RoomB.h"
#include "../../World/Floor1/Floor1RoomC.h"
#include "../../World/Floor1/Floor1RoomD.h"
#include "../../World/Floor1/Floor1RoomE.h"
#include "../../World/Floor1/Floor1RoomF.h"
#include "../../World/Floor1/Floor1RoomG.h"

#include "../../Entities/Player.h"

#include <cstdio>
#include <cmath>

bool gameComplete = false;
bool gameLost = false;

using namespace GLESGAE;

GameState::GameState()
: State(Fingers::States::GameState)
, mWorldManager(0)
{
	loadTextures();
	loadMeshes();
	loadWorld();
}

GameState::~GameState()
{
	unloadTextures();
	unloadMeshes();
}

bool GameState::update(const float delta)
{
	mWorldManager->update(delta);
	mWorldManager->render();
	
	return true;
}

void GameState::loadTextures()
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	
	ResourceBank<Texture>& textureBank(resourceManager->createBank<Texture>(Resources::Texture));
	Fingers::GameTextures::Bank = textureBank.getId();
	Fingers::GameTextures::Group = textureBank.newGroup();
	
	Resource<Texture>& texture(textureBank.add(Fingers::GameTextures::Group, Resources::Texture, new Texture));
	Fingers::GameTextures::RoomTiles = texture.getId();
	texture->loadBMP("data/Textures/tilesheet.bmp");
}

void GameState::unloadTextures()
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	
	resourceManager->removeBank<Texture>(Fingers::GameTextures::Bank, Resources::Texture);
}

void GameState::loadMeshes()
{
	Vector2 scale(0.05F, 0.05F);
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	
	Resource<Texture>& texture(resourceManager->getBank<Texture>(Fingers::GameTextures::Bank, Resources::Texture).get(Fingers::GameTextures::Group, Fingers::GameTextures::RoomTiles));
	
	SpriteFactory::Settings settings;
	settings.mesh.bank = Fingers::Meshes::Bank;
	settings.mesh.group = Fingers::PlayerMeshes::Group;
	
	settings.vertex.bank = Fingers::VertexBuffers::Bank;
	settings.vertex.group = Fingers::VertexBuffers::Group;
	
	settings.index.bank = Fingers::IndexBuffers::Bank;
	settings.index.group = Fingers::IndexBuffers::Group;

	settings.material.bank = Fingers::Materials::Bank;
	settings.material.group = Fingers::Materials::Group;
	
	settings.shader.bank = Fingers::Shaders::Bank;
	settings.shader.group = Fingers::Shaders::Group;

	{ // Player Anims	
		SpriteFactory spriteFactory(texture, settings);
	
		Resources::Locator heart(spriteFactory.create(Vector2(0.0125F, 0.0125F), 133U, 38U, 148U, 53U));
		Fingers::PlayerMeshes::Heart = heart.resource;
	
		Resources::Locator player(spriteFactory.create(scale, 32U, 0U, 63U, 31U));
		Fingers::PlayerMeshes::Frames::Static = player.resource;
		
		Resources::Locator walk1(spriteFactory.create(scale, 0U, 65U, 31U, 96U));
		Fingers::PlayerMeshes::Frames::Walk1 = walk1.resource;
		
		Resources::Locator walk2(spriteFactory.create(scale, 32U, 65U, 63U, 96U));
		Fingers::PlayerMeshes::Frames::Walk2 = walk2.resource;
		
		Resources::Locator hurt(spriteFactory.create(scale, 64U, 65U, 95U, 96U));
		Fingers::PlayerMeshes::Frames::Hurt = hurt.resource;
		
		Resources::Locator death(spriteFactory.create(scale, 96U, 64U, 127U, 95U));
		Fingers::PlayerMeshes::Frames::Death = death.resource;
	}
	
	{ // Room Meshes
		settings.mesh.group = Fingers::RoomMeshes::Group;
		SpriteFactory spriteFactory(texture, settings);
	
		Resources::Locator wall(spriteFactory.create(scale, 32U, 32U, 63U, 63U));
		Fingers::RoomMeshes::Collidables::BlockWall = wall.resource;
		
		Resources::Locator stairs(spriteFactory.create(scale, 0U, 32U, 31U, 63U));
		Fingers::RoomMeshes::Collidables::StairWell = stairs.resource;
	
		Resources::Locator floor(spriteFactory.create(scale, 0U, 0U, 31U, 31U));
		Fingers::RoomMeshes::Background::Floor = floor.resource;
		
		Vector2 doorScale(0.1F, 0.05F);
		Resources::Locator door(spriteFactory.create(doorScale, 96U, 0U, 159U, 31U));
		Fingers::RoomMeshes::Collidables::Door = door.resource;
		
		Resources::Locator exit(spriteFactory.create(doorScale, 192U, 32U, 255U, 63U));
		Fingers::RoomMeshes::Collidables::ExitDoor = exit.resource;
	}
	
	{ // Collectables
		settings.mesh.group = Fingers::CollectableMeshes::Group;
		SpriteFactory spriteFactory(texture, settings);
		
		Resources::Locator gem(spriteFactory.create(scale, 64U, 0U, 95U, 31U));
		Fingers::CollectableMeshes::Gems = gem.resource;
		
		
		Resources::Locator health(spriteFactory.create(scale, 96U, 32U, 127U, 63U));
		Fingers::CollectableMeshes::Health = health.resource;
	}
	
	{ // Pushables
		settings.mesh.group = Fingers::PushableMeshes::Group;
		SpriteFactory spriteFactory(texture, settings);
		
		Resources::Locator weight(spriteFactory.create(scale, 2U, 233U, 25U, 255U));
		Fingers::PushableMeshes::Weight = weight.resource;
		
		Resources::Locator diamond(spriteFactory.create(scale, 64U, 32U, 95U, 63U));
		Fingers::PushableMeshes::StarDiamond = diamond.resource;
	}
	
	{ // "fonts"
		settings.mesh.group = Fingers::FontMeshes::Group;
		SpriteFactory spriteFactory(texture, settings);
		
		Vector2 banner(0.25F, 0.15F);
		Resources::Locator winner(spriteFactory.create(banner, 128U, 102U, 255U, 140U));
		Fingers::FontMeshes::Complete = winner.resource;
		
		Resources::Locator loser(spriteFactory.create(banner, 128U, 64U, 255U, 101U));
		Fingers::FontMeshes::Lost = loser.resource;
	}
	
	{ // It's a Trap!
		settings.mesh.group = Fingers::TrapMeshes::Group;
		SpriteFactory spriteFactory(texture, settings);
		
		Vector2 floorTrap(0.1F, 0.1F);
		Resources::Locator trapDoorClosed(spriteFactory.create(floorTrap, 31U, 203U, 77U, 249U));
		Fingers::TrapMeshes::TrapDoorClosed = trapDoorClosed.resource;
		
		Resources::Locator trapDoorOpen(spriteFactory.create(floorTrap, 81U, 203U, 127U, 249U));
		Fingers::TrapMeshes::TrapDoorOpen = trapDoorOpen.resource;
		
		Resources::Locator pressurePadDown(spriteFactory.create(floorTrap, 131U, 203U, 177U, 249U));
		Fingers::TrapMeshes::PressurePadDown = pressurePadDown.resource;
		
		Resources::Locator pressurePadUp(spriteFactory.create(floorTrap, 180U, 203U, 227U, 249U));
		Fingers::TrapMeshes::PressurePadUp = pressurePadUp.resource;
		
		Resources::Locator spikesDown(spriteFactory.create(floorTrap, 131U, 155U, 177U, 201U));
		Fingers::TrapMeshes::SpikesDown = spikesDown.resource;
		
		Resources::Locator spikesUp(spriteFactory.create(floorTrap, 180U, 155U, 227U, 201U));
		Fingers::TrapMeshes::SpikesUp = spikesUp.resource;
		
		Resources::Locator cameraBox(spriteFactory.create(Vector2(0.025F, 0.025F), 1U, 195U, 10U, 210U));
		Fingers::TrapMeshes::CameraBox = cameraBox.resource;
		
		Resources::Locator cameraSight(spriteFactory.create(Vector2(0.15F, 0.15F), 0U, 96U, 95U, 192U));
		Fingers::TrapMeshes::CameraSight = cameraSight.resource;
		
		Resources::Locator arrowBox(spriteFactory.create(Vector2(0.025F, 0.025F), 1U, 221U, 12U, 231U));
		Fingers::TrapMeshes::ArrowBox = arrowBox.resource;
		
		Resources::Locator arrow(spriteFactory.create(Vector2(0.0125F ,0.05F), 17U, 197U, 25U, 231U));
		Fingers::TrapMeshes::Arrow = arrow.resource;
		
		Resources::Locator movableWall(spriteFactory.create(scale, 224U, 0U, 255U, 31U));
		Fingers::TrapMeshes::MovableWall = movableWall.resource;
		
		Resources::Locator crusherHead(spriteFactory.create(Vector2(0.075F, 0.025F), 160U, 20U, 223U, 31U));
		Fingers::TrapMeshes::CrusherHead = crusherHead.resource;
		
		Resources::Locator crusherArm(spriteFactory.create(Vector2(0.025F, 0.025F), 185U, 0U, 197U, 19U));
		Fingers::TrapMeshes::CrusherArm = crusherArm.resource;
	}
}

void GameState::unloadMeshes()
{
}

void GameState::loadWorld()
{
	Application* application(Application::getInstance());
	ResourceManager* resourceManager(application->getResourceManager());
	mWorldManager = new WorldManager(3U);
	
	ResourceBank<Entity>& entityBank(resourceManager->createBank<Entity>(Fingers::Entities::Type));
	Fingers::Entities::Bank = entityBank.getId();
	Fingers::Entities::Group = entityBank.newGroup();
	
	ResourceBank<Room>& roomBank(resourceManager->createBank<Room>(Fingers::Rooms::Type));
	Fingers::Rooms::Bank = roomBank.getId();
	Fingers::Rooms::Floor1::Group = roomBank.newGroup();
	Fingers::Rooms::Floor2::Group = roomBank.newGroup();
	Fingers::Rooms::Floor3::Group = roomBank.newGroup();
	
	Resource<Room>& floor1StartingRoom(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new StartingRoom));
	Resource<Room>& floor1RoomA(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomA));
	Resource<Room>& floor1RoomB(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomB));
	Resource<Room>& floor1RoomC(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomC));
	Resource<Room>& floor1RoomD(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomD));
	Resource<Room>& floor1RoomE(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomE));
	Resource<Room>& floor1RoomF(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomF));
	Resource<Room>& floor1RoomG(roomBank.add(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Type, new Floor1RoomG));
	Fingers::Rooms::Floor1::StartingRoom = floor1StartingRoom.getId();
	Fingers::Rooms::Floor1::RoomA = floor1RoomA.getId();
	Fingers::Rooms::Floor1::RoomB = floor1RoomB.getId();
	Fingers::Rooms::Floor1::RoomC = floor1RoomC.getId();
	Fingers::Rooms::Floor1::RoomD = floor1RoomD.getId();
	Fingers::Rooms::Floor1::RoomE = floor1RoomE.getId();
	Fingers::Rooms::Floor1::RoomF = floor1RoomF.getId();
	Fingers::Rooms::Floor1::RoomG = floor1RoomG.getId();
	mWorldManager->addRoom(floor1StartingRoom);
	mWorldManager->addRoom(floor1RoomA);
	mWorldManager->addRoom(floor1RoomB);
	mWorldManager->addRoom(floor1RoomC);
	mWorldManager->addRoom(floor1RoomD);
	mWorldManager->addRoom(floor1RoomE);
	mWorldManager->addRoom(floor1RoomF);
	mWorldManager->addRoom(floor1RoomG);
	
	Resources::Locator playerStatic;
	playerStatic.bank = Fingers::Meshes::Bank;
	playerStatic.group = Fingers::PlayerMeshes::Group;
	playerStatic.resource = Fingers::PlayerMeshes::Frames::Static;
	
	Resource<Entity>& playerEntity(entityBank.add(Fingers::Entities::Group, Fingers::Entities::Type, new Player(playerStatic)));
	
	floor1StartingRoom->addEntity(playerEntity);
	floor1StartingRoom->setVisible(true);
}


