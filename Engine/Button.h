/******************************************************************************************
 *	Button.h																			  *
 *	Kacper Wojtkowski December 2024 r.												      *
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
 *****************************************************************************************/

 // !!!!!!!!!!!!!!!!!! IMPORTANT  !!!!!!!!!!!!!!!!!!!!!  
 // > Use `box-sizing: content-box;` (for sizeWidth and sizeHeight).  
 // > There's no need to set up the button during creation.  
 // > `MenuButton` is a type of button that must be placed  
 //   within a class that contains an `enum class`.  
 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  


#pragma once

#include <string>

#include "Graphics.h"
#include "Mouse.h"
#include "Font.h"
#include "Rect.h"
#include "Sound.h"
#include "Vec2.h"

class Button
{
public:
	Button() = default;
	Button(const Font* font, const std::string& text, const Vei2& pos)
		: 
		font(font),
		text(text),
		pos(pos),
		sizeWidth((int)text.size() * font->GetWidthChar()),
		sizeHeight(font->GetHeightChar())
	{}

	void Draw(Graphics& gfx) const
	{
		const int borderSize = isSetBorder ? this->borderSize : 0;
		// border
		if (isSetBorder) gfx.DrawRect(GetRect().GetExpanded(borderSize), borderColor);
		// background
		if (isSetBackground && isSetBackgroundHoverDarker && hovered) gfx.DrawRect(GetRect(), Color::GetDarker(backgroundColor, darker));
		else if(isSetBackground ) gfx.DrawRect(GetRect(), backgroundColor);

		// padding
		Vei2 textPos = pos + Vei2{sizePaddingX + borderSize, sizePaddingY + borderSize};
		// positionCenter
		if (isSetPositionCenter)
		{
			textPos -= Vei2{sizeWidth / 2 + borderSize + sizePaddingX, sizeHeight / 2 + borderSize + sizePaddingY};
		}
		// textAlignCenter
		if (isSetTextAlignCenter) {
			const int textWidth = (int)text.size() * font->GetWidthChar();
			textPos += Vei2{(sizeWidth - textWidth) / 2, (sizeHeight - font->GetHeightChar()) / 2};
		}

		font->DrawText(text, textPos, fontColor, gfx);
	}
	void ProcessMouse(const Mouse::Event& e)
	{
		// hovered
		hovered = GetRect().Contains(e.GetPos());

		if (hovered && !hoveredAlready) {
			hoverSound.Play();
			hoveredAlready = true;
		}
		else if(!hovered){
			hoveredAlready = false;
		}

		// clicked
		if (hovered) {
			clicked = e.LeftIsPressed();
		}
	}
	bool IsClicked() const
	{
		return hovered && clicked;
	}
	bool IsHovered() const
	{
		return hovered;
	}
	void PositionMoveBy(const Vei2& vec)
	{
		pos += vec;
	}

	int GetPosEndX() const // USE WITH BRAIN (I PREFER TO USE IT DIRECTRLY IN GAME() )
	{
		return GetRect().right + borderSize;
	}

	//************* STYLE DEFAULTS *************//
	// naked
	void ToNaked() 
	{
		// font
		fontColor = Colors::White;
		isSetFontHoverDarker = false;
		// text
		isSetTextAlignCenter = true;
		// border
		isSetBorder = false;
		// background
		isSetBackground = false;
	}
	// default
	void ToDefault()
	{
		// darker
		darker = 20;
		// position
		isSetPositionCenter = false;
		// font
		fontColor = Colors::Black;
		isSetFontHoverDarker = true;
		// text
		isSetTextAlignCenter = true;
		// border
		isSetBorder = true;
		borderColor = Colors::Gray;
		borderSize = 5;
		// background
		isSetBackground = true;
		backgroundColor = Colors::White;
		isSetBackgroundHoverDarker = true;
	}

	//*********** SETTERS FOR STYLES ***********//
	
	// darker
	void SetDarker(int valDarker)
	{
		darker = valDarker;
	}
	// position
	void SetPositionCenter(bool set = false)
	{
		isSetPositionCenter = set;
	}
	// font
	void SetFontHoverDarker(bool set = true)
	{
		isSetFontHoverDarker = set;
	}
	// text
	void SetTextAlignCenter(bool set = false)
	{
		isSetTextAlignCenter = set;
	}
	// size
	void SetSize(int width, int height)
	{
		sizeWidth = width;
		sizeHeight = height;
	}
	void SetSizePadding(int paddingX = 12, int paddingY = 8)
	{
		sizePaddingX = paddingX;
		sizePaddingY = paddingY;
	}
	// border
	void SetBorder(bool set = true, int size = 5, Color color = Colors::Gray)
	{
		isSetBorder = set;
		borderSize = size;
		borderColor = color;
	}
	// background
	void SetBackground(bool set = true, Color color = Colors::White, bool setHoverDarker = true)
	{
		isSetBackground = set;
		backgroundColor = color;
		isSetBackgroundHoverDarker = setHoverDarker;
	}
	//********************************//

private:
	RectI GetRect() const
	{

		if (isSetPositionCenter == false) {
			const int borderSize = isSetBorder ? this->borderSize : 0;
			return RectI(pos + Vei2(borderSize, borderSize), sizePaddingX + sizeWidth + sizePaddingX, sizePaddingY + sizeHeight + sizePaddingY);
		}
		return RectI::FromCenter(pos, sizeWidth / 2 + sizePaddingX, sizeHeight / 2 + sizePaddingY);
	}

private:
	const Font* font = nullptr;
	Vei2 pos;
	std::string text;
	bool hovered = false;
	bool clicked = false;
	Sound hoverSound = { L"Sounds/menu_boop.wav" };
	bool hoveredAlready = false;

	//*********** STYLES ***********//
	// darker
	int darker = 20;
	// position
	bool isSetPositionCenter = false;
	// font
	Color fontColor = Colors::Black;
	bool isSetFontHoverDarker = true;
	// text
	bool isSetTextAlignCenter = true;
	// size (width and height are set according to the font size)
	int sizeWidth; 
	int sizeHeight;
	int sizePaddingX = 12;
	int sizePaddingY = 8;
	// border
	bool isSetBorder = true;
	Color borderColor = Colors::Gray;
	int borderSize = 5;
	// background
	bool isSetBackground = true;
	Color backgroundColor = Colors::White;
	bool isSetBackgroundHoverDarker = true;
	//*****************************//
};

template<typename O>
class MenuButton : public Button
{
public:
	MenuButton() = default;
	MenuButton(const O& option, const Font* font, const std::string& text, const Vei2& pos)
		:
		Button(font, text, pos),
		option(option)
	{}
	O GetOption() const {
		return option;
	}
private:
	O option;
};