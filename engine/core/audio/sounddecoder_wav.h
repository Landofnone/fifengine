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

#ifndef FIFE_SOUNDDECODER_WAV_H
#define FIFE_SOUNDDECODER_WAV_H

// Standard C++ library includes

// Platform specific includes

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "vfs/raw/rawdata.h"

#include "sounddecoder.h"

namespace FIFE {
	
	/* The SoundDecoder class for wav-files
	 * Most of the code is from the Allacrost Audio Engine
	 */
	class SoundDecoderWav : public SoundDecoder {
	public:
		
		SoundDecoderWav(RawDataPtr file);
		
		~SoundDecoderWav() {
			releaseBuffer();
		}
		
		/** Returns the decoded length of the file in bytes
		 */
		unsigned long getDecodedLength() {
			return m_declength;
		}
		
		/** Sets the current position in the file (in bytes)
		 *
		 * @return 0 (False), if the positioning was successful
		 */
		bool setCursor(unsigned long pos);
		
		/** Request the decoding of the next part of the stream.
		 *
		 * @param length The length of the decoded part
		 * @return 0 (False), if decoding was successful
		 */
		bool decode(unsigned long length);
		
		/** Returns the next decoded buffer.
		 *
		 * The length of the buffer is returned by getBufferSize().
		 */
		void *getBuffer() {
			return m_data;
		}
		
		/** Returns the byte-size of the buffer returned by getBuffer().
		 */
		unsigned long getBufferSize() {
			return m_datasize;
		}
		
		/** Releases the buffer returned by getBuffer()
		 */
		void releaseBuffer() {
			if (m_data != NULL) {
				delete[] m_data;
				m_data = NULL;
			}
		}
		
	private:
		unsigned long	m_beginning;
		unsigned long	m_declength;
		unsigned long	m_datasize;
		char*					m_data;
		RawDataPtr		m_file;
	};
}
	
#endif