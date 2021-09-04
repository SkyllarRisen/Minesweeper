/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "FrameTimer.h"
#include <thread>
#include <chrono>


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	mField( Vec2I(Graphics::ScreenWidth - ( 20 * MineField::Tile::dim + 20 ), Graphics::ScreenHeight - ( 20 * MineField::Tile::dim + 20 ) ) / 2 , 20, 20, 20)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	double elapsedTime = ft.Mark();
	frameTime = elapsedTime;
	while (elapsedTime > 0.0)
	{
		const double dt = std::min(elapsedTime, 0.001);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

bool Game::GameOver() const
{
	return abortGame;
}

void Game::UpdateModel(const double dt)
{
	
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		abortGame = true;

	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();

		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			mField.OnRevealClick(e.GetPos());
		}

		if (e.GetType() == Mouse::Event::Type::RPress)
		{
			mField.OnToggleFlagClick(e.GetPos());
		}

	}	
}

void Game::ComposeFrame()
{
	mField.Draw(gfx);
}
