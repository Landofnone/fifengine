/***************************************************************************
 *   Copyright (C) 2005-2007 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

// Standard C++ library includes

// Platform specific includes

// 3rd party library includes
#include <boost/filesystem/convenience.hpp>

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "util/rect.h"
#include "util/exception.h"
#include "video/image.h"
#include "video/renderbackend.h"

#include "fontbase.h"

namespace FIFE {

	FontBase::FontBase(): 
		m_pool(),
		mColor(),
		mGlyphSpacing(0),
		mRowSpacing(0),
		mFilename(""),
		m_antiAlias(true) {
	}

	void FontBase::setRowSpacing(int spacing) {
		mRowSpacing = spacing;
	}

	int FontBase::getRowSpacing() const {
		return mRowSpacing;
	}

	void FontBase::setGlyphSpacing(int spacing) {
		mGlyphSpacing = spacing;
	}

	int FontBase::getGlyphSpacing() const {
		return mGlyphSpacing;
	}

	void FontBase::setAntiAlias(bool antiAlias) {
		m_antiAlias = antiAlias;
	}

	bool FontBase::isAntiAlias() {
		return m_antiAlias;
	}

	SDL_Color FontBase::getColor() const {
		return mColor;
	}

	int FontBase::getStringIndexAt(const std::string &text, int x) {
		for (int i = 0; i < static_cast<int>(text.size()); ++i) {
			if (getWidth(text.substr(0,i)) > x) {
				return i-1;
			}
		}
		return text.length();
	}

	Image* FontBase::getAsImage(const std::string& text) {
		Image* image = m_pool.getRenderedText(this, text);
		if (!image) {
			SDL_Surface* textSurface = renderString(text);
			image = RenderBackend::instance()->createStaticImageFromSDL(textSurface);
			m_pool.addRenderedText( this, text, image );
		}
		return image;
	}
}