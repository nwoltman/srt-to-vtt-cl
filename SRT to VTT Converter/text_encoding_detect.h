#pragma once
#ifndef TEXT_ENCODING_DETECT_H_
#define TEXT_ENCODING_DETECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) 2014, Jonathan Bennett & AutoIt Consulting Ltd
// All rights reserved.
// http://www.autoitconsulting.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
// *Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////////
//
// text_encoding_detect.h
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include <stddef.h>

namespace AutoIt
{
	class TextEncodingDetect
	{
	public:
		enum Encoding
		{
			None,				// Unknown or binary
			ANSI,				// 0-255
			ASCII,				// 0-127
			UTF8_BOM,			// UTF8 with BOM
			UTF8_NOBOM,			// UTF8 without BOM
			UTF16_LE_BOM,		// UTF16 LE with BOM
			UTF16_LE_NOBOM,		// UTF16 LE without BOM
			UTF16_BE_BOM,		// UTF16-BE with BOM
			UTF16_BE_NOBOM,		// UTF16-BE without BOM
		};

		TextEncodingDetect();
		~TextEncodingDetect();

		Encoding CheckBOM(const unsigned char *pBuffer, size_t size);		// Just check if there is a BOM and return 
		Encoding DetectEncoding(const unsigned char *pBuffer, size_t size);	// Check BOM and also guess if there is no BOM
		static int GetBOMLengthFromEncodingMode(Encoding encoding);			// Just return the BOM length of a given mode

		void SetNullSuggestsBinary(bool null_suggests_binary) { null_suggests_binary_ = null_suggests_binary; }
		void SetUtf16UnexpectedNullPercent(int percent);
		void SetUtf16ExpectedNullPercent(int percent);

	private:
		TextEncodingDetect(const TextEncodingDetect&);
		const TextEncodingDetect& operator=(const TextEncodingDetect&);

		static const unsigned char* utf16_bom_le_;
		static const unsigned char* utf16_bom_be_;
		static const unsigned char* utf8_bom_;

		bool	null_suggests_binary_;
		int		utf16_expected_null_percent_;
		int		utf16_unexpected_null_percent_;

		Encoding CheckUTF8(const unsigned char *pBuffer, size_t size);				// Check for valid UTF8 with no BOM
		Encoding CheckUTF16NewlineChars(const unsigned char *pBuffer, size_t size);	// Check for valid UTF16 with no BOM via control chars
		Encoding CheckUTF16ASCII(const unsigned char *pBuffer, size_t size);		// Check for valid UTF16 with no BOM via null distribution
		bool DoesContainNulls(const unsigned char *pBuffer, size_t size);			// Check for nulls
	};

} // AutoIt

//////////////////////////////////////////////////////////////////////

#endif
