// RubeusCore.cpp : Defines the entry point for the application.
//
#include "RubeusCore.h"

int main()
{
	using namespace Rubeus;

	using namespace GraphicComponents;
	using namespace AudioComponents;
	using namespace UtilityComponents;

	using namespace RML;

	using namespace Awerere;

	RWindowComponent * GameWindow = new RWindowComponent("Hello World",
														 1280, 720,
														 EWindowParameters::WINDOWED_MODE,
														 EWindowParameters::NON_RESIZABLE_WINDOW,
														 1);

	RSymphony * symphony = new RSymphony();
	symphony->addMusicTrack(1);
	symphony->addSoundTrack(1);
	symphony->loadTrack(AudioComponents::MUSIC_TRACK, AudioComponents::TRACK_0, "Assets/Garage.wav", 10, true);
	symphony->loadTrack(AudioComponents::SOUND_TRACK, AudioComponents::TRACK_0, "Assets/sound.wav", 10);
	symphony->playTrack(AudioComponents::MUSIC_TRACK, AudioComponents::TRACK_0);
	symphony->playTrack(AudioComponents::SOUND_TRACK, AudioComponents::TRACK_0);

	RShaderComponent * shader0 = new RShaderComponent("Shaders/basic.vert", "Shaders/basic.frag");

	RStaticLayer * layer0 = new RStaticLayer(*shader0);

	RGroup * g = new RGroup(Matrix4::translation(Vector3D(0.0f, 0.0f, 0.0f)) * Matrix4::rotation(0, Vector3D(0, 0, 1)));
	RGroup * g2 = new RGroup(Matrix4::translation(Vector3D(0.0f, 0.0f, 0.0f)) * Matrix4::rotation(0, Vector3D(0, 0, 1)));

	RTimer * timer = new RTimer(2);
	timer->setFrameCounter();

	APhysicsMaterial mat;

	std::vector<RGameObject *> gameObjects;

	RGameObject * object1 = new RGameObject(0.0f, 0.0f, 3.0f, 3.0f, "Assets/debug.png", true, EColliderType::BOX, new ABoxCollider(RML::Vector3D(0.0f, 0.0f, 1), RML::Vector3D(3.0f, 3.0f, 1)), true, APhysicsMaterial::DefaultMaterial);

	RGameObject * object2 = new RGameObject(0.0, 6.0f, 3.0f, 3.0f, "Assets/debug.png", true, EColliderType::BOX, new ABoxCollider(RML::Vector3D(0.0f, 6.0f, 1), RML::Vector3D(3.0f, 9.0f, 1)), true, APhysicsMaterial::DefaultMaterial);

	gameObjects.push_back(object1);
	gameObjects.push_back(object2);
	g->add(object1);
	g->add(object2);
	g->add(g2);
	layer0->addGroup(*g);
	layer0->addGroup(*g2);

	shader0->enableShader();
	GLint textureIDs[32];
	for (int i = 0; i < 32; i++)
	{
		textureIDs[i] = i;
	}
	shader0->setUniform1iv("textures", textureIDs, 32);

	ABoxCollider box(Vector3D(3, 3, 0), Vector3D(5, 5, 0));
	ASphereCollider sphere(Vector3D(5.5, 5.5, 0), 1);

	LOG(box.tryIntersect(sphere).getGap());

	RWorld world(gameObjects);

	APhysicsEngine awerere(*GameWindow, world, GameWindow->getHeight() / 9, GameWindow->getWidth() / 16);

	object1->m_PhysicsObject->m_Collider->m_PhysicsMaterial.m_Gravity = RML::Vector2D(0.0f, 0.0f);
	object2->m_PhysicsObject->m_Collider->m_PhysicsMaterial.m_Gravity = RML::Vector2D(0.0f, -1.0f);

	// See if maps are slowing things down. Also have a performance check
	while (!GameWindow->closed())
	{
		// TODO: Message bus needs references to all systems here
		// Clear Window buffer
		GameWindow->clearWindow();

		// Miscellaneous testing stuff
		shader0->enableShader();
		shader0->setUniform2f("light_position", Vector2D(GameWindow->m_X * 16.0f / 1280.0f, (720.0f - GameWindow->m_Y) * 9.0f / 720.0f));

		// Physics engine update
		awerere.update(1.0f / 60.0f);

		// Render update
		layer0->draw();

		// Window buffer update
		GameWindow->updateWindow();

		// Frame counter update
		timer->evaluateFrames();
	}

	delete timer;
	delete g;
	delete g2;
	delete object1;
	delete object2;
	delete layer0;
	delete shader0;
	delete symphony;
	delete GameWindow;

	return 0;
}
