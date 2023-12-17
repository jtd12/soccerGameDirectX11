#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	if (!this->render_window.Initialize(this, hInstance, window_title, window_class, width, height))
		return false;

	if (!gfx.Initialize(this->render_window.GetHWND(), width, height))
		return false;


	this->gfx.modelRobot[0]->SetPosition(10, 8.0, 40);
	this->gfx.modelRobot[1]->SetPosition(10, 8.0, 38);
	this->gfx.modelRobot[2]->SetPosition(10, 8.0, 36);
	this->gfx.modelRobot[3]->SetPosition(10, 8.0, 34);
	this->gfx.modelRobot[4]->SetPosition(10, 8.0, 32);
	this->gfx.modelRobot[5]->SetPosition(10, 8.0, 29);
	this->gfx.modelRobot[6]->SetPosition(10, 8.0, 27);
	this->gfx.modelRobot[7]->SetPosition(10, 8.0, 25);
	this->gfx.modelRobot[8]->SetPosition(10, 8.0, 22);
	this->gfx.modelRobot[9]->SetPosition(10, 8.0, 20);



	this->gfx.modelRobotAI[0]->SetPosition(20, 8.0, 40);
	this->gfx.modelRobotAI[1]->SetPosition(20, 8.0, 38);
	this->gfx.modelRobotAI[2]->SetPosition(20, 8.0, 36);
	this->gfx.modelRobotAI[3]->SetPosition(20, 8.0, 34);
	this->gfx.modelRobotAI[4]->SetPosition(20, 8.0, 32);
	this->gfx.modelRobotAI[5]->SetPosition(20, 8.0, 29);
	this->gfx.modelRobotAI[6]->SetPosition(20, 8.0, 27);
	this->gfx.modelRobotAI[7]->SetPosition(20, 8.0, 25);
	this->gfx.modelRobotAI[8]->SetPosition(20, 8.0, 22);
	this->gfx.modelRobotAI[9]->SetPosition(20, 8.0, 20);

	this->gfx.b->SetPosition(0, 0.7f, -1);

	return true;
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}
void Engine::positionsPlayers()
{
	this->gfx.modelRobot[0]->movement(XMFLOAT3(20, 7.0, -17),1);
	this->gfx.modelRobot[1]->movement(XMFLOAT3(40, 7.0, -8), 1);
	this->gfx.modelRobot[2]->movement(XMFLOAT3(45, 7.0, -35), 1);
	this->gfx.modelRobot[3]->movement(XMFLOAT3(10, 7.0, 25), 1);
	this->gfx.modelRobot[4]->movement(XMFLOAT3(25, 7.0, -10), 1);
	this->gfx.modelRobot[5]->movement(XMFLOAT3(30, 7.0, 15), 1);
	this->gfx.modelRobot[6]->movement(XMFLOAT3(5, 7.0, -20), 1);
	this->gfx.modelRobot[7]->movement(XMFLOAT3(35, 7.0, -25), 1);
	this->gfx.modelRobot[8]->movement(XMFLOAT3(25, 7.0, 10), 1);
	this->gfx.modelRobot[9]->movement(XMFLOAT3(20, 7.0, -5), 1);



	this->gfx.modelRobotAI[0]->movement(XMFLOAT3(-20, 7.0, -17),- 1);
	this->gfx.modelRobotAI[1]->movement(XMFLOAT3(-40, 7.0, -8),- 1);
	this->gfx.modelRobotAI[2]->movement(XMFLOAT3(-45, 7.0, -35), -1);
	this->gfx.modelRobotAI[3]->movement(XMFLOAT3(-10, 7.0, 25), -1);
	this->gfx.modelRobotAI[4]->movement(XMFLOAT3(-25, 7.0, -10),- 1);
	this->gfx.modelRobotAI[5]->movement(XMFLOAT3(-30, 7.0, 15), -1);
	this->gfx.modelRobotAI[6]->movement(XMFLOAT3(-5, 7.0, -20), -1);
	this->gfx.modelRobotAI[7]->movement(XMFLOAT3(-35, 7.0, -25),- 1);
	this->gfx.modelRobotAI[8]->movement(XMFLOAT3(-25, 7.0, 10), -1);
	this->gfx.modelRobotAI[9]->movement(XMFLOAT3(-20, 7.0, -5), -1);

}
void Engine::Update()
{
	this->gfx.modelDecor[1]->AdjustRotation(0, 0.001f, 0);

	positionsPlayers();


	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}
	//this->gfx.model.AdjustRotation(0.0f, 0.001f, 0.0f);
	
	//this->gfx.modelRobot[0]->SetPosition(5, 15, 2);
	//this->gfx.modelRobot[0]->AdjustRotation(0, 0.005, 0);


	const float cameraSpeed = 0.02f;

	if (keyboard.KeyIsPressed('W'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed(VK_SPACE))
	{
		this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
	}
	if (keyboard.KeyIsPressed('Z'))
	{
		this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
	}



}

void Engine::RenderFrame()
{
	this->gfx.RenderFrame();
}

