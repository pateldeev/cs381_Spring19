#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <Entity381.h>
#include <Utils.h>

#include <OGRE/OgreRenderWindow.h>

InputMgr::InputMgr(Engine *engine) :
	Mgr(engine) {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = 0;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 8.f;
	this->cameraNode = 0;
	this->cameraFollowing = 0;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init() {
	OIS::ParamList pl;
	size_t windowHandle = 0;
	std::ostringstream windowHandleStr;

	engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleStr << windowHandle;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, true));

	int left, top;
	unsigned int width, height, depth;

	engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

}

void InputMgr::Stop() {
	if (mInputMgr) {
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
	}
}

void InputMgr::Tick(float dt) {
	//Must capture both every tick for buffered input to work
	mMouse->capture();
	mKeyboard->capture();
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q))
		engine->keepRunning = false;

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);
}

void InputMgr::UpdateCamera(float dt) {
	const float move = 400.0f;
	const float rotate = 0.05f;

	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (mKeyboard->isKeyDown(OIS::KC_W)) {
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->pitch(Ogre::Degree(5 * rotate));
		else
			dirVec.z -= move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_S)) {
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->pitch(Ogre::Degree(-5 * rotate));
		else
			dirVec.z += move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_E)) {
		dirVec.y += move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_F)) {
		dirVec.y -= move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_A)) {
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->yaw(Ogre::Degree(5 * rotate));
		else
			dirVec.x -= move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_D)) {
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			cameraNode->yaw(Ogre::Degree(-5 * rotate));
		else
			dirVec.x += move;
		cameraFollowing = 0;
	}

	if (mKeyboard->isKeyDown(OIS::KC_R)) {
		cameraNode->resetToInitialState();
		cameraNode->translate(0, 200, 500, Ogre::Node::TransformSpace::TS_LOCAL);
		cameraFollowing = 0;
	}

	if (cameraFollowing) { //follow entity
		Ogre::Vector3 entity_size = cameraFollowing->sceneNode->_getWorldAABB().getSize();

		Ogre::Vector3 entity_loc = cameraFollowing->sceneNode->_getDerivedPosition();
		entity_loc.y += (1.6 * entity_size.y);
		cameraNode->setPosition(entity_loc);

		cameraNode->resetOrientation();
		cameraNode->yaw(Ogre::Degree(-90 - cameraFollowing->heading));

		cameraNode->translate(0.f, 0.f, 1.5 * std::max(entity_size.x, entity_size.z), Ogre::Node::TransformSpace::TS_LOCAL);
	} else { //apply user input
		cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
		if (cameraNode->_getDerivedPosition().y < 2)
			cameraNode->translate(0, 2 - cameraNode->_getDerivedPosition().y, 0, Ogre::Node::TS_LOCAL);
	}
}

void InputMgr::UpdateVelocityAndSelection(float dt) {
	const static float keyTime = 0.2f;

	keyboardTimer -= dt;

	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_UP)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredSpeed(deltaDesiredSpeed);
	}
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_DOWN)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredSpeed(-deltaDesiredSpeed);
	}
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_LEFT)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredHeading(-deltaDesiredHeading);
		//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredHeading(deltaDesiredHeading);
	}

	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_PGUP)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredAltitude(deltaDesiredAltitude);
	}
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_PGDOWN)) {
		keyboardTimer = keyTime;
		engine->entityMgr->ChangeSelectedDesiredAltitude(-deltaDesiredAltitude);
	}

//Set velocity to zero....
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)) {
		keyboardTimer = keyTime;
		engine->entityMgr->StopSelectedEntities();
	}

//tab handling
	if ((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)) {
		keyboardTimer = keyTime;
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->entityMgr->AddNextUnselectedToGroup();
		else
			engine->entityMgr->SelectNextEntity();
	}
}

void InputMgr::LoadLevel() {
	engine->gfxMgr->windowResized(engine->gfxMgr->mWindow);
}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke) {
	if (ke.key == OIS::KC_T) {
		if (!cameraFollowing)
			cameraFollowing = engine->entityMgr->GetMainSelected(); //follow selected object
		else
			cameraFollowing = 0; //stop following
	}
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke) {
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me) {
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid) {

	if (mid == OIS::MouseButtonID::MB_Left || mid == OIS::MouseButtonID::MB_Right || mid == OIS::MouseButtonID::MB_Middle) {

		//create ray and check intersection with xz plane
		Ogre::Ray ray = engine->gfxMgr->mCamera->getCameraToViewportRay(float(me.state.X.abs) / float(engine->gfxMgr->mWindow->getWidth()),
			float(me.state.Y.abs) / float(engine->gfxMgr->mWindow->getHeight()));
		std::pair<bool, Ogre::Real> groundIntersection = ray.intersects(Ogre::Plane(Ogre::Vector3(0.f, 1.f, 0.f), 0.f));

		if (groundIntersection.first) { //we have an intersection with ocean
			//Ogre::Vector3 intersectPt = ray.getPoint(groundIntersection.second);

			int nearestEntIndex = -1;
			int nearestEntDistance = 250;
			for (int i = 0; i < engine->entityMgr->count; ++i) {
				Ogre::Vector3 entLoc = engine->entityMgr->GetEntity(i)->sceneNode->_getDerivedPosition();
				float distanceToRay = ray.getOrigin().distance(entLoc)
					* std::sin(ray.getDirection().angleBetween(entLoc - ray.getOrigin()).valueRadians()); //use right triangle to find normal vector length between ray and entity point

				if (distanceToRay < nearestEntDistance) { //found new closest entity
					nearestEntIndex = i;
					nearestEntDistance = distanceToRay;
				}
			}

			if (nearestEntIndex >= 0 && mid == OIS::MouseButtonID::MB_Left) { //select clicked object
				std::cout << std::endl << "SUCCESS: Now selecting entity nearest click!" << std::endl;
				if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
					engine->entityMgr->AddEntityToGroup(nearestEntIndex);
				else
					engine->entityMgr->SelectEntity(nearestEntIndex);
			} else if (nearestEntIndex >= 0 && mid == OIS::MouseButtonID::MB_Right) { //follow clicked object

				if (engine->entityMgr->IsEntitySelected(engine->entityMgr->GetEntity(nearestEntIndex))) {
					std::cout << std::endl << "FAILURE: An entity cannot follow itself!" << std::endl;
				} else {
					engine->entityMgr->AddFollowCommandToSelectedEntities(engine->entityMgr->GetEntity(nearestEntIndex));
					std::cout << std::endl << "SUCCESS: Now having selected entities following clicked entity!" << std::endl;
				}

			} else if (mid == OIS::MouseButtonID::MB_Middle) { //set desired location
				Ogre::Vector3 clickLoc = ray.getPoint(groundIntersection.second);
				clickLoc.y = 0.f;

				std::cout << std::endl << "SUCCESS: Having selected entities go to location: " << clickLoc << std::endl;
				engine->entityMgr->AddMoveCommandToSelectedEntities(clickLoc);
			} else { //couldn't find entity
				std::cout << std::endl << "FAILURE: No entity near click! No new entity selected!" << std::endl;
			}
		} else { //ray didn't hit plane
			std::cout << std::endl << "FAILURE: Ray didn't intersect with ground. Make sure click makes its to XZ plane!" << std::endl;
		}
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid) {
	return true;
}
